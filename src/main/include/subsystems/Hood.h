// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/controller/PIDController.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/DutyCycleEncoder.h>
#include <rev/CANSparkMax.h>
#include <iostream>
#include <frc/DigitalInput.h>
#include "Constants.h"
#include <networktables/NetworkTableEntry.h>

class Hood : public frc2::SubsystemBase
{
public:
  Hood();
  double GetEncoderDistance();
  void ResetEncoders();
  bool MagnetDetected();
  void SetSetpoint(double setpoint);
  void Periodic();
  std::string StateToString(int state);

  double m_DeltaPosition;
  double m_Position;
  double m_PositionBefore;

  enum state
  {
    Init,
    haut_Direction,
    bas_Direction,
    bh_Direction,
    StopSecure
    // Ready,
  };
  Hood::state m_state = Hood::state::Init;

private:
  void UseOutput(double output, double setpoint);
  frc::DutyCycleEncoder m_encoderHood{HOOD_ENCODER_ID};
  frc::DigitalInput m_SensorHall{HOOD_SENSOR_HALL_ID};

  rev::CANSparkMax m_HoodMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  frc2::PIDController m_pidController{HOOD_PID_P, HOOD_PID_I, HOOD_PID_D};

#if SHUFFLEBOARD_DEBUG
  nt::NetworkTableEntry m_entry_HoodPosition;
  nt::NetworkTableEntry m_entry_HoodSetpoint;
  nt::NetworkTableEntry m_entry_HoodError;
  nt::NetworkTableEntry m_entry_HoodOutput;
  nt::NetworkTableEntry m_entry_HoodState;
#endif
};