import math
from cereal import car
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.car import get_safety_config
from openpilot.selfdrive.car.interfaces import CarInterfaceBase
from openpilot.selfdrive.car.body.values import SPEED_FROM_RPM

class CarInterface(CarInterfaceBase):
  @staticmethod
  def _get_params(ret, candidate, fingerprint, car_fw, experimental_long, docs):
    ret.notCar = True
    ret.carName = "body"
    ret.safetyConfigs = [get_safety_config(car.CarParams.SafetyModel.body)]

    ret.minSteerSpeed = -math.inf
    ret.maxLateralAccel = math.inf  # TODO: set to a reasonable value
    ret.steerRatio = 0.5
    ret.steerLimitTimer = 1.0
    ret.steerActuatorDelay = 0.

    ret.mass = 9
    ret.wheelbase = 0.406
    ret.wheelSpeedFactor = SPEED_FROM_RPM
    ret.centerToFront = ret.wheelbase * 0.44

    ret.radarUnavailable = True
    ret.openpilotLongitudinalControl = True
    ret.steerControlType = car.CarParams.SteerControlType.angle

    return ret

  def _update(self, c, conditional_experimental_mode, experimental_mode_via_lkas, mute_door, mute_seatbelt, personalities_via_wheel):
    ret = self.CS.update(self.cp, conditional_experimental_mode, experimental_mode_via_lkas, personalities_via_wheel)

    # wait for everything to init first
    if self.frame > int(5. / DT_CTRL):
      # body always wants to enable
      ret.init('events', 1)
      ret.events[0].name = car.CarEvent.EventName.pcmEnable
      ret.events[0].enable = True
    self.frame += 1

    return ret

  def apply(self, c, now_nanos, sport_plus):
    return self.CC.update(c, self.CS, now_nanos)
