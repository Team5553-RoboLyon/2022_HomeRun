// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/TurnHood.h"

TurnHood::TurnHood(Hood *phood)
    : m_pHood(phood)
{
  AddRequirements(m_pHood);
}

// Called when the command is initially scheduled.
void TurnHood::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnHood::Execute()
{
  m_pHood->TurnHaut();
}

// Called once the command ends or is interrupted.
void TurnHood::End(bool interrupted)
{
  m_pHood->StopMotor();
}

// Returns true when the command should end.
bool TurnHood::IsFinished()
{
  return false;
}
