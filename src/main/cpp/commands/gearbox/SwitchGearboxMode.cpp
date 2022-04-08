// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/gearbox/SwitchGearboxMode.h"

SwitchGearboxMode::SwitchGearboxMode(Gearbox *gearbox, Drivetrain *drivetrain, Climber *climber, Intake *intake, Turret *turret, Hood *hood, Conveyor *conveyor, Shooter *shooter)
{
  m_pGearbox = gearbox;
  m_pDrivetrain = drivetrain;
  m_pClimber = climber;
  m_pIntake = intake;
  m_pTurret = turret;
  m_pHood = hood;
  m_pconveyor = conveyor;
  m_pshooter = shooter;
}

// Called when the command is initially scheduled.
void SwitchGearboxMode::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SwitchGearboxMode::Execute()
{
  {
    if (m_pGearbox->GetPTOState() == Gearbox::PTOState::Driving)
    {
      m_pDrivetrain->Disable();
      m_pClimber->Enable();
      m_pTurret->Enable();
      m_pTurret->SetClampedSetpoint(0.0);
      m_pIntake->Close();
      m_pHood->SetSetpoint(0.0);
      m_pconveyor->StopAllMotors();
      m_pshooter->SetSpeed(0.0);
    }
    else
    {
      m_pDrivetrain->Enable();
      m_pClimber->Disable();
    }
  }
}

// Called once the command ends or is interrupted.
void SwitchGearboxMode::End(bool interrupted) {}
