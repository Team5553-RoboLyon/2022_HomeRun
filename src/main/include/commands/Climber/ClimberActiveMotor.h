// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Climber.h"
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ClimberActiveMotor
    : public frc2::CommandHelper<frc2::CommandBase, ClimberActiveMotor>
{
public:
  ClimberActiveMotor(std::function<double()> joystickInput, Climber *pclimber);

  void Initialize() ;

  void Execute() ;

  void End(bool interrupted) ;

  bool IsFinished() ;

private:
  Climber *m_pClimber;
  std::function<double()> m_joystickInput;
};