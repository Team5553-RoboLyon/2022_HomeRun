// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc2/command/PIDSubsystem.h>
#include "Constants.h"

class Hood : public frc2::PIDSubsystem
{
public:
  Hood();
  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  bool AtSetpoint();

private:
  ctre::phoenix::motorcontrol::can::VictorSPX m_HoodMotor{HOOD_MOTOR_ID};
};
