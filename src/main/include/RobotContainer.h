// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/Joystick.h>

#include "Constants.h"
#include "subsystems/Drivetrain.h"
#include "commands/driving/Drive.h"
#include "lib/JsonConfig.h"

class RobotContainer
{
public:
  RobotContainer();

private:
  void ConfigureButtonBindings();

  Drivetrain m_Drivetrain;

  frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
  frc::Joystick m_DriverLeftJoystick{DRIVER_JOYSTICK_LEFT_ID};
};
