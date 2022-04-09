// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/InstantCommand.h>
#include <frc/AnalogGyro.h>
#include "commands/auto/AutoMoovBackward.h"
#include "commands/Shoot/SetShooterAuto.h"
#include "commands/global/CompleteInit.h"
#include "commands/auto/AutoMoovToBall.h"
#include "commands/Intake/ActiveIntakeMotor.h"
#include "commands/auto/AutoBackToShoot.h"
#include "commands/Conveyor/IntakeConveyorMode.h"
#include "commands/auto/AutoTurn.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Shooter.h"
#include "subsystems/Turret.h"
#include "subsystems/Hood.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Intake.h"
#include "subsystems/Camera.h"
#include "subsystems/Gearbox.h"

class Auto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Auto>
{
public:
  Auto(Drivetrain *drivetrain, Shooter *shooter, Turret *turret,
       Hood *hood, Conveyor *conveyor, Intake *intake, Camera *camera,
       Gearbox *gearbox, frc::AnalogGyro *gyro);
};
