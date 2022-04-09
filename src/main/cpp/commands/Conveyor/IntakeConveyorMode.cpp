// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/IntakeConveyorMode.h"

IntakeConveyorMode::IntakeConveyorMode(Conveyor *pconveyor)
    : m_pConveyor(pconveyor)
{
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void IntakeConveyorMode::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeConveyorMode::Execute()
{
  m_pConveyor->ActiveConveyorMotor();
  m_pConveyor->UnblockFeedingMotor();
}

// Called once the command ends or is interrupted.
void IntakeConveyorMode::End(bool interrupted)
{
  m_pConveyor->StopAllMotors();
}

// Returns true when the command should end.
bool IntakeConveyorMode::IsFinished()
{
  return false;
}
