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
#include <robolyon/HallSecurity.h>

class Hood : public frc2::SubsystemBase
{
public:
    Hood();

    double GetMeasurement();

    void Periodic() ;

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
    frc::DutyCycleEncoder m_encoderHood{0};

    rev::CANSparkMax m_HoodMotor{18, rev::CANSparkMax::MotorType::kBrushless};
    HallSecurity m_hallSecurity{8, 0.3};

    double m_setPoint = 0;
};
