// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include <frc/filter/MedianFilter.h>
#include "subsystems/Shooter.h"
#include "subsystems/Hood.h"
#include "subsystems/Turret.h"
#include "subsystems/Camera.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"

#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))

class SetShooterAuto
    : public frc2::CommandHelper<frc2::CommandBase,
                                 SetShooterAuto>
{
public:
  SetShooterAuto(Shooter *shooter, Hood *hood, Turret *turret, Camera *camera);

  void Execute() override;
  void End(bool interrupted) override;
  void Initialize() override;

private:
  int *getNearestElementId(double target);
  frc::MedianFilter<double> m_horizontalMedian = frc::MedianFilter<double>(3);
  Shooter *m_shooter;
  Hood *m_hood;
  Turret *m_turret;
  Camera *m_camera;

#define SHOOTER_TABLE_SIZE 7
  static constexpr double shooterDataTable[SHOOTER_TABLE_SIZE][3] = {
      // pitch, angle, vitesse
      {-17.4, 33, 0.7},
      {-13.8, 36, 0.67},
      {-8.6, 20, 0.65},
      {-1, 17, 0.6},
      {9.7, 13, 0.57},
      {10, 8, 0.55},
      {18.6, 8, 0.6},
  };
};
