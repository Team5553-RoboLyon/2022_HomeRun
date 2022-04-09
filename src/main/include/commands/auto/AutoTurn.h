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
class AutoTurn
    : public frc2::CommandHelper<frc2::CommandBase, AutoTurn>
{
public:
  AutoTurn(Drivetrain *drivetrain, frc::AnalogGyro *gyro, double setpoint);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  double m_setpoint = 0.0;
  double m_error = 0.0;
  Drivetrain *m_pDrivetrain;
  frc::AnalogGyro *m_pGyro;
};
