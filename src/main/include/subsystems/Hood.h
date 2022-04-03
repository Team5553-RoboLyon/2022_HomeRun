// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include <iostream>
#include <frc/DigitalInput.h>
#include <units/angle.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <robolyon/HallSecurity.h>
#include "Constants.h"

class Hood : public frc2::SubsystemBase
{
public:
    Hood();

    double GetMeasurement();

    void Periodic();

    void SetSetpoint(double setpoint);

    void Enable();

    void Disable();

    void ResetEncoders();

private:
    enum state
    {
        WaitingEncoder,
        Init,
        Enabled,
        Disabled
    };
    Hood::state m_state = Hood::state::WaitingEncoder;

    frc::ProfiledPIDController<units::degree> m_controller{
        0.035, 0.008, 0.0004,
        frc::TrapezoidProfile<units::degree>::Constraints{5_deg / 1_s, 10_deg / (1_s * 1_s)}};
    frc::Encoder m_encoderHood{HOOD_ENCODER_A_ID, HOOD_ENCODER_B_ID};

    rev::CANSparkMax m_HoodMotor{HOOD_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
    HallSecurity m_hallSecurity{HOOD_SENSOR_HALL_ID, 0.3};

    double m_setPoint = 0;
};
