// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/tests/DrivetrainTest.h"

DrivetrainTest::DrivetrainTest(Drivetrain *pdrivetrain)
    : m_pDrivetrain(pdrivetrain)
{
  AddRequirements(m_pDrivetrain);
}

void DrivetrainTest::Initialize() {}

void DrivetrainTest::Execute() {}

void DrivetrainTest::End(bool interrupted) {}

bool DrivetrainTest::IsFinished()
{
  return false;
}
