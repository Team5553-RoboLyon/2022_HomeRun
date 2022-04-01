// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Shooter.h"

#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))

class SetShooterAuto
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetShooterAuto>
{
public:
  SetShooterAuto(Shooter *shooter);

  void Initialize() override;

private:
  int *getNearestElementId(double target);
  Shooter *m_shooter;

  static constexpr double shooterDataTable[3][3] = {
      {1.3, 1.4, 1.5},
      {1.6, 1.7, 1.8},
      {1.9, 1.10, 1.11},
  };
};
