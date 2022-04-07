// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Conveyor/ActiveConveyorFeederMotor.h"

ActiveConveyorFeederMotor::ActiveConveyorFeederMotor(Conveyor *pconveyor, Shooter *pshooter)
    : m_pConveyor(pconveyor), m_pShooter(pshooter)
{
  AddRequirements(m_pConveyor);
  AddRequirements(m_pShooter);
}

// Called when the command is initially scheduled.
void ActiveConveyorFeederMotor::Initialize()
{
  m_pConveyor->m_count = 0;
  m_pConveyor->m_state = Conveyor::state::_INIT;
  m_pShooter->m_countShooter = 0;
}

// Called repeatedly when this Command is scheduled to run
void ActiveConveyorFeederMotor::Execute()
{
  m_pShooter->m_countShooter += 1;
  m_pShooter->SetSpeed(0.53);
  if (m_pShooter->m_countShooter >= 25)
  {
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
void ActiveConveyorFeederMotor::End(bool interrupted)
{
  m_pConveyor->StopAllMotors();
  m_pShooter->SetSpeed(0.0);
}

// Returns true when the command should end.
bool ActiveConveyorFeederMotor::IsFinished()
{
  return false;
}
