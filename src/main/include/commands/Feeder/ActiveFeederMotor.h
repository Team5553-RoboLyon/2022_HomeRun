// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Feeder.h"
#include <spdlog/spdlog.h>

class ActiveFeederMotor
    : public frc2::CommandHelper<frc2::CommandBase, ActiveFeederMotor>
{
public:
  ActiveFeederMotor(Feeder *pfeeder);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Feeder *m_pFeeder;
};
