// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/TurnHoodBas.h"

TurnHoodBas::TurnHoodBas(Hood *phood)
    : m_pHood(phood)
{
  AddRequirements(m_pHood);
}

// Called when the command is initially scheduled.
void TurnHoodBas::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnHoodBas::Execute() {}

// Called once the command ends or is interrupted.
void TurnHoodBas::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnHoodBas::IsFinished()
{
  return false;
}
