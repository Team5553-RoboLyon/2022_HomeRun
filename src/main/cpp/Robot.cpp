// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedShooter = 0.0;
  hood.ResetEncoders();
  turret.ResetEncoder();
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
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::PutNumber("encodeur Hood", hood.GetEncoder());
  frc::SmartDashboard::PutNumber("encodeur Turret", turret.GetMeasurement());
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
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

  frc::SmartDashboard::PutNumber("Setpoint hood", 0.0);
  frc::SmartDashboard::PutNumber("Setpoint turret", 0.0);

  turret.ResetEncoder();
}

void Robot::TeleopPeriodic()
{
  double joystick = m_Joystick.GetThrottle();
  double speedHood = m_Joystick.GetY() * 0.1;
  double speedTurret = m_Joystick.GetZ() * 0.3;
  frc::SmartDashboard::PutNumber("vitesse shooter", joystick);
  frc::SmartDashboard::PutNumber("vitesse hood", speedHood);
  frc::SmartDashboard::PutNumber("vitesse turret", speedTurret);
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

  hood.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint hood", 0.0), 1.0, 57.0));
  turret.SetSetpoint(std::clamp(frc::SmartDashboard::GetNumber("Setpoint turret", 0.0), -45.0, 45.0));

  m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speedTurret);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
