// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/auto/AutoTurn.h"

AutoTurn::AutoTurn(Drivetrain *drivetrain, frc::AnalogGyro *gyro, double setpoint)
{
  m_pDrivetrain = drivetrain;
  m_pGyro = gyro;
  m_setpoint = setpoint;
  AddRequirements(m_pDrivetrain);
}

// Called when the command is initially scheduled.
void AutoTurn::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoTurn::Execute()
{
  m_error = m_setpoint - std::fmod(m_pGyro->GetAngle(), 360.0);
  double speed = std::clamp(((m_error * (DRIVETRAIN_AUTONOMOUS_SPEED - 0.1)) / m_setpoint) + 0.1, -DRIVETRAIN_AUTONOMOUS_SPEED, DRIVETRAIN_AUTONOMOUS_SPEED);
  m_pDrivetrain->Drive(speed, -speed);
}

// Called once the command ends or is interrupted.
void AutoTurn::End(bool interrupted)
{
  m_pDrivetrain->Stop();
}

// Returns true when the command should end.
bool AutoTurn::IsFinished()
{
  return std::abs(m_error) < 2;
}
