// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

#include "subsystems/Gearbox.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Climber.h"
#include "subsystems/Intake.h"
#include "subsystems/Turret.h"
#include "subsystems/Hood.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Shooter.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class SwitchGearboxMode
    : public frc2::CommandHelper<frc2::InstantCommand, SwitchGearboxMode>
{
public:
  SwitchGearboxMode(Gearbox *gearbox, Drivetrain *drivetrain, Climber *climber, Intake *intake, Turret *turret, Hood *hood, Conveyor *conveyor, Shooter *shooter);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

private:
  Gearbox *m_pGearbox;
  Drivetrain *m_pDrivetrain;
  Climber *m_pClimber;
  Turret *m_pTurret;
  Intake *m_pIntake;
  Hood *m_pHood;
  Shooter *m_pshooter;
  Conveyor *m_pconveyor;
};
