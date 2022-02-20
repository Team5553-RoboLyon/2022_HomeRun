// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/Encoder.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>

class Turret : public frc2::PIDSubsystem
{
public:
  Turret();
  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void ResetEncoder();
  void SetPID(double p, double i, double d);

private:
  ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{4};
  frc::Encoder m_encoderTurret{1, 2};
  // frc::Encoder m_encodeur{1, 2};
};
