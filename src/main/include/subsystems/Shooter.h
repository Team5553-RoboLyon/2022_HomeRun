// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include "Hood.h"

class Shooter : public frc2::SubsystemBase
{
public:
  Shooter();
  Hood m_hood;
  void Periodic() override;
  void SetSpeed(double speed);
  double AppliedSpeed();

private:
  ctre::phoenix::motorcontrol::can::TalonFX m_MotorLeft{2};
  ctre::phoenix::motorcontrol::can::TalonFX m_MotorRight{3};
};
