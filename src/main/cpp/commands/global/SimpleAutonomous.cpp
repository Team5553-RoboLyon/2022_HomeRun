// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/global/SimpleAutonomous.h"

SimpleAutonomous::SimpleAutonomous(Drivetrain *drivetrain)
{
  m_pDrivetrain = drivetrain;
  AddRequirements(m_pDrivetrain);
}

// Called when the command is initially scheduled.
void SimpleAutonomous::Initialize()
{
  spdlog::error("RobotContainer::AutonomousInit()");
  m_count = 0;
  m_pDrivetrain->GetGearbox()->InitTeleopPeriod();
  m_pDrivetrain->Enable();
  m_pDrivetrain->Drive(DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED);
}

// Called repeatedly when this Command is scheduled to run
void SimpleAutonomous::Execute()
{
}

// Called once the command ends or is interrupted.
void SimpleAutonomous::End(bool interrupted)
{
  spdlog::error("end");
  m_pDrivetrain->Drive(0.0, 0.0);
}

// Returns true when the command should end.
bool SimpleAutonomous::IsFinished()
{
  m_count += 1;
  if (m_count < 75)
  {
    return false;
  }
  else
  {
    return true;
  }
}
