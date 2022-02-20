// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
    : PIDSubsystem(frc2::PIDController(0.04, 0.02, 0.002))
{
  SetSetpoint(0.0);
  GetController().SetIntegratorRange(-5, 5);
  GetController().SetTolerance(0.0, std::numeric_limits<double>::infinity());
  m_encoderTurret.SetDistancePerPulse(45.000 / 1290);
  m_encoderTurret.SetReverseDirection(true);
  Disable();
}

void Turret::UseOutput(double output, double setpoint)
{
  m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.6, 0.6));
  frc::SmartDashboard::PutNumber("outputTurret", output);
}

double Turret::GetMeasurement()
{
  return m_encoderTurret.GetDistance();
}

void Turret::ResetEncoder()
{
  m_encoderTurret.Reset();
}

void Turret::SetPID(double p, double i, double d)
{
  GetController().SetP(p);
  GetController().SetI(i);
  GetController().SetD(d);
}
