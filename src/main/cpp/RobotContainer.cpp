// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer()
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  // frc::Joystick *joystick1 = (JsonConfig::GetConfig()["invertJoysticks"].get<bool>() ? &m_DriverRightJoystick : &m_DriverLeftJoystick);
  // frc::Joystick *joystick2 = (JsonConfig::GetConfig()["invertJoysticks"].get<bool>() ? &m_DriverLeftJoystick : &m_DriverRightJoystick);
  m_Drivetrain.SetDefaultCommand(Drive([=]
                                       { return -m_DriverLeftJoystick.GetY(); },
                                       [=]
                                       { return m_DriverRightJoystick.GetZ(); },
                                       [=]
                                       { return m_DriverRightJoystick.GetX(); },
                                       &m_Drivetrain));
}

void RobotContainer::ConfigureButtonBindings()
{
}
