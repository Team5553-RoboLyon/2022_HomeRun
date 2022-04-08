// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
    : PIDSubsystem(frc2::PIDController(0.04, 0.02, 0.002))
{
  SetSetpoint(0.0);
  GetController().SetIntegratorRange(-TURRET_PID_INTEGRATOR_RANGE, TURRET_PID_INTEGRATOR_RANGE);
  GetController().SetTolerance(0.0, std::numeric_limits<double>::infinity());
  m_encoderTurret.SetDistancePerPulse(45.000 / 1290);
  m_encoderTurret.SetReverseDirection(true);
  ResetEncoder();
  Enable();
}

void Turret::UseOutput(double output, double setpoint)
{
  m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, std::clamp(output, -0.8, 0.8));
}

double Turret::GetMeasurement()
{
  return m_encoderTurret.GetDistance();
}
void Turret::SetClampedSetpoint(double setpoint)
{
  SetSetpoint(std::clamp(setpoint, -80.0, 80.0));
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
