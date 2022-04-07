// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include "Constants.h"

class Shooter : public frc2::SubsystemBase
{
public:
  Shooter();
  void Periodic();
  void SetSpeed(double speed);
  double AppliedSpeed();
  int m_countShooter;
  bool isReady = false;

private:
  ctre::phoenix::motorcontrol::can::TalonFX m_MotorLeft{SHOOTER_MOTOR_LEFT_CAN_ID};
  ctre::phoenix::motorcontrol::can::TalonFX m_MotorRight{SHOOTER_MOTOR_RIGHT_CAN_ID};
};
