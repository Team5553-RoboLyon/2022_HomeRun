// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Feeder/UnblockFeederMotor.h"

UnblockFeederMotor::UnblockFeederMotor(Feeder *pfeeder)
    : m_pFeeder(pfeeder);
{
  AddRequirements(m_pFeeder);
}

void UnblockFeederMotor::Initialize() {}

void UnblockFeederMotor::Execute() {}

void UnblockFeederMotor::End(bool interrupted) {}

bool UnblockFeederMotor::IsFinished()
{
  return false;
}
