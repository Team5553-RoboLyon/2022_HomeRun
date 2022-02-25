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
#if IS_CLIMBER_PID
  m_setpoint = 0.0;
  m_encoderClimber.Reset();
  m_integrative = 0.0;
  m_lastError = 0.0;
  frc::SmartDashboard::PutNumber("setpoint", 0.0);
  frc::SmartDashboard::PutNumber("speedCoef", 0.0);
#endif

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
  m_solenoidClimber.Set(frc::DoubleSolenoid::Value::kForward);
  m_solenoidRotatingArms.Set(frc::DoubleSolenoid::Value::kForward);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  double offset = m_joystickLeft.GetThrottle() + m_joystickRight.GetThrottle() * 0.1;
  frc::SmartDashboard::PutNumber("Offset", offset);
  bool isAnyPTOEnabled = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse ||
                         m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kReverse;

  double speedCoefficientLeft = m_solenoidClimber.Get() == frc::DoubleSolenoid::Value::kReverse ? 0.4 : 0.2;
  double speedCoefficientRight = m_solenoidRotatingArms.Get() == frc::DoubleSolenoid::Value::kReverse ? 0.8 : 0.2;
  double speedRight = utils::Deadband(-m_joystickRight.GetY(), 0.15) * speedCoefficientRight;
  double speedLeft = utils::Deadband(-m_joystickLeft.GetY(), 0.15) * speedCoefficientLeft;
  frc::SmartDashboard::PutNumber("speedRight", speedRight);
  frc::SmartDashboard::PutNumber("speedLeft", speedLeft);

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
    m_leftMotor.Set(speedLeft + offset);
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

#if IS_CLIMBER_PID
  frc::SmartDashboard::PutNumber("encodeur climber", m_encoderClimber.Get().value());
  frc::SmartDashboard::PutNumber("error", m_error);
  frc::SmartDashboard::PutNumber("integrative", m_integrative);
  frc::SmartDashboard::PutNumber("derivative", m_derivative);
  frc::SmartDashboard::PutNumber("speedClimber_PID", m_speedPID);
  m_speedCoef = frc::SmartDashboard::GetNumber("speedCoef", 0.0);
  m_setpoint = frc::SmartDashboard::GetNumber("setpoint", 0.0);
  m_error = m_setpoint - m_encoderClimber.Get().value();
  m_integrative += (m_error * 0.02);
  m_derivative = (m_error - m_lastError) / .02;
  m_lastError = m_error;
  m_speedPID = std::abs(m_speedCoef) * std::clamp(kP * m_error + kI * m_integrative + kD * m_derivative, -1.0, 1.0);
#endif
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