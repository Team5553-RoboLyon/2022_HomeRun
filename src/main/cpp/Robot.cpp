// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedFeeder = 0.0;
  m_speedConveyor = 0.0;
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
  // frc::SmartDashboard::PutNumber("Coefficient de vitesse", std::abs(m_Joystick.GetThrottle()));
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
  m_ConveyorMotor.SetInverted(false);
  m_FeederMotorLeft.SetInverted(false);
  m_FeederMotorRight.SetInverted(true);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  // frc::SmartDashboard::PutNumber("Coefficient de vitesse conveyor", std::abs(m_JoystickRight.GetThrottle()));
  // frc::SmartDashboard::PutNumber("Coefficient de vitesse feeder", std::abs(m_JoystickLeft.GetThrottle()));
  m_speedFeeder = frc::SmartDashboard::GetNumber("vitesse feeder", 0.0);
  m_speedConveyor = frc::SmartDashboard::GetNumber("vitesse conveyor", 0.0);

  if (m_JoystickLeft.GetRawButton(1))
  {
    m_ConveyorMotor.Set(m_speedConveyor);
  }
  else
  {
    m_ConveyorMotor.Set(0.0);
  }
  if (m_JoystickRight.GetRawButton(1))
  {
    m_FeederMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, m_speedFeeder);
    m_FeederMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, m_speedFeeder);
  }
  else
  {
    m_FeederMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_FeederMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
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
