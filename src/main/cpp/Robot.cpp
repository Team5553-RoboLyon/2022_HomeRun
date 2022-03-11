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

  m_shooter.Init();

  m_turret.ResetEncoder();
  m_hood.ResetEncoders();
}

void Robot::RobotPeriodic()
{
}

void Robot::TeleopInit()
{
  m_solenoidClimber.Set(frc::DoubleSolenoid::Value::kForward);
  m_solenoidRotatingArms.Set(frc::DoubleSolenoid::Value::kForward);
  m_hood.Enable();
  m_turret.Enable();
  // a mettre dans init de m_hood et m_turret
  frc::SmartDashboard::PutNumber("Setpoint m_turret", frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0));
  frc::SmartDashboard::PutNumber("Setpoint m_hood", frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0));
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
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

  frc::SmartDashboard::PutNumber("shooter output", m_joystickLeft.GetThrottle());
  if (m_joystickLeft.GetRawButton(2))
  {
    m_shooter.Set(m_joystickLeft.GetThrottle());
  }
  else
  {
    m_shooter.Set(0.0);
  }
  if (m_joystickRight.GetRawButton(5))
  {
    m_hood.Enable();
  }
  else
  {
    m_hood.Disable();
  }

  m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));
  m_turret.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0), -35.0, 35.0));
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