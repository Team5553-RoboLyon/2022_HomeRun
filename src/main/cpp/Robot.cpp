// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <spdlog/spdlog.h>

namespace utils
{
  double Deadband(double value, double deadband = 0.1)
  {
    if (std::abs(value) < deadband)
    {
      return 0;
    }

    if (value >= 0)
    {
      return (value - deadband) / (1.0 - deadband);
    }
    else
    {
      return (value + deadband) / (1.0 - deadband);
    }
  }
} // namespace utils

void Robot::RobotInit()
{

  m_leftMotor.RestoreFactoryDefaults();
  m_leftMotorFollower.RestoreFactoryDefaults();
  m_rightMotor.RestoreFactoryDefaults();
  m_rightMotorFollower.RestoreFactoryDefaults();

  m_leftMotorFollower.Follow(m_leftMotor);
  m_rightMotorFollower.Follow(m_rightMotor);

  m_leftMotor.SetInverted(true);
  m_leftMotorFollower.SetInverted(true);
  m_rightMotor.SetInverted(false);
  m_rightMotorFollower.SetInverted(false);
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
  m_solenoidClimber.Set(frc::DoubleSolenoid::Value::kForward);
  m_solenoidRotatingArms.Set(frc::DoubleSolenoid::Value::kForward);
  m_solenoidClimber.GetFwdChannel();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  bool isAnyPTOEnabled = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse ||
                         m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kReverse;

  double speedCoefficientLeft = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse ? 0.4 : 0.2;
  double speedCoefficientRight = m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kReverse ? 0.1 : 0.2;
  double speedRight = utils::Deadband(-m_joystickRight.GetY(), 0.15) * speedCoefficientRight;
  double speedLeft = utils::Deadband(-m_joystickLeft.GetY(), 0.15) * speedCoefficientLeft;

  if (m_joystickLeft.GetRawButtonPressed(1))
  {
    frc::DoubleSolenoid::Value value = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward;
    m_solenoidClimber.Set(value);
  }

  if (m_joystickRight.GetRawButtonPressed(1))
  {
    frc::DoubleSolenoid::Value value = m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward;
    m_solenoidRotatingArms.Set(value);
  }

  if (m_joystickRight.GetRawButtonPressed(2))
  {
    if (m_compressor.Enabled())
    {
      m_compressor.Disable();
    }
    else
    {
      m_compressor.EnableDigital();
    }
  }

  if (m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse)
  {
    m_leftMotor.Set(speedLeft);
  }

  if (m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kReverse)
  {
    m_rightMotor.Set(-speedRight);
  }

  if (!isAnyPTOEnabled)
  {
    m_leftMotor.Set(speedLeft);
    m_rightMotor.Set(speedRight);
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