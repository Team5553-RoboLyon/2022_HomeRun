// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include "lib/RobotError.h"

class DrivetrainDirectionTest
    : public frc2::CommandHelper<frc2::CommandBase, DrivetrainDirectionTest>
{
public:
  DrivetrainDirectionTest(Drivetrain *pdrivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Drivetrain *m_pDrivetrain;
  bool m_IsFinished;
  double m_testDuration;
};
