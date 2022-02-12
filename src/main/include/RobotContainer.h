// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/DriverStation.h>
#include "lib/RobotError.h"

#include "Constants.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Climber.h"
#include "subsystems/Intake.h"
#include "commands/driving/Drive.h"
#include "commands/Climber/ClimberActiveMotor.h"
#include "lib/JsonConfig.h"

#include "commands/tests/DrivetrainTest.h"

class RobotContainer
{
public:
  RobotContainer();
  void StartTests();

private:
  void ConfigureButtonBindings();

  Drivetrain m_Drivetrain;
  Climber m_Climber;
  Intake m_Intake;

  frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
  frc::Joystick m_DriverLeftJoystick{DRIVER_JOYSTICK_LEFT_ID};

  frc2::JoystickButton m_ThrottleLeft{&m_DriverLeftJoystick, 1};
  // frc2::Trigger m_ThrottleLeft{[this]
  //                              { return m_DriverRightJoystick.GetThrottle(); }};
};
