// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/AutoMoovToBall.h"

AutoMoovToBall::AutoMoovToBall(Drivetrain *drivetrain)
{
  m_pDrivetrain = drivetrain;
  AddRequirements(m_pDrivetrain);
}

// Called when the command is initially scheduled.
void AutoMoovToBall::Initialize()
{
  m_count = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutoMoovToBall::Execute()
{
  m_pDrivetrain->Drive(DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED);
  m_count += 1;
}

// Called once the command ends or is interrupted.
void AutoMoovToBall::End(bool interrupted)
{
  m_pDrivetrain->Stop();
}

// Returns true when the command should end.
bool AutoMoovToBall::IsFinished()
{
  return (m_count > AUTO_TAKING_BALL_TIME);
}
