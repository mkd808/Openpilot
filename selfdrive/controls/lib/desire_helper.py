from cereal import log
from openpilot.common.conversions import Conversions as CV
from openpilot.common.realtime import DT_MDL

from openpilot.selfdrive.frogpilot.functions.frogpilot_functions import calculate_lane_width

LaneChangeState = log.LateralPlan.LaneChangeState
LaneChangeDirection = log.LateralPlan.LaneChangeDirection
TurnDirection = log.LateralPlan.Desire

LANE_CHANGE_SPEED_MIN = 20 * CV.MPH_TO_MS
LANE_CHANGE_TIME_MAX = 10.

DESIRES = {
  LaneChangeDirection.none: {
    LaneChangeState.off: log.LateralPlan.Desire.none,
    LaneChangeState.preLaneChange: log.LateralPlan.Desire.none,
    LaneChangeState.laneChangeStarting: log.LateralPlan.Desire.none,
    LaneChangeState.laneChangeFinishing: log.LateralPlan.Desire.none,
  },
  LaneChangeDirection.left: {
    LaneChangeState.off: log.LateralPlan.Desire.none,
    LaneChangeState.preLaneChange: log.LateralPlan.Desire.none,
    LaneChangeState.laneChangeStarting: log.LateralPlan.Desire.laneChangeLeft,
    LaneChangeState.laneChangeFinishing: log.LateralPlan.Desire.laneChangeLeft,
  },
  LaneChangeDirection.right: {
    LaneChangeState.off: log.LateralPlan.Desire.none,
    LaneChangeState.preLaneChange: log.LateralPlan.Desire.none,
    LaneChangeState.laneChangeStarting: log.LateralPlan.Desire.laneChangeRight,
    LaneChangeState.laneChangeFinishing: log.LateralPlan.Desire.laneChangeRight,
  },
}

TURN_DESIRES = {
  TurnDirection.none: log.LateralPlan.Desire.none,
  TurnDirection.turnLeft: log.LateralPlan.Desire.turnLeft,
  TurnDirection.turnRight: log.LateralPlan.Desire.turnRight,
}


