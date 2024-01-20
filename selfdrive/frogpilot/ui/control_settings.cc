#include "selfdrive/frogpilot/ui/control_settings.h"
#include "selfdrive/ui/ui.h"

FrogPilotControlsPanel::FrogPilotControlsPanel(SettingsWindow *parent) : FrogPilotListWidget(parent) {
  const std::vector<std::tuple<QString, QString, QString, QString>> controlToggles {
    {"AdjustablePersonalities", "Adjustable Personalities", "Use the 'Distance' button on the steering wheel or the onroad UI to switch between openpilot's driving personalities.\n\n1 bar = Aggressive\n2 bars = Standard\n3 bars = Relaxed", "../frogpilot/assets/toggle_icons/icon_distance.png"},
    {"AlwaysOnLateral", "Always on Lateral", "Maintain openpilot lateral control when the brake or gas pedals are used.\n\nDeactivation occurs only through the 'Cruise Control' button.", "../frogpilot/assets/toggle_icons/icon_always_on_lateral.png"},

    {"ConditionalExperimental", "Conditional Experimental Mode", "Automatically switches to 'Experimental Mode' under predefined conditions.", "../frogpilot/assets/toggle_icons/icon_conditional.png"},
    {"CECurves", "Curve Detected Ahead", "Switch to 'Experimental Mode' when a curve is detected.", ""},
    {"CENavigation", "Navigation Based", "Switch to 'Experimental Mode' based on navigation data. (i.e. Intersections, stop signs, etc.)", ""},
    {"CESlowerLead", "Slower Lead Detected Ahead", "Switch to 'Experimental Mode' when a slower lead vehicle is detected ahead.", ""},
    {"CEStopLights", "Stop Lights and Stop Signs", "Switch to 'Experimental Mode' when a stop light or stop sign is detected.", ""},
    {"CESignal", "Turn Signal When Below Highway Speeds", "Switch to 'Experimental Mode' when using turn signals below highway speeds to help assit with turns.", ""},

    {"CustomPersonalities", "Custom Driving Personalities", "Customize the driving personality profiles to your driving style.", "../frogpilot/assets/toggle_icons/icon_custom.png"},
    {"DeviceShutdown", "Device Shutdown Timer", "Configure the timer for automatic device shutdown when offroad conserving energy and preventing battery drain.", "../frogpilot/assets/toggle_icons/icon_time.png"},
    {"ExperimentalModeActivation", "Experimental Mode Via", "Toggle Experimental Mode by double-clicking the 'Lane Departure'/'LKAS' button or double tapping screen.\n\nOverrides 'Conditional Experimental Mode'.", "../assets/img_experimental_white.svg"},

    {"FireTheBabysitter", "Fire the Babysitter", "Deactivate some of openpilot's 'Babysitter' protocols for more user autonomy.", "../frogpilot/assets/toggle_icons/icon_babysitter.png"},
    {"NoLogging", "Disable All Logging", "Turn off all data tracking to enhance privacy or reduce thermal load.\n\nWARNING: This action will prevent drive recording and data cannot be recovered!", ""},
    {"MuteDoor", "Mute Door Open Alert", "Disable alerts for open doors.", ""},
    {"MuteDM", "Mute Driver Monitoring", "Disable driver monitoring.", ""},
    {"MuteOverheated", "Mute Overheated System Alert", "Disable alerts for the device being overheated.", ""},
    {"MuteSeatbelt", "Mute Seatbelt Unlatched Alert", "Disable alerts for unlatched seatbelts.", ""},
    {"OfflineMode", "Offline Mode", "Allow the device to be offline indefinitely.", ""},

    {"LateralTune", "Lateral Tuning", "Modify openpilot's steering behavior.", "../frogpilot/assets/toggle_icons/icon_lateral_tune.png"},
    {"AverageCurvature", "Average Desired Curvature", "Use Pfeiferj's distance-based curvature adjustment for improved curve handling.", ""},
    {"NNFF", "NNFF - Neural Network Feedforward", "Use Twilsonco's Neural Network Feedforward for enhanced precision in lateral control.", ""},
    {"SteerRatio", steerRatioStock != 0 ? QString("Steer Ratio (Default: %1)").arg(steerRatioStock, 0, 'f', 2) : "Steer Ratio", "Set a custom steer ratio for your vehicle controls.", ""},

    {"LongitudinalTune", "Longitudinal Tuning", "Modify openpilot's acceleration and braking behavior.", "../frogpilot/assets/toggle_icons/icon_longitudinal_tune.png"},
    {"AccelerationProfile", "Acceleration Profile", "Change the acceleration rate to be either sporty or eco-friendly.", ""},
    {"AggressiveAcceleration", "Aggressive Acceleration With Lead", "Increase acceleration aggressiveness when following a lead vehicle from a stop.", ""},
    {"StoppingDistance", "Increased Stopping Distance", "Increase the stopping distance for a more comfortable stop.", ""},
    {"SmoothBraking", "Smoother Braking Behind Lead", "Smoothen out the braking behavior when approaching slower vehicles.", ""},

    {"Model", "Model Selector", "Choose your preferred openpilot model.", "../assets/offroad/icon_calibration.png"},

    {"MTSCEnabled", "Map Turn Speed Control", "Slow down for anticipated curves detected by your downloaded maps.", "../frogpilot/assets/toggle_icons/icon_speed_map.png"},

    {"NudgelessLaneChange", "Nudgeless Lane Change", "Enable lane changes without manual steering input.", "../frogpilot/assets/toggle_icons/icon_lane.png"},
    {"LaneChangeTime", "Lane Change Timer", "Specify a delay before executing a nudgeless lane change.", ""},
    {"LaneDetection", "Lane Detection", "Block nudgeless lane changes when a lane isn't detected.", ""},
    {"OneLaneChange", "One Lane Change Per Signal", "Limit to one nudgeless lane change per turn signal activation.", ""},

    {"QOLControls", "Quality of Life", "Miscellaneous quality of life changes to improve your overall openpilot experience.", "../frogpilot/assets/toggle_icons/quality_of_life.png"},
    {"DisableOnroadUploads", "Disable Onroad Uploads", "Prevent large data uploads when onroad.", ""},
    {"HigherBitrate", "Higher Bitrate Recording", "Increases the quality of the footage uploaded to comma connect.", ""},
    {"PauseLateralOnSignal", "Pause Lateral On Turn Signal Below", "Temporarily disable lateral control during turn signal use below the set speed.", ""},
    {"ReverseCruise", "Reverse Cruise Increase", "Reverses the 'long press' functionality when increasing the max set speed. Useful to increase the max speed quickly.", ""},
    {"SetSpeedOffset", "Set Speed Offset", "Set an offset for your desired set speed.", ""},

    {"SpeedLimitController", "Speed Limit Controller", "Automatically adjust vehicle speed to match speed limits using 'Open Street Map's, 'Navigate On openpilot', or your car's dashboard (TSS2 Toyotas only).", "../assets/offroad/icon_speed_limit.png"},
    {"Offset1", "Speed Limit Offset (0-34 mph)", "Speed limit offset for speed limits between 0-34 mph.", ""},
    {"Offset2", "Speed Limit Offset (35-54 mph)", "Speed limit offset for speed limits between 35-54 mph.", ""},
    {"Offset3", "Speed Limit Offset (55-64 mph)", "Speed limit offset for speed limits between 55-64 mph.", ""},
    {"Offset4", "Speed Limit Offset (65-99 mph)", "Speed limit offset for speed limits between 65-99 mph.", ""},
    {"SLCFallback", "Fallback Method", "Choose your fallback method for when there are no speed limits currently being obtained from Navigation, OSM, and the car's dashboard.", ""},
    {"SLCOverride", "Override Method", "Choose your preferred method to override the current speed limit.", ""},
    {"SLCPriority", "Priority Order", "Determine the priority order for what speed limits to use.", ""},

    {"TurnDesires", "Use Turn Desires", "Use turn desires for enhanced precision in turns below the minimum lane change speed.", "../assets/navigation/direction_continue_right.png"},

    {"VisionTurnControl", "Vision Turn Speed Controller", "Slow down for detected road curvature for smoother curve handling.", "../frogpilot/assets/toggle_icons/icon_vtc.png"},
    {"CurveSensitivity", "Curve Detection Sensitivity", "Set curve detection sensitivity. Higher values prompt earlier responses, lower values lead to smoother but later reactions.", ""},
    {"TurnAggressiveness", "Turn Speed Aggressiveness", "Set turn speed aggressiveness. Higher values result in faster turns, lower values yield gentler turns.", ""},
  };

  for (const auto &[param, title, desc, icon] : controlToggles) {
    ParamControl *toggle;

    if (param == "AdjustablePersonalities") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 3, {{0, "None"}, {1, "Steering Wheel"}, {2, "Onroad UI Button"}, {3, "Wheel + Button"}}, this, true);

    } else if (param == "AlwaysOnLateral") {
      std::vector<QString> aolToggles{"AlwaysOnLateralMain"};
      std::vector<QString> aolToggleNames{tr("Enable On Cruise Main")};
      toggle = new FrogPilotParamToggleControl(param, title, desc, icon, aolToggles, aolToggleNames);

      QObject::connect(static_cast<FrogPilotParamToggleControl*>(toggle), &FrogPilotParamToggleControl::buttonClicked, [this](const bool checked) {
        if (checked) {
          FrogPilotConfirmationDialog::toggleAlert("WARNING: This is very experimental and isn't guaranteed to work. If you run into any issues, please report it in the FrogPilot Discord!",
          "I understand the risks.", this);
        }
        if (FrogPilotConfirmationDialog::toggle("Reboot required to take effect.", "Reboot Now", this)) {
          Hardware::reboot();
        }
      });

    } else if (param == "ConditionalExperimental") {
      FrogPilotParamManageControl *conditionalExperimentalToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(conditionalExperimentalToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        conditionalSpeedsImperial->setVisible(!isMetric);
        conditionalSpeedsMetric->setVisible(isMetric);
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(conditionalExperimentalKeys.find(key.c_str()) != conditionalExperimentalKeys.end());
        }
      });
      toggle = conditionalExperimentalToggle;
    } else if (param == "CECurves") {
      FrogPilotParamValueControl *CESpeedImperial = new FrogPilotParamValueControl("CESpeed", "Below", "Switch to 'Experimental Mode' below this speed in absence of a lead vehicle.", "", 0, 99,
                                                                                   std::map<int, QString>(), this, false, " mph");
      FrogPilotParamValueControl *CESpeedLeadImperial = new FrogPilotParamValueControl("CESpeedLead", "  w/Lead", "Switch to 'Experimental Mode' below this speed when following a lead vehicle.", "", 0, 99,
                                                                                       std::map<int, QString>(), this, false, " mph");
      conditionalSpeedsImperial = new FrogPilotDualParamControl(CESpeedImperial, CESpeedLeadImperial, this);
      addItem(conditionalSpeedsImperial);

      FrogPilotParamValueControl *CESpeedMetric = new FrogPilotParamValueControl("CESpeed", "Below", "Switch to 'Experimental Mode' below this speed in absence of a lead vehicle.", "", 0, 150,
                                                                                 std::map<int, QString>(), this, false, " kph");
      FrogPilotParamValueControl *CESpeedLeadMetric = new FrogPilotParamValueControl("CESpeedLead", "  w/Lead", "Switch to 'Experimental Mode' below this speed when following a lead vehicle.", "", 0, 150,
                                                                                     std::map<int, QString>(), this, false, " kph");
      conditionalSpeedsMetric = new FrogPilotDualParamControl(CESpeedMetric, CESpeedLeadMetric, this);
      addItem(conditionalSpeedsMetric);

      std::vector<QString> curveToggles{"CECurvesLead"};
      std::vector<QString> curveToggleNames{tr("With Lead")};
      toggle = new FrogPilotParamToggleControl(param, title, desc, icon, curveToggles, curveToggleNames);
    } else if (param == "CEStopLights") {
      std::vector<QString> stopLightToggles{"CEStopLightsLead"};
      std::vector<QString> stopLightToggleNames{tr("With Lead")};
      toggle = new FrogPilotParamToggleControl(param, title, desc, icon, stopLightToggles, stopLightToggleNames);

    } else if (param == "CustomPersonalities") {
      FrogPilotParamManageControl *customPersonalitiesToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(customPersonalitiesToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(false);
        }
        aggressiveProfile->setVisible(true);
        standardProfile->setVisible(true);
        relaxedProfile->setVisible(true);
      });
      toggle = customPersonalitiesToggle;

      FrogPilotParamValueControl *aggressiveFollow = new FrogPilotParamValueControl("AggressiveFollow", "Follow",
      "Set the 'Aggressive' personality' following distance. Represents seconds to follow behind the lead vehicle.\n\nStock: 1.25 seconds.", "../frogpilot/assets/other_images/aggressive.png",
      10, 50, std::map<int, QString>(), this, false, " sec", 10);
      FrogPilotParamValueControl *aggressiveJerk = new FrogPilotParamValueControl("AggressiveJerk", " Jerk",
      "Configure brake/gas pedal responsiveness for the 'Aggressive' personality. Higher values yield a more 'relaxed' response.\n\nStock: 0.5.", "", 1, 50,
                                                                std::map<int, QString>(), this, false, "", 10);
      aggressiveProfile = new FrogPilotDualParamControl(aggressiveFollow, aggressiveJerk, this, true);
      addItem(aggressiveProfile);

      FrogPilotParamValueControl *standardFollow = new FrogPilotParamValueControl("StandardFollow", "Follow",
      "Set the 'Standard' personality following distance. Represents seconds to follow behind the lead vehicle.\n\nStock: 1.45 seconds.", "../frogpilot/assets/other_images/standard.png",
      10, 50, std::map<int, QString>(), this, false, " sec", 10);
      FrogPilotParamValueControl *standardJerk = new FrogPilotParamValueControl("StandardJerk", " Jerk",
      "Adjust brake/gas pedal responsiveness for the 'Standard' personality. Higher values yield a more 'relaxed' response.\n\nStock: 1.0.", "", 1, 50,
                                                              std::map<int, QString>(), this, false, "", 10);
      standardProfile = new FrogPilotDualParamControl(standardFollow, standardJerk, this, true);
      addItem(standardProfile);

      FrogPilotParamValueControl *relaxedFollow = new FrogPilotParamValueControl("RelaxedFollow", "Follow",
      "Set the 'Relaxed' personality following distance. Represents seconds to follow behind the lead vehicle.\n\nStock: 1.75 seconds.", "../frogpilot/assets/other_images/relaxed.png",
      10, 50, std::map<int, QString>(), this, false, " sec", 10);
      FrogPilotParamValueControl *relaxedJerk = new FrogPilotParamValueControl("RelaxedJerk", " Jerk",
      "Set brake/gas pedal responsiveness for the 'Relaxed' personality. Higher values yield a more 'relaxed' response.\n\nStock: 1.0.", "", 1, 50,
                                                             std::map<int, QString>(), this, false, "", 10);
      relaxedProfile = new FrogPilotDualParamControl(relaxedFollow, relaxedJerk, this, true);
      addItem(relaxedProfile);

    } else if (param == "DeviceShutdown") {
      std::map<int, QString> shutdownLabels;
      for (int i = 0; i <= 33; ++i) {
        shutdownLabels[i] = i == 0 ? "Instant" : i <= 3 ? QString::number(i * 15) + " mins" : QString::number(i - 3) + (i == 4 ? " hour" : " hours");
      }
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 33, shutdownLabels, this, false);

    } else if (param == "ExperimentalModeActivation") {
      std::vector<QString> experimentalModeToggles{"ExperimentalModeViaLKAS", "ExperimentalModeViaScreen"};
      std::vector<QString> experimentalModeNames{tr("LKAS Button"), tr("Screen")};
      toggle = new FrogPilotParamToggleControl(param, title, desc, icon, experimentalModeToggles, experimentalModeNames);

    } else if (param == "FireTheBabysitter") {
      FrogPilotParamManageControl *fireTheBabysitterToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(fireTheBabysitterToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(fireTheBabysitterKeys.find(key.c_str()) != fireTheBabysitterKeys.end());
        }
      });
      toggle = fireTheBabysitterToggle;

    } else if (param == "LateralTune") {
      FrogPilotParamManageControl *lateralTuneToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(lateralTuneToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(lateralTuneKeys.find(key.c_str()) != lateralTuneKeys.end());
        }
      });
      toggle = lateralTuneToggle;
    } else if (param == "SteerRatio") {
      toggle = new FrogPilotParamValueControlFloat(param, title, desc, icon, steerRatioStock * 0.75, steerRatioStock * 1.25, std::map<int, QString>(), this, false, "", 10.0);

    } else if (param == "LongitudinalTune") {
      FrogPilotParamManageControl *longitudinalTuneToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(longitudinalTuneToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(longitudinalTuneKeys.find(key.c_str()) != longitudinalTuneKeys.end());
        }
      });
      toggle = longitudinalTuneToggle;
    } else if (param == "AccelerationProfile") {
      std::vector<QString> profileOptions{tr("Standard"), tr("Eco"), tr("Sport"), tr("Sport+")};
      FrogPilotButtonParamControl *profileSelection = new FrogPilotButtonParamControl(param, title, desc, icon, profileOptions);
      toggle = profileSelection;

      QObject::connect(static_cast<FrogPilotButtonParamControl*>(toggle), &FrogPilotButtonParamControl::buttonClicked, [this](int id) {
        if (id == 3) {
          FrogPilotConfirmationDialog::toggleAlert("WARNING: This maxes out openpilot's acceleration from 2.0 m/s to 4.0 m/s and may cause oscillations when accelerating!",
          "I understand the risks.", this);
        }
      });
    } else if (param == "StoppingDistance") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 10, std::map<int, QString>(), this, false, " feet");

    } else if (param == "Model") {
      modelSelectorButton = new FrogPilotButtonIconControl(title, tr("SELECT"), desc, icon);
      QStringList models = {"New Delhi (Default)", "Blue Diamond V1", "Blue Diamond V2", "Farmville", "New Lemon Pie"};
      QObject::connect(modelSelectorButton, &FrogPilotButtonIconControl::clicked, this, [this, models]() {
        int currentModel = params.getInt("Model");
        QString currentModelLabel = models[currentModel];

        QString selection = MultiOptionDialog::getSelection(tr("Select a driving model"), models, currentModelLabel, this);
        if (!selection.isEmpty()) {
          int selectedModel = models.indexOf(selection);
          params.putInt("Model", selectedModel);
          params.remove("CalibrationParams");
          params.remove("LiveTorqueParameters");
          modelSelectorButton->setValue(selection);
          if (FrogPilotConfirmationDialog::toggle("Reboot required to take effect.", "Reboot Now", this)) {
            Hardware::reboot();
          }
        }
      });
      modelSelectorButton->setValue(models[params.getInt("Model")]);
      addItem(modelSelectorButton);

    } else if (param == "NudgelessLaneChange") {
      FrogPilotParamManageControl *laneChangeToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(laneChangeToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(laneChangeKeys.find(key.c_str()) != laneChangeKeys.end());
        }
      });
      toggle = laneChangeToggle;
    } else if (param == "LaneChangeTime") {
      std::map<int, QString> laneChangeTimeLabels;
      for (int i = 0; i <= 10; ++i) {
        laneChangeTimeLabels[i] = i == 0 ? "Instant" : QString::number(i / 2.0) + " seconds";
      }
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 10, laneChangeTimeLabels, this, false);

    } else if (param == "QOLControls") {
      FrogPilotParamManageControl *qolToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(qolToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(qolKeys.find(key.c_str()) != qolKeys.end());
        }
      });
      toggle = qolToggle;
    } else if (param == "PauseLateralOnSignal") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 99, std::map<int, QString>(), this, false, " mph");
    } else if (param == "SetSpeedOffset") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 99, std::map<int, QString>(), this, false, " mph");

    } else if (param == "SpeedLimitController") {
      FrogPilotParamManageControl *speedLimitControllerToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(speedLimitControllerToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(speedLimitControllerKeys.find(key.c_str()) != speedLimitControllerKeys.end());
        }
        slscPriorityButton->setVisible(true);
      });
      toggle = speedLimitControllerToggle;
    } else if (param == "Offset1" || param == "Offset2" || param == "Offset3" || param == "Offset4") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 0, 99, std::map<int, QString>(), this, false, " mph");
    } else if (param == "SLCFallback") {
      std::vector<QString> fallbackOptions{tr("None"), tr("Experimental Mode"), tr("Previous Limit")};
      FrogPilotButtonParamControl *fallbackSelection = new FrogPilotButtonParamControl(param, title, desc, icon, fallbackOptions);
      toggle = fallbackSelection;
    } else if (param == "SLCOverride") {
      std::vector<QString> overrideOptions{tr("None"), tr("Manual Set Speed"), tr("Max Set Speed")};
      FrogPilotButtonParamControl *overrideSelection = new FrogPilotButtonParamControl(param, title, desc, icon, overrideOptions);
      toggle = overrideSelection;
    } else if (param == "SLCPriority") {
      const QStringList priorities {
        "Navigation, Dashboard, Offline Maps",
        "Navigation, Offline Maps, Dashboard",
        "Navigation, Offline Maps",
        "Navigation, Dashboard",
        "Navigation",
        "Offline Maps, Dashboard, Navigation",
        "Offline Maps, Navigation, Dashboard",
        "Offline Maps, Navigation",
        "Offline Maps, Dashboard",
        "Offline Maps",
        "Dashboard, Navigation, Offline Maps",
        "Dashboard, Offline Maps, Navigation",
        "Dashboard, Offline Maps",
        "Dashboard, Navigation",
        "Dashboard",
        "Highest",
        "Lowest",
        "",
      };

      slscPriorityButton = new ButtonControl(title, tr("SELECT"), desc);
      QObject::connect(slscPriorityButton, &ButtonControl::clicked, this, [this, priorities]() {
        QStringList availablePriorities = {"Dashboard", "Navigation", "Offline Maps", "Highest", "Lowest", "None"};
        QStringList selectedPriorities;
        int priorityValue = -1;

        QStringList priorityPrompts = {tr("Select your primary priority"), tr("Select your secondary priority"), tr("Select your tertiary priority")};

        for (int i = 0; i < 3; ++i) {
          QString selection = MultiOptionDialog::getSelection(priorityPrompts[i], availablePriorities, "", this);
          if (selection.isEmpty()) break;

          if (selection == "None") {
            priorityValue = 17;
            break;
          } else if (selection == "Highest") {
            priorityValue = 15;
            break;
          } else if (selection == "Lowest") {
            priorityValue = 16;
            break;
          } else {
            selectedPriorities.append(selection);
            availablePriorities.removeAll(selection);
            availablePriorities.removeAll("Highest");
            availablePriorities.removeAll("Lowest");
          }
        }

        if (priorityValue == -1 && !selectedPriorities.isEmpty()) {
          QString priorityString = selectedPriorities.join(", ");
          priorityValue = priorities.indexOf(priorityString);
        }

        if (priorityValue != -1) {
          slscPriorityButton->setValue(priorities[priorityValue]);
          params.putInt("SLCPriority", priorityValue);
          updateToggles();
        }
      });
      slscPriorityButton->setValue(priorities[params.getInt("SLCPriority")]);
      addItem(slscPriorityButton);

    } else if (param == "VisionTurnControl") {
      FrogPilotParamManageControl *visionTurnControlToggle = new FrogPilotParamManageControl(param, title, desc, icon, this);
      QObject::connect(visionTurnControlToggle, &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
        parentToggleClicked();
        for (auto &[key, toggle] : toggles) {
          toggle->setVisible(visionTurnControlKeys.find(key.c_str()) != visionTurnControlKeys.end());
        }
      });
      toggle = visionTurnControlToggle;
    } else if (param == "CurveSensitivity" || param == "TurnAggressiveness") {
      toggle = new FrogPilotParamValueControl(param, title, desc, icon, 1, 200, std::map<int, QString>(), this, false, "%");

    } else {
      toggle = new ParamControl(param, title, desc, icon, this);
    }

    addItem(toggle);
    toggles[param.toStdString()] = toggle;

    QObject::connect(toggle, &ToggleControl::toggleFlipped, [this]() {
      updateToggles();
    });

    QObject::connect(static_cast<FrogPilotParamValueControl*>(toggle), &FrogPilotParamValueControl::buttonPressed, [this]() {
      updateToggles();
    });

    QObject::connect(toggle, &AbstractControl::showDescriptionEvent, [this]() {
      update();
    });

    QObject::connect(static_cast<FrogPilotParamManageControl*>(toggle), &FrogPilotParamManageControl::manageButtonClicked, this, [this]() {
      update();
    });
  }

  std::set<std::string> rebootKeys = {"AlwaysOnLateral", "FireTheBabysitter", "HigherBitrate", "MuteDM", "NNFF"};
  for (const std::string &key : rebootKeys) {
    QObject::connect(toggles[key], &ToggleControl::toggleFlipped, [this]() {
      if (FrogPilotConfirmationDialog::toggle("Reboot required to take effect.", "Reboot Now", this)) {
        Hardware::reboot();
      }
    });
  }

  conditionalExperimentalKeys = {"CECurves", "CECurvesLead", "CESlowerLead", "CENavigation", "CEStopLights", "CESignal"};
  fireTheBabysitterKeys = {"NoLogging", "MuteDM", "MuteDoor", "MuteOverheated", "MuteSeatbelt", "OfflineMode"};
  laneChangeKeys = {"LaneChangeTime", "LaneDetection", "OneLaneChange"};
  lateralTuneKeys = {"AverageCurvature", "NNFF", "SteerRatio"};
  longitudinalTuneKeys = {"AccelerationProfile", "AggressiveAcceleration", "SmoothBraking", "StoppingDistance"};
  mtscKeys = {"MTSCAggressiveness"};
  qolKeys = {"DisableOnroadUploads", "HigherBitrate", "PauseLateralOnSignal", "ReverseCruise", "SetSpeedOffset"};
  speedLimitControllerKeys = {"Offset1", "Offset2", "Offset3", "Offset4", "SLCFallback", "SLCOverride", "SLCPriority"};
  visionTurnControlKeys = {"CurveSensitivity", "TurnAggressiveness"};

  QObject::connect(uiState(), &UIState::offroadTransition, this, [this](bool offroad) {
    if (!offroad) {
      updateCarToggles();
    }
  });

  QObject::connect(device(), &Device::interactiveTimeout, this, &FrogPilotControlsPanel::hideSubToggles);
  QObject::connect(parent, &SettingsWindow::closeParentToggle, this, &FrogPilotControlsPanel::hideSubToggles);
  QObject::connect(parent, &SettingsWindow::updateMetric, this, &FrogPilotControlsPanel::updateMetric);

  hideSubToggles();
  updateMetric();
}

