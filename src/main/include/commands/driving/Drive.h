// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"
#include "lib/RobotError.h"

#include "subsystems/Drivetrain.h"

class Drive
    : public frc2::CommandHelper<frc2::CommandBase, Drive>
{
public:
#if IS_DRIVETRAIN_OMNIBASE
  Drive(std::function<double()> forward, std::function<double()> turn, std::function<double()> lateral, Drivetrain *pdrivetrain);
#else
  Drive(std::function<double()> forward, std::function<double()> turn, Drivetrain *pdrivetrain);
#endif

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  std::function<double()> m_Forward;
  std::function<double()> m_Turn;
#if IS_DRIVETRAIN_OMNIBASE
  std::function<double()> m_Lateral;
#endif

  Drivetrain *m_pDrivetrain;
};
