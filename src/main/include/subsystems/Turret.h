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

class Turret : public frc2::PIDSubsystem
{
public:
  Turret();
  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void ResetEncoder();
  void SetPID(double p, double i, double d);
  bool MagnetDetected();
  void ResetTurretState();
  double m_TDeltaPosition;
  double m_TPosition;
  double m_TPositionBefore;
  double m_TSpeedConsigne;

private:
  enum State
  {
    unknownPosition,
    goTo0,
    ready,
    d_Direction,
    g_Direction,
    dg_Direction,
    StopSecure
  };
  ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{4};
  frc::Encoder m_encoderTurret{10, 11};
  frc::DigitalInput m_SensorHall{7};
  State m_State = Turret::State::unknownPosition;
  frc::Timer m_Timer;
};
