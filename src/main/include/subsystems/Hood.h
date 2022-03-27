// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <frc/DutyCycleEncoder.h>
#include <rev/CANSparkMax.h>
#include <iostream>
#include <frc/DigitalInput.h>
#include <units/angle.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include "Constants.h"
#include <robolyon/HallSecurity.h>

class Hood : public frc2::SubsystemBase
{
public:
  Hood();

  double GetMeasurement();

  void Periodic() override;

  void SetSetpoint(double setpoint);

  double GetSetpoint();

  void Enable();

  void Disable();

  void ResetEncoders();

  void UseOutput(double output, double setpoint);

  static std::string StateToString(int state);

private:
  enum state
  {
    WaitingEncoder,
    Init,
    Enabled,
    Disabled
  };
  Hood::state m_state = Hood::state::WaitingEncoder;

  frc::ProfiledPIDController<units::degree> m_pidcontroller{
      HOOD_PID_P, HOOD_PID_I, HOOD_PID_D,
      frc::TrapezoidProfile<units::degree>::Constraints{5_deg / 1_s, 10_deg / (1_s * 1_s)}};
  frc::DutyCycleEncoder m_encoderHood{1};

  rev::CANSparkMax m_HoodMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  HallSecurity m_hallSecurity{HOOD_SENSOR_HALL_ID, 0.3};

  double m_setPoint = 0;

#if SHUFFLEBOARD_DEBUG
  nt::NetworkTableEntry m_entry_HoodPosition;
  nt::NetworkTableEntry m_entry_HoodSetpoint;
  nt::NetworkTableEntry m_entry_HoodError;
  nt::NetworkTableEntry m_entry_HoodOutput;
  nt::NetworkTableEntry m_entry_HoodState;
#endif
};