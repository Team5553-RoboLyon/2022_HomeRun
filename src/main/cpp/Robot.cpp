// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <spdlog/spdlog.h>

void Robot::RobotInit()
{
}

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
void Robot::DisabledInit()
{
}

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
  m_TurretEncoder.Reset();
  m_TurretMotor.SetInverted(false);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (m_joystick.GetRawButton(1))
  {
    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.5);
  }
  frc::SmartDashboard::PutNumber("encodeur turret", m_TurretEncoder.Get().value());
  double encoder = frc::SmartDashboard::GetNumber("encodeur turret", 0.0);
  spdlog::info(m_TurretEncoder.Get());
  double speedTurret = m_joystick.GetZ() * 0.5;
  frc::SmartDashboard::PutNumber("Speed Turret", speedTurret);
  if (m_joystick.GetRawButtonPressed(2))
  {
    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speedTurret);
  }

  if (encoder >= 10.05) // 10.05 pour 0.5
  {
    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }
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