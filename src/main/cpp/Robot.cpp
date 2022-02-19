// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <spdlog/spdlog.h>

void Robot::RobotInit()
{

  m_leftMotor.RestoreFactoryDefaults();
  m_leftMotorFollower.RestoreFactoryDefaults();
  m_rightMotor.RestoreFactoryDefaults();
  m_rightMotorFollower.RestoreFactoryDefaults();

  m_leftMotorFollower.Follow(m_leftMotor);
  m_rightMotorFollower.Follow(m_rightMotor);
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
  frc::SmartDashboard::PutNumber("Speed PTO", 0.0);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (m_joystick.GetRawButton(1))
  {
    m_leftMotor.Set(frc::SmartDashboard::GetNumber("Speed PTO", 0.0));
    m_rightMotor.Set(frc::SmartDashboard::GetNumber("Speed PTO", 0.0));
  }
  else
  {
    m_leftMotor.Set(0);
    m_rightMotor.Set(0);
  }

  if (m_joystick.GetRawButtonPressed(2))
  {
    frc::DoubleSolenoid::Value value = m_solenoid.Get() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward;
    m_solenoid.Set(value);
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
