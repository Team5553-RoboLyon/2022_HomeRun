// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shoot/NearShoot.h"

NearShoot::NearShoot(Conveyor *pconveyor, Shooter *shooter, Hood *hood, Turret *turret)
{
  m_pShooter = shooter;
  m_pConveyor = pconveyor;
  m_phood = hood;
  m_pturret = turret;
  AddRequirements({m_pShooter, m_pConveyor, m_phood, m_pturret});
}

// Called when the command is initially scheduled.
void NearShoot::Initialize()
{
  m_phood->SetSetpoint(4.0);
  m_pShooter->SetSpeed(SHOOTER_MOTOR_SPEED);
  m_pShooter->m_countShooter = 0;
  m_pturret->SetSetpoint(0.0);
  ChainballInit2(m_pConveyor, m_pShooter);
}

// Called repeatedly when this Command is scheduled to run
void NearShoot::Execute()
{
  m_pShooter->m_countShooter += 1;
  if (std::abs(m_pturret->GetError()) < 2 && std::abs(m_phood->GetError()) < 2 && m_pShooter->m_countShooter >= 10)
  {
    ChainballRun2(m_pConveyor, m_pShooter);
  }
}

// Called once the command ends or is interrupted.
void NearShoot::End(bool interrupted)
{
  m_phood->SetSetpoint(0.0);
  m_pShooter->SetSpeed(0.0);
  m_pShooter->m_countShooter = 0;
  m_pturret->SetSetpoint(0.0);
  m_pConveyor->StopAllMotors();
}

// Returns true when the command should end.
bool NearShoot::IsFinished()
{
  return false;
}
