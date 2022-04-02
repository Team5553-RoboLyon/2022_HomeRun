// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/ActiveConveyorMotor.h"

ActiveConveyorMotor::ActiveConveyorMotor(Conveyor *pconveyor)
    : m_pConveyor(pconveyor)
{
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void ActiveConveyorMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ActiveConveyorMotor::Execute()
{
  m_pConveyor->ActiveConveyorMotor();
}

// Called once the command ends or is interrupted.
void ActiveConveyorMotor::End(bool interrupted)
{
  m_pConveyor->StopConveyorMotor();
}

// Returns true when the command should end.
bool ActiveConveyorMotor::IsFinished()
{
  return false;
}
