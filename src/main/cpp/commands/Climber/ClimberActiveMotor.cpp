// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Climber/ClimberActiveMotor.h"

ClimberActiveMotor::ClimberActiveMotor(std::function<double()> joystickInput, Climber *pclimber)
    : m_pClimber(pclimber), m_joystickInput(joystickInput)
{
  AddRequirements(m_pClimber);
}

// Called when the command is initially scheduled.
void ClimberActiveMotor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberActiveMotor::Execute()
{
  m_pClimber->ActiveMotor(m_joystickInput());
}

// Called once the command ends or is interrupted.
void ClimberActiveMotor::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimberActiveMotor::IsFinished()
{
  return false;
}
