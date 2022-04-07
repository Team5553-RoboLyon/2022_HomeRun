// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Climber/Climb.h"

Climb::Climb(std::function<double()> rotating, std::function<double()> linear, Climber *climber)
{
  m_pClimber = climber;
  AddRequirements(m_pClimber);
  m_rotating = rotating;
  m_linear = linear;
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void Climb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute()
{
  if (m_pClimber->GetEnabled())
  {
    m_pClimber->MoveRotatingArms(m_rotating());
    m_pClimber->MoveClimber(m_linear());
  }
}

// Called once the command ends or is interrupted.
void Climb::End(bool interrupted) {}

// Returns true when the command should end.
bool Climb::IsFinished()
{
  return false;
}
