// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/NearShoot.h"

NearShoot::NearShoot(Conveyor *pconveyor, Shooter *shooter, Hood *hood, Turret *turret)
    : m_pConveyor(pconveyor), m_pShooter(shooter), m_phood(hood), m_pturret(turret)

{
  AddRequirements(m_pShooter);
  AddRequirements(m_phood);
  AddRequirements(m_pturret);
  AddRequirements(m_pConveyor);
}

// Called when the command is initially scheduled.
void NearShoot::Initialize()
{
  m_pShooter->m_countShooter = 0;
  m_pConveyor->m_count = 0;
  m_pConveyor->m_state = Conveyor::state::_INIT;
  m_phood->SetSetpoint(4.0);
  m_pShooter->SetSpeed(0.7);
  m_pturret->SetClampedSetpoint(0.0);
}

// Called repeatedly when this Command is scheduled to run
void NearShoot::Execute()
{

  if (std::abs(m_pturret->GetController().GetPositionError()) < 2 && std::abs(m_phood->GetError()) < 2 && m_pShooter->m_countShooter >= 10)
  {
    m_pShooter->isReady = true;
    switch (m_pConveyor->m_state)
    {
    case Conveyor::state::_INIT:

      if (m_pConveyor->m_count >= 20)
      {
        m_pConveyor->m_state = Conveyor::state::_ENABLE;
        m_pConveyor->m_count = 0;
      }
      else
      {
        m_pConveyor->UnblockFeedingMotor();
        if (m_pConveyor->m_count <= 8)
        {
          m_pConveyor->UnblockConveyorMotor();
        }
        else
        {
          m_pConveyor->StopConveyorMotor();
        }
      }
      m_pConveyor->m_count += 1;

      break;
    case Conveyor::state::_ENABLE:
      if (m_pConveyor->m_count >= 30)
      {
        m_pConveyor->m_count = 0;
        m_pConveyor->m_state = Conveyor::state::_INIT;
      }
      else
      {
        m_pConveyor->m_count += 1;
        m_pConveyor->ActiveConveyorMotor();
        m_pConveyor->ActiveFeedingMotor();
      }

      break;

    default:
      break;
    }
  }
}

// Called once the command ends or is interrupted.
void NearShoot::End(bool interrupted)
{
  m_pShooter->SetSpeed(0.0);
  m_phood->SetSetpoint(0.0);
  m_pturret->SetClampedSetpoint(0.0);
  m_pConveyor->StopAllMotors();
}

// Returns true when the command should end.
bool NearShoot::IsFinished()
{
  return false;
}
