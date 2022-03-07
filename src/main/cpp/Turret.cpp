// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
    : PIDSubsystem(frc2::PIDController(0.065, 0.001, 0.006))
{
  SetSetpoint(0.0);
  GetController().SetIntegratorRange(-5, 5);
  GetController().SetTolerance(0.0, std::numeric_limits<double>::infinity());
  m_encoderTurret.SetDistancePerRotation(90.000 / 2.577);
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
  spdlog::info("RESETING TURRET ENCODEUR");
  m_encoderTurret.Reset();
  spdlog::info("RESETTED TURRET ENCODEUR");
}

void Turret::SetPID(double p, double i, double d)
{
  GetController().SetP(p);
  GetController().SetI(i);
  GetController().SetD(d);
}
