// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/UnblockFeederMotor.h"

UnblockFeederMotor::UnblockFeederMotor(Conveyor *pconveyor)
    : m_pConveyor(pconveyor)

{
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void UnblockFeederMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UnblockFeederMotor::Execute()
{
  m_pConveyor->UnblockFeedingMotor();
}

// Called once the command ends or is interrupted.
void UnblockFeederMotor::End(bool interrupted)
{
  m_pConveyor->StopFeedingMotor();
}

// Returns true when the command should end.
bool UnblockFeederMotor::IsFinished()
{
  return false;
}
