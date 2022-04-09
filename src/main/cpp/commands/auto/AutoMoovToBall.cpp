// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/AutoMoovToBall.h"

AutoMoovToBall::AutoMoovToBall(Gearbox *gearbox, frc::AnalogGyro *gyro)
{
  m_pGearbox = gearbox;
  m_pGyro = gyro;
  AddRequirements(m_pGearbox);
}

// Called when the command is initially scheduled.
void AutoMoovToBall::Initialize()
{
  m_count = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutoMoovToBall::Execute()
{
  switch (m_state)
  {
  case State::halfTour:
    if (m_pGyro->GetAngle() > 180)
    {
      m_pGearbox->Stop();
      m_state = State::goToBall;
    }
    else
    {
      m_pGearbox->SetEveryone(DRIVETRAIN_AUTONOMOUS_SPEED, -DRIVETRAIN_AUTONOMOUS_SPEED, Gearbox::PTOState::Driving);
    }
    break;
  case State::goToBall:
    m_pGearbox->SetEveryone(DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED, Gearbox::PTOState::Driving);
    m_count += 1;
    if (m_count > AUTO_TAKING_BALL_TIME)
    {
      m_pGearbox->Stop();
      m_state = State::finished;
    }
    break;

  default:
    break;
  }
}

// Called once the command ends or is interrupted.
void AutoMoovToBall::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoMoovToBall::IsFinished()
{
  return m_state == State::finished;
}
