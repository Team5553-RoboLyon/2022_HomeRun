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
#include <spdlog/spdlog.h>

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
    enum state
    {
        Enabled,
        Disabled
    };
    Hood::state m_state = Hood::state::Disabled;

private:
    frc::PIDController m_controller{HOOD_PID_P, HOOD_PID_I, HOOD_PID_D};
    frc::Encoder m_encoderHood{HOOD_ENCODER_A_ID, HOOD_ENCODER_B_ID};

    rev::CANSparkMax m_HoodMotor{HOOD_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
    HallSecurity m_hallSecurity{HOOD_SENSOR_HALL_ID, 0.3};

    double m_setPoint = 0.0;
};
