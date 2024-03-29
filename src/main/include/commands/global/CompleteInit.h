// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Camera.h"
#include "subsystems/Hood.h"
#include "subsystems/Gearbox.h"
#include "subsystems/Turret.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CompleteInit
    : public frc2::CommandHelper<frc2::InstantCommand, CompleteInit>
{
public:
  CompleteInit(Camera *camera, Hood *hood, Gearbox *gearbox, Drivetrain *drivetrain, Turret *pturret);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

private:
  Camera *m_pCamera;
  Hood *m_pHood;
  Gearbox *m_pGearbox;
  Drivetrain *m_pDrivetrain;
  Turret *m_pTurret;
};
