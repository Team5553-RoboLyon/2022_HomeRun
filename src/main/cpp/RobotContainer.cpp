// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer()
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  m_Drivetrain.SetDefaultCommand(Drive([this]
                                       { return -m_DriverRightJoystick.GetY(); },
                                       [this]
                                       { return m_DriverRightJoystick.GetZ(); },
                                       [this]
                                       { return m_DriverLeftJoystick.GetX(); },
                                       &m_Drivetrain));
}

void RobotContainer::ConfigureButtonBindings()
{
}
