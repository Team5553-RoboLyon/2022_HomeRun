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
#if IS_DRIVETRAIN_OMNIBASE
  m_pDrivetrain->Drive(DRIVETRAIN_TEST_SPEED, DRIVETRAIN_TEST_SPEED, DRIVETRAIN_TEST_SPEED);
#else
  m_pDrivetrain->Drive(DRIVETRAIN_TEST_SPEED, DRIVETRAIN_TEST_SPEED);
#endif
}

void DrivetrainDirectionTest::Execute()
{
#if IS_DRIVETRAIN_OMNIBASE
  double m_encoderValues[3];
#else
  double m_encoderValues[2];
#endif

  m_pDrivetrain->GetEncoderValues(m_encoderValues);
  bool isValueSupposedToBePositive = DRIVETRAIN_TEST_SPEED > 0;

#if IS_DRIVETRAIN_OMNIBASE
  bool isValuePositive = m_encoderValues[0] > 0 && m_encoderValues[1] > 0 && m_encoderValues[2] > 0;
#else
  bool isValuePositive = m_encoderValues[0] > 0 && m_encoderValues[1] > 0;
#endif

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
