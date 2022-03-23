// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/ActiveFeederMotor.h"

ActiveFeederMotor::ActiveFeederMotor(Conveyor *pconveyor)
    : m_pConveyor(pconveyor)

{
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void ActiveFeederMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ActiveFeederMotor::Execute() {}

// Called once the command ends or is interrupted.
void ActiveFeederMotor::End(bool interrupted) {}

// Returns true when the command should end.
bool ActiveFeederMotor::IsFinished()
{
  return false;
}
