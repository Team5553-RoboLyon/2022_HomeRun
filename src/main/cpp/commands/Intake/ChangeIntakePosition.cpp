// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/ChangeIntakePosition.h"

ChangeIntakePosition::ChangeIntakePosition(Intake *pintake)
    : m_pIntake(pintake)
{
  spdlog::trace("ChangeIntakePosition::ChangeIntakePosition()");
  AddRequirements(m_pIntake);
}

void ChangeIntakePosition::Initialize()
{
  spdlog::debug("ChangeIntakePosition::Initialize()");
  m_pIntake->ChangePosition();
}

void ChangeIntakePosition::Execute()
{
  spdlog::trace("ChangeIntakePosition::Execute()");
}

void ChangeIntakePosition::End(bool interrupted)
{
  spdlog::trace("ChangeIntakePosition::End()");
}

bool ChangeIntakePosition::IsFinished()
{
  return false;
}
