// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/UnblockIntakeMotor.h"

UnblockIntakeMotor::UnblockIntakeMotor(Intake *pintake)
    : m_pIntake(pintake)
{
  AddRequirements(m_pIntake);
}

void UnblockIntakeMotor::Initialize() {}

void UnblockIntakeMotor::Execute() { m_pIntake->UnblockMotor(); }

void UnblockIntakeMotor::End(bool interrupted) { m_pIntake->StopMotor(); }

bool UnblockIntakeMotor::IsFinished()
{
  return false;
}
