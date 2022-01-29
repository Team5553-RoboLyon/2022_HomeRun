// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"

#if IS_DRIVETRAIN_OMNIBASE
#include "subsystems/DrivetrainOmni.h"
#endif

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Drive
    : public frc2::CommandHelper<frc2::CommandBase, Drive>
{
public:
  Drive(std::function<double()> forward, std::function<double()> turn, std::function<double()> lateral, Drivetrain *pdrivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  std::function<double()> m_Forward;
  std::function<double()> m_Turn;
  std::function<double()> m_Lateral;
  Drivetrain *m_pDrivetrain;
};
