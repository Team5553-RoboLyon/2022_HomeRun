// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/ActiveIntakeMotor.h"

ActiveIntakeMotor::ActiveIntakeMotor(Intake *pintake)
    : m_pIntake(pintake)
{
  AddRequirements(m_pIntake);
}

void ActiveIntakeMotor::Initialize() {}

void ActiveIntakeMotor::Execute() { m_pIntake->ActiveMotor(); }

void ActiveIntakeMotor::End(bool interrupted) { m_pIntake->StopMotor(); }

bool ActiveIntakeMotor::IsFinished()
{
  return false;
}
