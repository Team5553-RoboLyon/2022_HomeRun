// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <spdlog/spdlog.h>

void Robot::RobotInit() {}

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
  m_NeoMotorRight.RestoreFactoryDefaults();
  m_NeoMotorRightFollower.RestoreFactoryDefaults();
  m_NeoMotorLeft.RestoreFactoryDefaults();
  m_NeoMotorLeftFollower.RestoreFactoryDefaults();

  m_NeoMotorRight.SetInverted(true);
  m_NeoMotorRightFollower.SetInverted(false);
  m_NeoMotorLeft.SetInverted(true);
  m_NeoMotorLeftFollower.SetInverted(false);

  m_NeoMotorRight.SetOpenLoopRampRate(0.2);
  m_NeoMotorRightFollower.SetOpenLoopRampRate(0.2);
  m_NeoMotorLeft.SetOpenLoopRampRate(0.2);
  m_NeoMotorLeftFollower.SetOpenLoopRampRate(0.2);
}

void Robot::TeleopPeriodic()
{
  frc::SmartDashboard::PutNumber("joystick ", m_Joystick.GetY());
  double speed = frc::SmartDashboard::GetNumber("joystick", 0.0) * 0.1;
  frc::SmartDashboard::PutNumber("vitesse bras", speed);

  m_NeoMotorRight.Set(speed);
  m_NeoMotorRightFollower.Set(speed);
  // m_NeoMotorLeft.Set(speed);
  // m_NeoMotorLeftFollower.Set(speed);

  if (m_Joystick.GetRawButton(1))
  {
    if (m_TransfertPosition)
    {
      m_TransfertSolenoid.kReverse;
      m_TransfertPosition = false;
    }
    else
    {
      m_TransfertSolenoid.kForward;
      m_TransfertPosition = true;
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
