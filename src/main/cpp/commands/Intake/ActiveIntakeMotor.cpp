// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/ActiveIntakeMotor.h"

ActiveIntakeMotor::ActiveIntakeMotor(Intake *pintake)
    : m_pIntake(pintake)
{
  spdlog::trace("ActiveIntakeMotor::ActiveIntakeMotor()");
  AddRequirements(m_pIntake);
}

void ActiveIntakeMotor::Initialize()
{
  spdlog::trace("ActiveIntakeMotor::Initialize()");
}

void ActiveIntakeMotor::Execute()
{
  spdlog::trace("ActiveIntakeMotor::Execute()");
  m_pIntake->ActiveMotor();
}

void ActiveIntakeMotor::End(bool interrupted)
{
  spdlog::trace("ActiveIntakeMotor::End()");
  m_pIntake->StopMotor();
}

bool ActiveIntakeMotor::IsFinished()
{
  return false;
}
