// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"
#include <frc/AnalogGyro.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoMoovToBall
    : public frc2::CommandHelper<frc2::CommandBase, AutoMoovToBall>
{
public:
  AutoMoovToBall(Gearbox *gearbox, frc::AnalogGyro *gyro);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  enum State
  {
    halfTour,
    goToBall,
    finished,
  };
  State m_state = State::halfTour;
  double m_count = 0;
  Gearbox *m_pGearbox;
  frc::AnalogGyro *m_pGyro;
};
