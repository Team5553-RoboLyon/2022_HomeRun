// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/global/CompleteInit.h"

CompleteInit::CompleteInit(Camera *camera, Hood *hood, Gearbox *gearbox, Drivetrain *drivetrain, Turret *pturret, Intake *intake)

{
  m_pCamera = camera;
  m_pHood = hood;
  m_pGearbox = gearbox;
  m_pDrivetrain = drivetrain;
  m_pTurret = pturret;
  m_pIntake = intake;

  AddRequirements({m_pCamera, m_pHood, m_pGearbox, m_pDrivetrain, m_pTurret});
}

// Called when the command is initially scheduled.
void CompleteInit::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CompleteInit::Execute()
{
  m_pCamera->DisableLED();
  m_pHood->ResetPID();
  m_pGearbox->InitTeleopPeriod();
  m_pTurret->ResetPID();
  m_pDrivetrain->Enable();
  m_pIntake->Close();
  frc::Shuffleboard::GetTab("dev").Add("shooter coef", 1.0).GetEntry().SetDouble(1.0);
  frc::Shuffleboard::GetTab("dev").Add("disangage", 2.0).GetEntry().SetDouble(2.0);
  frc::Shuffleboard::GetTab("dev").Add("shoot0", 5.0).GetEntry().SetDouble(5.0);
  frc::Shuffleboard::GetTab("dev").Add("Shoot1", 8.0).GetEntry().SetDouble(8.0);
  frc::Shuffleboard::GetTab("dev").Add("Shoot2_pause", 12.0).GetEntry().SetDouble(12.0);
}

// Called once the command ends or is interrupted.
void CompleteInit::End(bool interrupted) {}