class DesireHelper:
  def __init__(self):
    self.lane_change_state = LaneChangeState.off
    self.lane_change_direction = LaneChangeDirection.none
    self.lane_change_timer = 0.0
    self.lane_change_ll_prob = 1.0
    self.keep_pulse_timer = 0.0
    self.prev_one_blinker = False
    self.desire = log.LateralPlan.Desire.none

    # FrogPilot variables
    self.turn_direction = TurnDirection.none

    self.lane_change_completed = False
    self.turn_completed = False

    self.lane_change_wait_timer = 0
    self.lane_width_left = 0
    self.lane_width_right = 0

  def update(self, carstate, modeldata, lateral_active, lane_change_prob, frogpilot_planner):
    v_ego = carstate.vEgo
    one_blinker = carstate.leftBlinker != carstate.rightBlinker
    below_lane_change_speed = v_ego < LANE_CHANGE_SPEED_MIN

    # Calculate the left and right lane widths
    check_lane_width = frogpilot_planner.adjacent_lanes or frogpilot_planner.blind_spot_path
    turning = abs(carstate.steeringAngleDeg) >= 60
    if check_lane_width and not turning:
      # Calculate left and right lane widths
      self.lane_width_left = calculate_lane_width(modeldata.laneLines[0], modeldata.laneLines[1], modeldata.roadEdges[0])
      self.lane_width_right = calculate_lane_width(modeldata.laneLines[3], modeldata.laneLines[2], modeldata.roadEdges[1])
    else:
      self.lane_width_left = 0
      self.lane_width_right = 0

    # Calculate the desired lane width for nudgeless lane change with lane detection
    if not (frogpilot_planner.lane_detection and one_blinker) or below_lane_change_speed:
      lane_available = True
    else:
      # Set the minimum lane threshold to 2.8 meters
      min_lane_threshold = 2.8
      desired_lane = self.lane_width_left if carstate.leftBlinker else self.lane_width_right
      # Check if the lane width exceeds the threshold
      lane_available = desired_lane >= min_lane_threshold

    if not lateral_active or self.lane_change_timer > LANE_CHANGE_TIME_MAX:
      self.lane_change_state = LaneChangeState.off
      self.lane_change_direction = LaneChangeDirection.none
      self.turn_direction = TurnDirection.none
    elif one_blinker and below_lane_change_speed and frogpilot_planner.turn_desires:
      self.turn_direction = TurnDirection.turnLeft if carstate.leftBlinker else TurnDirection.turnRight
      # Set the "turn_completed" flag to prevent lane changes after completing a turn
      self.turn_completed = True
    else:
      # TurnDirection.turnLeft / turnRight
      self.turn_direction = TurnDirection.none

      # LaneChangeState.off
      if self.lane_change_state == LaneChangeState.off and one_blinker and not self.prev_one_blinker and not below_lane_change_speed:
        self.lane_change_state = LaneChangeState.preLaneChange
        self.lane_change_ll_prob = 1.0
        self.lane_change_wait_timer = 0

      # LaneChangeState.preLaneChange
      elif self.lane_change_state == LaneChangeState.preLaneChange:
        # Set lane change direction
        self.lane_change_direction = LaneChangeDirection.left if \
          carstate.leftBlinker else LaneChangeDirection.right

        torque_applied = carstate.steeringPressed and \
                         ((carstate.steeringTorque > 0 and self.lane_change_direction == LaneChangeDirection.left) or
                          (carstate.steeringTorque < 0 and self.lane_change_direction == LaneChangeDirection.right))

        blindspot_detected = ((carstate.leftBlindspot and self.lane_change_direction == LaneChangeDirection.left) or
                              (carstate.rightBlindspot and self.lane_change_direction == LaneChangeDirection.right))

        # Conduct a nudgeless lane change if all the conditions are true
        self.lane_change_wait_timer += DT_MDL
        if frogpilot_planner.nudgeless and lane_available and not self.lane_change_completed and self.lane_change_wait_timer >= frogpilot_planner.lane_change_delay:
          self.lane_change_wait_timer = 0
          torque_applied = True

        if not one_blinker or below_lane_change_speed:
          self.lane_change_state = LaneChangeState.off
          self.lane_change_direction = LaneChangeDirection.none
        elif torque_applied and not blindspot_detected:
          # Set the "lane_change_completed" flag to prevent any more lane changes if the toggle is on
          self.lane_change_completed = frogpilot_planner.one_lane_change
          self.lane_change_state = LaneChangeState.laneChangeStarting

      # LaneChangeState.laneChangeStarting
      elif self.lane_change_state == LaneChangeState.laneChangeStarting:
        # fade out over .5s
        self.lane_change_ll_prob = max(self.lane_change_ll_prob - 2 * DT_MDL, 0.0)

        # 98% certainty
        if lane_change_prob < 0.02 and self.lane_change_ll_prob < 0.01:
          self.lane_change_state = LaneChangeState.laneChangeFinishing

      # LaneChangeState.laneChangeFinishing
      elif self.lane_change_state == LaneChangeState.laneChangeFinishing:
        # fade in laneline over 1s
        self.lane_change_ll_prob = min(self.lane_change_ll_prob + DT_MDL, 1.0)

        if self.lane_change_ll_prob > 0.99:
          self.lane_change_direction = LaneChangeDirection.none
          if one_blinker:
            self.lane_change_state = LaneChangeState.preLaneChange
          else:
            self.lane_change_state = LaneChangeState.off

    if self.lane_change_state in (LaneChangeState.off, LaneChangeState.preLaneChange):
      self.lane_change_timer = 0.0
    else:
      self.lane_change_timer += DT_MDL

    self.prev_one_blinker = one_blinker

    # Reset the flags
    self.lane_change_completed &= one_blinker
    self.turn_completed &= one_blinker

    if self.turn_direction != TurnDirection.none:
      self.desire = TURN_DESIRES[self.turn_direction]
    elif not self.turn_completed:
      self.desire = DESIRES[self.lane_change_direction][self.lane_change_state]
    else:
      self.desire = log.LateralPlan.Desire.none

    # Send keep pulse once per second during LaneChangeStart.preLaneChange
    if self.lane_change_state in (LaneChangeState.off, LaneChangeState.laneChangeStarting):
      self.keep_pulse_timer = 0.0
    elif self.lane_change_state == LaneChangeState.preLaneChange:
      self.keep_pulse_timer += DT_MDL
      if self.keep_pulse_timer > 1.0:
        self.keep_pulse_timer = 0.0
      elif self.desire in (log.LateralPlan.Desire.keepLeft, log.LateralPlan.Desire.keepRight):
        self.desire = log.LateralPlan.Desire.none
