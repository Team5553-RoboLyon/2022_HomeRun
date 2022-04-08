// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/UnblockIntakeMotor.h"

UnblockIntakeMotor::UnblockIntakeMotor(Intake *pintake)
    : m_pIntake(pintake)
{
  spdlog::trace("UnblockIntakeMotor::UnblockIntakeMotor()");
  AddRequirements(m_pIntake);
}

void UnblockIntakeMotor::Initialize()
{
  spdlog::trace("UnblockIntakeMotor::Initialize()");
  m_pIntake->Open();
}

void UnblockIntakeMotor::Execute()
{
  spdlog::trace("UnblockIntakeMotor::Execute()");
  m_pIntake->UnblockMotor();
}

void UnblockIntakeMotor::End(bool interrupted)
{
  spdlog::trace("UnblockIntakeMotor::End()");
  m_pIntake->StopMotor();
}

bool UnblockIntakeMotor::IsFinished()
{
  return false;
}
