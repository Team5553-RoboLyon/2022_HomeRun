// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

#define MAX_HEIGHT_CLIMBER 56.4 // In rotations

void Robot::RobotInit()
{
  m_speedIntake = 0.0;
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
  m_IntakeMotor.SetInverted(true);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  frc::SmartDashboard::PutNumber("vitesse Intake", m_Joystick.GetThrottle());
  frc::SmartDashboard::PutNumber("valeur intake", m_IntakeSolenoid.Get());
  double speedIntake = frc::SmartDashboard::GetNumber("vitesse Intake", 0.0);

  // m_FeederMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speedFeeder);
  // m_FeederMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speedFeeder);
  if (m_Joystick.GetRawButton(1))
  {
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speedIntake);
  }
  else
  {
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }

  if (m_Joystick.GetRawButton(2))
  {
    {
      m_IntakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }

    if (m_Joystick.GetRawButton(3))
    {
      m_IntakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
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
