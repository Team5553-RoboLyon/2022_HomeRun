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

void Robot::RobotPeriodic()
{
}

void Robot::TeleopInit()
{
  m_solenoidIntake.Set(frc::DoubleSolenoid::Value::kForward);
  m_solenoidClimber.Set(frc::DoubleSolenoid::Value::kForward);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  double offset = 0.035;
  frc::SmartDashboard::PutNumber("Offset", offset);
  bool isAnyPTOEnabled = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse;

  double speedCoefficient = isAnyPTOEnabled ? 0.4 : 0.2;
  double speedRight = utils::Deadband(-m_joystickRight.GetY(), 0.15) * speedCoefficient;
  double speedLeft = utils::Deadband(-m_joystickLeft.GetY(), 0.15) * speedCoefficient;
  frc::SmartDashboard::PutNumber("speedRight", speedRight);
  frc::SmartDashboard::PutNumber("speedLeft", speedLeft);

  if (m_joystickLeft.GetRawButtonPressed(1))
  {
    frc::DoubleSolenoid::Value value = m_solenoidIntake.Get() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward;
    m_solenoidIntake.Set(value);
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

  m_leftMotor.Set(speedLeft);
  m_rightMotor.Set(speedRight);

  m_OmniMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, utils::Deadband(m_joystickLeft.GetX()));

  if (m_joystickLeft.GetRawButtonPressed(2))
  {
    frc::DoubleSolenoid::Value value = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward;
    m_solenoidClimber.Set(value);
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