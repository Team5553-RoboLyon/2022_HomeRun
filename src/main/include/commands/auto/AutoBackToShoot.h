// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/AnalogGyro.h>
#include "subsystems/Drivetrain.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoBackToShoot
    : public frc2::CommandHelper<frc2::CommandBase, AutoBackToShoot>
{
public:
  AutoBackToShoot(Drivetrain *drivetrain, frc::AnalogGyro *gyro);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  enum State
  {
    halfTour,
    goToShoot,
    finished,
  };
  State m_state = State::halfTour;
  double m_count = 0;
  Drivetrain *m_pDrivetrain;
  frc::AnalogGyro *m_pGyro;
};
