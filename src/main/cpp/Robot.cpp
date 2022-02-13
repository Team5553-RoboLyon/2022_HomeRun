// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_setpoint = 0.0;
  m_Encoder.SetPosition(0);
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
  frc::SmartDashboard::PutNumber("Coefficient de vitesse", std::abs(m_Joystick.GetThrottle()));
  frc::SmartDashboard::PutNumber("Position", m_Encoder.GetPosition());
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
  m_ClimberMotor.SetInverted(false);
  m_ClimberMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  m_ClimberMotor.EnableVoltageCompensation(10);
  m_ClimberMotor.SetOpenLoopRampRate(0.2);

  frc::SmartDashboard::PutNumber("Setpoint", m_setpoint);
  frc::SmartDashboard::PutNumber("Coefficient de vitesse", std::abs(m_Joystick.GetThrottle()));
  frc::SmartDashboard::PutNumber("Position", m_Encoder.GetPosition());
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  m_setpoint = std::clamp(frc::SmartDashboard::GetNumber("Setpoint", 0.0), 0.0, MAX_HEIGHT_CLIMBER - 0.5);
  double error = m_setpoint - m_Encoder.GetPosition();
  frc::SmartDashboard::PutNumber("Erreur", error);
  double derivative = (error - m_lastError) / .02;
  frc::SmartDashboard::PutNumber("Derivative", derivative);
  m_integrative += (error * 0.02);
  frc::SmartDashboard::PutNumber("Integrative", m_integrative);
  double speed = std::abs(m_Joystick.GetThrottle()) * std::clamp((0.1 * error + 0.001 * m_integrative + 0.01 * derivative), -1.0, 1.0);
  frc::SmartDashboard::PutNumber("Speed", speed);
  m_lastError = error;
  m_ClimberMotor.Set(speed);
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
