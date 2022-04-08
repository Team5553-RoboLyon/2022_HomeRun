// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/UnblockShooter.h"

UnblockShooter::UnblockShooter(Shooter *shooter)
{
  m_pShooter = shooter;
  AddRequirements(m_pShooter);
}

// Called when the command is initially scheduled.
void UnblockShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UnblockShooter::Execute()
{
  m_pShooter->SetSpeed(SHOOTER_UNBLOCK_SPEED);
}

// Called once the command ends or is interrupted.
void UnblockShooter::End(bool interrupted)
{
  m_pShooter->SetSpeed(0.0);
}

// Returns true when the command should end.
bool UnblockShooter::IsFinished()
{
  return false;
}
