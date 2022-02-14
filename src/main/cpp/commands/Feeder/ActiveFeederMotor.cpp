// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Feeder/ActiveFeederMotor.h"

ActiveFeederMotor::ActiveFeederMotor(Feeder *pfeeder)
    : m_pFeeder(pfeeder)
{
  spdlog::trace("ActiveFeederMotor::ActiveFeederMotor()");
  AddRequirements(m_pFeeder);
}

void ActiveFeederMotor::Initialize()
{
  spdlog::trace("ActiveFeederMotor::Initialize()");
}

void ActiveFeederMotor::Execute()
{
  spdlog::trace("ActiveFeederMotor::Execute()");
  m_pFeeder->ActiveMotor();
}

void ActiveFeederMotor::End(bool interrupted)
{
  spdlog::trace("ActiveFeederMotor::End()");
  m_pFeeder->StopMotor();
}

bool ActiveFeederMotor::IsFinished()
{
  return false;
}
