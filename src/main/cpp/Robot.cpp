// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <spdlog/spdlog.h>

void Robot::RobotInit() {}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
  m_moteur.RestoreFactoryDefaults();
  m_moteurFollower.RestoreFactoryDefaults();

  m_moteur.SetInverted(true);
  m_moteurFollower.SetInverted(true);

  m_moteurFollower.Follow(m_moteur);

  speed = units::voltage::volt_t{0.0};
  value = 0.0;
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (m_driverController.GetAButtonPressed())
  {
    speed = speed + units::voltage::volt_t{0.1};
    value = value + 0.1;
  }

  if (m_driverController.GetBButtonPressed())
  {
    speed = speed - units::voltage::volt_t{-0.1};
    value = value - 0.1;
  }

  if (m_driverController.GetXButtonPressed())
  {
    speed = units::voltage::volt_t{0.0};
    value = 0.0;
  }

  m_moteur.SetVoltage(speed);

  frc::SmartDashboard::PutNumber("voltage", value);
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
