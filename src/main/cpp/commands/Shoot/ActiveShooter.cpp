// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/ActiveShooter.h"

ActiveShooter::ActiveShooter(Shooter *pshooter)
    : m_pShooter(pshooter)
{
  AddRequirements(m_pShooter);
}

// Called when the command is initially scheduled.
void ActiveShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ActiveShooter::Execute()
{
  ActiveShooter(m_pShooter).Schedule();
  // m_pShooter->Shoot();
}

// Called once the command ends or is interrupted.
void ActiveShooter::End(bool interrupted)
{
  m_pShooter->SetSpeed(0.0);
}

// Returns true when the command should end.
bool ActiveShooter::IsFinished()
{
  return false;
}
