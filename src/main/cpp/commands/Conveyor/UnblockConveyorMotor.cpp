// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/UnblockConveyorMotor.h"

UnblockConveyorMotor::UnblockConveyorMotor(Conveyor *pconveyor)
    : m_pConveyor(pconveyor)

{
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void UnblockConveyorMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UnblockConveyorMotor::Execute() {}

// Called once the command ends or is interrupted.
void UnblockConveyorMotor::End(bool interrupted) {}

// Returns true when the command should end.
bool UnblockConveyorMotor::IsFinished()
{
  return false;
}
