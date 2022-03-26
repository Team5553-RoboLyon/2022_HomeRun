// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/tests/DrivetrainDirectionTest.h"

DrivetrainDirectionTest::DrivetrainDirectionTest(Drivetrain *pdrivetrain)
    : m_pDrivetrain(pdrivetrain)
{
  AddRequirements(m_pDrivetrain);
}

void DrivetrainDirectionTest::Initialize()
{
  m_IsFinished = false;
  m_testDuration = 0.0;
  m_pDrivetrain->Drive(DRIVETRAIN_TEST_SPEED, DRIVETRAIN_TEST_SPEED, DRIVETRAIN_TEST_SPEED);
}

void DrivetrainDirectionTest::Execute()
{
  double m_encoderValues[3];

  m_pDrivetrain->GetGearbox()->GetEncoderValues(m_encoderValues);
  bool isValueSupposedToBePositive = DRIVETRAIN_TEST_SPEED > 0;

  bool isValuePositive = m_encoderValues[0] > 0 && m_encoderValues[1] > 0 && m_encoderValues[2] > 0;

  if (m_testDuration > DRIVETRAIN_TEST_DURATION)
  {
    if (isValueSupposedToBePositive && isValuePositive)
    {
      m_IsFinished = true;
    }
    else
    {
      this->Cancel();
      throw RobotError::RobotTestError("DrivetrainDirectionTest", "Drivetrain is not moving in the correct direction");
    }
  }
  else
  {
    m_testDuration += ROBOT_LOOP_TIME;
  }
}

void DrivetrainDirectionTest::End(bool interrupted)
{
  m_pDrivetrain->Stop();
}

bool DrivetrainDirectionTest::IsFinished()
{
  return m_IsFinished;
}
