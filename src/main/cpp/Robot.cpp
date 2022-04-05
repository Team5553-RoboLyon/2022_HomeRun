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

  m_leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  m_leftMotorFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  m_rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  m_rightMotorFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  m_shooter.Init();

  m_turret.ResetEncoder();
  m_hood.ResetEncoders();
}

void Robot::RobotPeriodic()
{
}

void Robot::TeleopInit()
{
  m_hood.Enable();
  m_turret.Enable();
  // a mettre dans init de m_hood et m_turret
  frc::SmartDashboard::PutNumber("Setpoint m_turret", frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0));
  frc::SmartDashboard::PutNumber("Setpoint m_hood", frc::SmartDashboard::GetNumber("Setpoint m_hood", 1.0));
  m_feedingSystem.SetIntakeState(frc::DoubleSolenoid::Value::kReverse);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{

  if (m_joystickRight.GetRawButtonPressed(8))
  {
    m_hood.SetSetpoint(m_hood.GetSetpoint() + 0.5);
  }
  if (m_joystickRight.GetRawButtonPressed(7))
  {
    m_hood.SetSetpoint(m_hood.GetSetpoint() - 0.5);
  }

  if (m_joystickRight.GetRawButtonPressed(6))
  {
    m_flyingWheelsSpeed += 0.05;
  }
  if (m_joystickRight.GetRawButtonPressed(5))
  {
    m_flyingWheelsSpeed -= 0.05;
  }

  if (m_joystickLeft.GetRawButton(1))
  {
    m_feedingSystem.ActivateConveyor();
    m_feedingSystem.ActivateIntake();
  }
  else
  {
    m_feedingSystem.StopConveyor();
    m_feedingSystem.StopIntake();
  }

  if (m_joystickRight.GetRawButton(1))
  {
    m_feedingSystem.ActivateFeeder();
  }
  else
  {
    m_feedingSystem.StopFeeder();
  }

  if (m_joystickRight.GetRawButtonPressed(2))
  {
    m_feedingSystem.SetIntakeState(m_feedingSystem.GetIntakeState() == frc::DoubleSolenoid::Value::kForward ? frc::DoubleSolenoid::Value::kReverse : frc::DoubleSolenoid::Value::kForward);
  }

  std::clamp(m_flyingWheelsSpeed, 0.0, SHOOTER_VOLTAGE_COMPENSATION);

  m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));
  m_turret.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0), -35.0, 35.0));

  frc::SmartDashboard::PutNumber("Setpoint Hood", m_hood.GetSetpoint());
  frc::SmartDashboard::PutNumber("Speed Shooter", m_flyingWheelsSpeed);
  frc::SmartDashboard::PutNumber("Setpoint Turret", m_turret.GetSetpoint());
  frc::SmartDashboard::PutNumber("Photonvision Target number", m_camera.GetLatestResult().GetTargets().size());
  if (m_camera.GetLatestResult().HasTargets())
  {
    frc::SmartDashboard::PutNumber("Pitch from Photonvision", m_camera.GetLatestResult().GetBestTarget().GetPitch());
    frc::SmartDashboard::PutNumber("Yaw from Photonvision", m_camera.GetLatestResult().GetBestTarget().GetYaw());
  }

  m_shooter.Set(m_flyingWheelsSpeed);

  if (m_joystickLeft.GetRawButtonPressed(2))
  {
    if (m_camera.GetLatestResult().HasTargets())
    {
      // Open a file for logging
      std::ofstream file;
      file.open("/home/lvuser/ShooterLogFile.csv", std::ios_base::app);
      file << m_camera.GetLatestResult().GetBestTarget().GetPitch() << "," << m_hood.GetSetpoint() << "," << m_flyingWheelsSpeed << "\n";
    }
    else
    {
      spdlog::error("No target detected. Couldn't log data");
    }
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