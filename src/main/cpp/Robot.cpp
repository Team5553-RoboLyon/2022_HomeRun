// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedShooter = 0.0;
}

void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::PutNumber("encodeur Hood", m_hood.GetEncoder());
  frc::SmartDashboard::PutNumber("encoderu hood copy", m_hoodcopy.GetEncoder());
}

void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
  m_ShooterMotorLeft.ConfigFactoryDefault();
  m_ShooterMotorRight.ConfigFactoryDefault();
  m_ShooterMotorLeftFollower.ConfigFactoryDefault();
  m_ShooterMotorRightFollower.ConfigFactoryDefault();

  m_ShooterMotorLeft.SetInverted(false);
  m_ShooterMotorRight.SetInverted(true);
  m_ShooterMotorRightFollower.SetInverted(true);
  m_ShooterMotorLeftFollower.SetInverted(false);

  m_ShooterMotorLeft.ConfigVoltageCompSaturation(11);
  m_ShooterMotorRight.ConfigVoltageCompSaturation(11);
  m_ShooterMotorLeftFollower.ConfigVoltageCompSaturation(11);
  m_ShooterMotorRightFollower.ConfigVoltageCompSaturation(11);

  m_ShooterMotorLeft.Follow(m_ShooterMotorRight);
  m_ShooterMotorLeftFollower.Follow(m_ShooterMotorRight);
  m_ShooterMotorRightFollower.Follow(m_ShooterMotorRight);

  // a mettre dans init de m_hood et m_turret
  frc::SmartDashboard::PutNumber("Setpoint m_hood", frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0));
  frc::SmartDashboard::PutNumber("vitesse shooter", 0.0);
  m_hood.ResetEncoders();
  m_hoodcopy.ResetEncoders();
}

void Robot::TeleopPeriodic()
{
  double joystick = frc::SmartDashboard::GetNumber("vitesse shooter", 0.0);
  frc::SmartDashboard::PutNumber("encodeur 1", SPEED_TO_RPM(m_ShooterMotorRight.GetSensorCollection().GetIntegratedSensorVelocity()));
  frc::SmartDashboard::PutNumber("encodeur 2", SPEED_TO_RPM(-m_ShooterMotorLeft.GetSensorCollection().GetIntegratedSensorVelocity()));

  if (m_Joystick.GetRawButton(1))
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
  }
  else
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }
  m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));
  m_hoodcopy.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));

  // if (m_Joystick.GetRawButton(2))
  // {
  //   m_hood.Disable();
  // }
  // else
  // {
  //   m_hood.Enable();
  // }
}
void Robot::TestInit()
{
  frc::LiveWindow::SetEnabled(false);
  spdlog::info("testinit");
  // m_hood.Enable();
}

void Robot::TestPeriodic()
{
  spdlog::info("TestPeriodic");

  // spdlog::info(m_hood.MagnetDetected());
  if (m_hood.m_state != Hood::state::Init)
  {
    m_hood.Disable();
  }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
