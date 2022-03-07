// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
    : PIDSubsystem(frc2::PIDController(0.001, 0, 0)) {}

void Turret::UseOutput(double output, double setpoint)
{
  m_encoderTurret.SetDistancePerRotation(1.0);
  SetSetpoint(0.0);
  m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, output);
  frc::SmartDashboard::PutNumber("outputTurret", output);
  GetController().SetIntegratorRange(-10, 10);
  Disable();
}

double Turret::GetMeasurement()
{
  return GetEncoder();
}

void Turret::ResetEncoder()
{
  while (!m_encoderTurret.IsConnected())
  {
    spdlog::info("ENCODER TURRET NOT RESETTED");
  }
  spdlog::info("RESETTING ENCODEUR");
  m_encoderTurret.Reset();
  spdlog::info("RESETTED ENCODEUR");
  spdlog::info(m_encoderTurret.IsConnected());
}

double Turret::GetEncoder()
{
  return m_encoderTurret.GetDistance();
}

void Turret::SetPID(double p, double i, double d)
{
  GetController().SetP(p);
  GetController().SetI(i);
  GetController().SetD(d);
}
