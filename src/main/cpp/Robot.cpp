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

  m_leftMotor.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);
  m_leftMotorFollower.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);
  m_rightMotor.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);
  m_rightMotorFollower.SetSmartCurrentLimit(DRIVETRAIN_CURRENT_LIMIT);

  m_shooter.Init();

  m_turret.ResetEncoder();
  m_hood.ResetEncoders();
}

void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::TeleopInit()
{
  m_turret.Enable();
  // a mettre dans init de m_hood et m_turret
  m_feedingSystem.SetIntakeState(frc::DoubleSolenoid::Value::kReverse);
#if TURRET_PID_CALIBRATE_MODE
  frc::SmartDashboard::PutNumber("Turret P", frc::SmartDashboard::GetNumber("Turret P", TURRET_PID_P));
  frc::SmartDashboard::PutNumber("Turret I", frc::SmartDashboard::GetNumber("Turret I", TURRET_PID_I));
  frc::SmartDashboard::PutNumber("Turret D", frc::SmartDashboard::GetNumber("Turret D", TURRET_PID_D));
  frc::SmartDashboard::PutNumber("Setpoint Turret", m_turret.GetSetpoint());
#endif

#if HOOD_PID_CALIBRATE_MODE
  frc::SmartDashboard::PutNumber("Hood P", frc::SmartDashboard::GetNumber("Hood P", HOOD_PID_P));
  frc::SmartDashboard::PutNumber("Hood I", frc::SmartDashboard::GetNumber("Hood I", HOOD_PID_I));
  frc::SmartDashboard::PutNumber("Hood D", frc::SmartDashboard::GetNumber("Hood D", HOOD_PID_D));
  frc::SmartDashboard::PutNumber("Setpoint Hood", m_hood.GetSetpoint());
#endif

  m_hood.ResetController();
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
#if TURRET_PID_CALIBRATE_MODE
  m_turret.SetPID(frc::SmartDashboard::GetNumber("Turret P", 0.0), frc::SmartDashboard::GetNumber("Turret I", 0.0), frc::SmartDashboard::GetNumber("Turret D", 0.0));
#endif

#if HOOD_PID_CALIBRATE_MODE
  m_hood.SetPID(frc::SmartDashboard::GetNumber("Hood P", 0.0), frc::SmartDashboard::GetNumber("Hood I", 0.0), frc::SmartDashboard::GetNumber("Hood D", 0.0));
#endif

  std::clamp(m_flyingWheelsSpeed, 0.0, SHOOTER_VOLTAGE_COMPENSATION);

  m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint Hood", 0.0), 1.0, 57.0));

#if !HOOD_PID_CALIBRATE_MODE
  frc::SmartDashboard::PutNumber("Setpoint Hood", m_hood.GetSetpoint());
#endif
  frc::SmartDashboard::PutNumber("Speed Shooter", m_flyingWheelsSpeed);
#if !TURRET_PID_CALIBRATE_MODE
  frc::SmartDashboard::PutNumber("Setpoint Turret", m_turret.GetSetpoint());
#endif
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
      file.close();
      spdlog::info("Logged to file, {}, {}, {}", m_camera.GetLatestResult().GetBestTarget().GetPitch(), m_hood.GetSetpoint(), m_flyingWheelsSpeed);
    }
    else
    {
      spdlog::error("No target detected. Couldn't log data");
    }
  }

#if USE_CAMERA_TO_MOVE_TURRET
  if (m_camera.GetLatestResult().HasTargets())
  {
    m_BufferYaw[m_BufferCount] = m_camera.GetLatestResult().GetBestTarget().GetYaw();
  }
  m_BufferCount = (m_BufferCount + 1) % BUFFER_SIZE;

  std::partial_sort_copy(&m_BufferYaw[0], &m_BufferYaw[BUFFER_SIZE - 1], &m_BufferYawSorted[0],
                         &m_BufferYawSorted[BUFFER_SIZE - c1]);
  m_turret.SetClampedSetpoint(m_turret.GetMeasurement() +
                              m_BufferYawSorted[(int)(BUFFER_SIZE / 2)]);

#elif !DISABLE_TURRET
  if (m_joystickRight.GetRawButtonPressed(3))
  {
    m_turret.SetClampedSetpoint(frc::SmartDashboard::GetNumber("Setpoint Turret", 0.0));
  }
#else
  m_turret.Disable();
#endif

  if (m_joystickLeft.GetRawButtonPressed(10))
  {
    m_compressor.Enabled() ? m_compressor.Disable() : m_compressor.EnableDigital();
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