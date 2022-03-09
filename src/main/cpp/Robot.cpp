// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedShooter = 0.0;
  // m_hood.ResetEncoders();
  m_turret.ResetEncoder();
}

void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::PutNumber("encodeur Hood", m_hood.GetEncoder());
  frc::SmartDashboard::PutNumber("encodeur Turret", m_turret.GetMeasurement());
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

  m_ShooterMotorLeft.SetInverted(true);
  m_ShooterMotorRight.SetInverted(false);

  m_ShooterMotorLeft.ConfigVoltageCompSaturation(11);
  m_ShooterMotorRight.ConfigVoltageCompSaturation(11);

  // a mettre dans init de m_hood et m_turret
  frc::SmartDashboard::PutNumber("Setpoint m_hood", 0.0);
  frc::SmartDashboard::PutNumber("Setpoint m_turret", 0.0);
}

void Robot::TeleopPeriodic()
{
  double joystick = m_Joystick.GetThrottle();
  frc::SmartDashboard::PutNumber("vitesse shooter", joystick);
  frc::SmartDashboard::PutNumber("encodeur 1", SPEED_TO_RPM(m_ShooterMotorRight.GetSensorCollection().GetIntegratedSensorVelocity()));
  frc::SmartDashboard::PutNumber("encodeur 2", SPEED_TO_RPM(-m_ShooterMotorLeft.GetSensorCollection().GetIntegratedSensorVelocity()));

  if (m_Joystick.GetRawButton(1))
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
    m_ShooterMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
  }
  else
  {
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ShooterMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }
  // a mettre dans le useoutput de m_turret et m_hood
  // m_hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_hood", 0.0), 1.0, 57.0));
  // m_turret.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint m_turret", 0.0), -35.0, 35.0));

  if (m_Joystick.GetRawButton(2))
  {
    m_hood.Enable();
  }
  else
  {
    m_hood.Disable();
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
