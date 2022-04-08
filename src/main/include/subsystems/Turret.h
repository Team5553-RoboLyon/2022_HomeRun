// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/Encoder.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <frc/Timer.h>
#include "Constants.h"

class Turret : public frc2::SubsystemBase
{
public:
  Turret();

  double GetMeasurement();
  void Periodic() override;
  void SetSetpoint(double setpoint);
  void Enable();
  void Disable();
  void ResetEncoders();
  double GetError();
  void ResetPID();

  enum state
  {
    Enabled,
    Disabled
  };
  Turret::state m_state = Turret::state::Disabled;

private:
  ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{TURRET_MOTOR_CAN_ID};
  frc::Encoder m_encoderTurret{TURRET_ENCODER_ID_A, TURRET_ENCODER_ID_B};
  frc2::PIDController m_controller = frc2::PIDController(TURRET_PID_P, TURRET_PID_I, TURRET_PID_D);
};
