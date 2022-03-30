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
  m_ShooterMotor.SetInverted(false);
  m_ShooterMotorFollower.SetInverted(true);

  m_ShooterMotorFollower.Follow(m_ShooterMotor);

  m_intakeMotor.SetInverted(false);
  m_conveyorMotor.SetInverted(false);
  m_feederMotor.SetInverted(true);
}

void Robot::RobotPeriodic()
{
}

void Robot::TeleopInit()
{
  m_solenoidIntake.Set(frc::DoubleSolenoid::Value::kForward);
  frc::SmartDashboard::PutNumber("speed_Feeder", 0.0);
  frc::SmartDashboard::PutNumber("speed_Conveyor", 0.0);
  frc::SmartDashboard::PutNumber("speed_Shooter", 0.0);
  frc::SmartDashboard::PutNumber("speed_Intake", 0.0);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (m_joystickLeft.GetRawButton(1))
  {
    m_ShooterMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frc::SmartDashboard::GetNumber("speed_Shooter", 0.0));
  }
  else
  {
    m_ShooterMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }

  if (m_joystickRight.GetRawButtonPressed(1))
  {
    m_solenoidIntake.Get() == frc::DoubleSolenoid::Value::kForward ? m_solenoidIntake.Set(frc::DoubleSolenoid::Value::kReverse) : m_solenoidIntake.Set(frc::DoubleSolenoid::Value::kForward);
  }

  if (m_joystickRight.GetRawButton(2))
  {
    m_intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frc::SmartDashboard::GetNumber("speed_Intake", 0.0));
  }
  else
  {
    m_intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }

  if (m_joystickLeft.GetRawButton(2))
  {
    m_conveyorMotor.Set(frc::SmartDashboard::GetNumber("speed_Conveyor", 0.0));
  }
  else
  {
    m_conveyorMotor.Set(0.0);
  }

  if (m_joystickLeft.GetRawButton(3))
  {
    m_feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frc::SmartDashboard::GetNumber("speed_Feeder", 0.0));
  }
  else
  {
    m_feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
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