// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/DebloquedIntakeMotor.h"

DebloquedIntakeMotor::DebloquedIntakeMotor(Intake *pintake)
    : m_pIntake(pintake)
{
  AddRequirements(m_pIntake);
}

void DebloquedIntakeMotor::Initialize() {}

void DebloquedIntakeMotor::Execute() { m_pIntake->DebloquedMotor(); }

void DebloquedIntakeMotor::End(bool interrupted) { m_pIntake->StopMotor(); }

bool DebloquedIntakeMotor::IsFinished()
{
  return false;
}
