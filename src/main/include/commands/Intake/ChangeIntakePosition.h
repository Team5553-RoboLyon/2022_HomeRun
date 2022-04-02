// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Intake.h"
#include <spdlog/spdlog.h>

class ChangeIntakePosition
    : public frc2::CommandHelper<frc2::CommandBase, ChangeIntakePosition>
{
public:
  ChangeIntakePosition(Intake *pintake);

  void Initialize() ;

  void Execute() ;

  void End(bool interrupted) ;

  bool IsFinished() ;

private:
  Intake *m_pIntake;
};
