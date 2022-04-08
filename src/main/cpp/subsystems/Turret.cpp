// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <spdlog/spdlog.h>

Turret::Turret()
{
  SetSetpoint(0.0);
  m_controller.SetIntegratorRange(-TURRET_PID_INTEGRATOR_RANGE, TURRET_PID_INTEGRATOR_RANGE);
  m_controller.SetTolerance(0.0, std::numeric_limits<double>::infinity());
  m_encoderTurret.SetDistancePerPulse(45.000 / 1290.0);
  m_encoderTurret.SetReverseDirection(false);
  ResetEncoders();
  Enable();
}

void Turret::SetSetpoint(double setpoint)
{
  m_controller.SetSetpoint(std::clamp(setpoint, -80.0, 80.0));
}
void Turret::Enable()
{
  m_state = Turret::state::Enabled;
}
void Turret::Disable()
{
  m_state = Turret::state::Disabled;
}
void Turret::ResetEncoders()
{
  m_encoderTurret.Reset();
}
double Turret::GetError()
{
  return m_controller.GetPositionError();
}
void Turret::ResetPID()
{
  m_controller.Reset();
}
void Turret::Periodic()
{
  if (m_state == Turret::state::Enabled)
  {
    double output = std::clamp(m_controller.Calculate(GetMeasurement()), -0.8, 0.8);
    spdlog::error(output);
    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, output);
  }
  else
  {
    spdlog::error("disabled");

    m_TurretMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
  }
}

double Turret::GetMeasurement()
{
  spdlog::error("encodeur value");
  spdlog::error(m_encoderTurret.GetDistance());
  return m_encoderTurret.GetDistance();
}
