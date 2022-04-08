// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/global/CompleteInit.h"

CompleteInit::CompleteInit(Camera *camera, Hood *hood, Gearbox *gearbox, Drivetrain *drivetrain) : m_pCamera(camera), m_pHood(hood), m_pGearbox(gearbox), m_pDrivetrain(drivetrain)
{
  AddRequirements({m_pCamera, m_pHood, m_pGearbox, m_pDrivetrain});
}

// Called when the command is initially scheduled.
void CompleteInit::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CompleteInit::Execute()
{
  m_pCamera->DisableLED();
  m_pHood->ResetPID();
  m_pGearbox->InitTeleopPeriod();
  m_pDrivetrain->Enable();
}

// Called once the command ends or is interrupted.
void CompleteInit::End(bool interrupted) {}