void FrogPilotControlsPanel::updateCarToggles() {
  FrogPilotParamValueControlFloat *steerRatioToggle = static_cast<FrogPilotParamValueControlFloat*>(toggles["SteerRatio"]);
  steerRatioStock = params.getFloat("SteerRatioStock");
  steerRatioToggle->setTitle(steerRatioStock != 0 ? QString("Steer Ratio (Default: %1)").arg(steerRatioStock, 0, 'f', 2) : QString("Steer Ratio"));
  steerRatioToggle->updateControl(steerRatioStock * 0.75, steerRatioStock * 1.25, "", 10.0);
  steerRatioToggle->refresh();
}

void FrogPilotControlsPanel::updateToggles() {
  std::thread([this]() {
    paramsMemory.putBool("FrogPilotTogglesUpdated", true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    paramsMemory.putBool("FrogPilotTogglesUpdated", false);
  }).detach();
}

void FrogPilotControlsPanel::updateMetric() {
  bool previousIsMetric = isMetric;
  isMetric = params.getBool("IsMetric");

  if (isMetric != previousIsMetric) {
    double distanceConversion = isMetric ? FOOT_TO_METER : METER_TO_FOOT;
    double speedConversion = isMetric ? MILE_TO_KM : KM_TO_MILE;
    params.putInt("CESpeed", std::nearbyint(params.getInt("CESpeed") * speedConversion));
    params.putInt("CESpeedLead", std::nearbyint(params.getInt("CESpeedLead") * speedConversion));
    params.putInt("Offset1", std::nearbyint(params.getInt("Offset1") * speedConversion));
    params.putInt("Offset2", std::nearbyint(params.getInt("Offset2") * speedConversion));
    params.putInt("Offset3", std::nearbyint(params.getInt("Offset3") * speedConversion));
    params.putInt("Offset4", std::nearbyint(params.getInt("Offset4") * speedConversion));
    params.putInt("PauseLateralOnSignal", std::nearbyint(params.getInt("PauseLateralOnSignal") * speedConversion));
    params.putInt("SetSpeedOffset", std::nearbyint(params.getInt("SetSpeedOffset") * speedConversion));
    params.putInt("StoppingDistance", std::nearbyint(params.getInt("StoppingDistance") * distanceConversion));
  }

  FrogPilotParamValueControl *offset1Toggle = static_cast<FrogPilotParamValueControl*>(toggles["Offset1"]);
  FrogPilotParamValueControl *offset2Toggle = static_cast<FrogPilotParamValueControl*>(toggles["Offset2"]);
  FrogPilotParamValueControl *offset3Toggle = static_cast<FrogPilotParamValueControl*>(toggles["Offset3"]);
  FrogPilotParamValueControl *offset4Toggle = static_cast<FrogPilotParamValueControl*>(toggles["Offset4"]);
  FrogPilotParamValueControl *pauseLateralToggle = static_cast<FrogPilotParamValueControl*>(toggles["PauseLateralOnSignal"]);
  FrogPilotParamValueControl *setSpeedOffsetToggle = static_cast<FrogPilotParamValueControl*>(toggles["SetSpeedOffset"]);
  FrogPilotParamValueControl *stoppingDistanceToggle = static_cast<FrogPilotParamValueControl*>(toggles["StoppingDistance"]);

  if (isMetric) {
    offset1Toggle->setTitle("Speed Limit Offset (0-34 kph)");
    offset2Toggle->setTitle("Speed Limit Offset (35-54 kph)");
    offset3Toggle->setTitle("Speed Limit Offset (55-64 kph)");
    offset4Toggle->setTitle("Speed Limit Offset (65-99 kph)");

    offset1Toggle->setDescription("Set speed limit offset for limits between 0-34 kph.");
    offset2Toggle->setDescription("Set speed limit offset for limits between 35-54 kph.");
    offset3Toggle->setDescription("Set speed limit offset for limits between 55-64 kph.");
    offset4Toggle->setDescription("Set speed limit offset for limits between 65-99 kph.");

    offset1Toggle->updateControl(0, 150, " kph");
    offset2Toggle->updateControl(0, 150, " kph");
    offset3Toggle->updateControl(0, 150, " kph");
    offset4Toggle->updateControl(0, 150, " kph");
    pauseLateralToggle->updateControl(0, 150, " kph");
    setSpeedOffsetToggle->updateControl(0, 150, " kph");
    stoppingDistanceToggle->updateControl(0, 5, " meters");
  } else {
    offset1Toggle->setTitle("Speed Limit Offset (0-34 mph)");
    offset2Toggle->setTitle("Speed Limit Offset (35-54 mph)");
    offset3Toggle->setTitle("Speed Limit Offset (55-64 mph)");
    offset4Toggle->setTitle("Speed Limit Offset (65-99 mph)");

    offset1Toggle->setDescription("Set speed limit offset for limits between 0-34 mph.");
    offset2Toggle->setDescription("Set speed limit offset for limits between 35-54 mph.");
    offset3Toggle->setDescription("Set speed limit offset for limits between 55-64 mph.");
    offset4Toggle->setDescription("Set speed limit offset for limits between 65-99 mph.");

    offset1Toggle->updateControl(0, 99, " mph");
    offset2Toggle->updateControl(0, 99, " mph");
    offset3Toggle->updateControl(0, 99, " mph");
    offset4Toggle->updateControl(0, 99, " mph");
    pauseLateralToggle->updateControl(0, 99, " mph");
    setSpeedOffsetToggle->updateControl(0, 99, " mph");
    stoppingDistanceToggle->updateControl(0, 10, " feet");
  }

  offset1Toggle->refresh();
  offset2Toggle->refresh();
  offset3Toggle->refresh();
  offset4Toggle->refresh();
  pauseLateralToggle->refresh();
  setSpeedOffsetToggle->refresh();
  stoppingDistanceToggle->refresh();

  previousIsMetric = isMetric;
}

void FrogPilotControlsPanel::parentToggleClicked() {
  aggressiveProfile->setVisible(false);
  conditionalSpeedsImperial->setVisible(false);
  conditionalSpeedsMetric->setVisible(false);
  modelSelectorButton->setVisible(false);
  slscPriorityButton->setVisible(false);
  standardProfile->setVisible(false);
  relaxedProfile->setVisible(false);

  this->openParentToggle();
}

void FrogPilotControlsPanel::hideSubToggles() {
  aggressiveProfile->setVisible(false);
  conditionalSpeedsImperial->setVisible(false);
  conditionalSpeedsMetric->setVisible(false);
  modelSelectorButton->setVisible(true);
  slscPriorityButton->setVisible(false);
  standardProfile->setVisible(false);
  relaxedProfile->setVisible(false);

  for (auto &[key, toggle] : toggles) {
    bool subToggles = conditionalExperimentalKeys.find(key.c_str()) != conditionalExperimentalKeys.end() ||
                      fireTheBabysitterKeys.find(key.c_str()) != fireTheBabysitterKeys.end() ||
                      laneChangeKeys.find(key.c_str()) != laneChangeKeys.end() ||
                      lateralTuneKeys.find(key.c_str()) != lateralTuneKeys.end() ||
                      longitudinalTuneKeys.find(key.c_str()) != longitudinalTuneKeys.end() ||
                      mtscKeys.find(key.c_str()) != mtscKeys.end() ||
                      qolKeys.find(key.c_str()) != qolKeys.end() ||
                      speedLimitControllerKeys.find(key.c_str()) != speedLimitControllerKeys.end() ||
                      visionTurnControlKeys.find(key.c_str()) != visionTurnControlKeys.end();
    toggle->setVisible(!subToggles);
  }

  this->closeParentToggle();
}

void FrogPilotControlsPanel::hideEvent(QHideEvent *event) {
  hideSubToggles();
}
