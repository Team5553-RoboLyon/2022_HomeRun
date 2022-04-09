// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/AutoBackToShoot.h"

AutoBackToShoot::AutoBackToShoot(Drivetrain *drivetrain, frc::AnalogGyro *gyro)
{
  m_pDrivetrain = drivetrain;
  m_pGyro = gyro;
  AddRequirements(m_pDrivetrain);
}

// Called when the command is initially scheduled.
void AutoBackToShoot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoBackToShoot::Execute()
{
  switch (m_state)
  {
  case AutoBackToShoot::State::halfTour:
    error = 0 - m_pGyro->GetAngle();

    if (m_pGyro->GetAngle() < 0 || std::abs(error) < 2)
    {
      m_pDrivetrain->Drive(0, 0);
      m_state = State::goToShoot;
    }
    else
    {
      double speed = std::clamp(((error * (DRIVETRAIN_AUTONOMOUS_SPEED - 0.1)) / 180) + 0.1, -DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED);
      m_pDrivetrain->Drive(speed, -speed);
    }
    break;
  case AutoBackToShoot::State::goToShoot:
    m_pDrivetrain->Drive(DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED);
    m_count += 1;
    if (m_count > AUTO_TAKING_BALL_TIME)
    {
      m_pDrivetrain->Stop();
      m_state = State::finished;
    }
    break;
  }
}

// Called once the command ends or is interrupted.
void AutoBackToShoot::End(bool interrupted)
{
}

// Returns true when the command should end.
bool AutoBackToShoot::IsFinished()
{
  return m_state == State::finished;
}
