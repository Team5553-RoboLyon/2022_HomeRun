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

  m_moteur.SetSmartCurrentLimit(40);
  m_moteurFollower.SetSmartCurrentLimit(40);

  m_moteurFollower.Follow(m_moteur);

  m_speed = 0.0;
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (m_driverController.GetAButtonPressed())
  {
    m_speed += 0.1;
  }

  if (m_driverController.GetBButtonPressed())
  {
    m_speed -= 0.1;
  }

  if (m_driverController.GetXButtonPressed())
  {
    m_speed = 0.0;
  }
  m_speed = std::clamp(m_speed, -12.0, 12.0);
  m_moteur.SetVoltage(units::voltage::volt_t{m_speed});
  int error = m_moteur.GetStickyFaults();
  int errorFollow = m_moteurFollower.GetStickyFaults();
  frc::SmartDashboard::PutNumber("voltage", m_speed);
  frc::SmartDashboard::PutNumber("error", error);
  frc::SmartDashboard::PutNumber("errorFollower", errorFollow);
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
