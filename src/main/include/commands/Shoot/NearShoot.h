// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Shooter.h"
#include "subsystems/Shooter.h"
#include "subsystems/Hood.h"
#include "subsystems/Turret.h"
#include "subsystems/Conveyor.h"
#include "commands/Conveyor/Chainball.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class NearShoot
    : public frc2::CommandHelper<frc2::CommandBase, NearShoot>
{
public:
  NearShoot(Conveyor *pconveyor, Shooter *shooter, Hood *hood, Turret *turret);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Shooter *m_pShooter;
  Conveyor *m_pConveyor;
  Hood *m_phood;
  Turret *m_pturret;
};
