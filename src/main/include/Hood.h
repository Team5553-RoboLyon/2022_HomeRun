// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/DutyCycleEncoder.h>
#include <rev/CANSparkMax.h>
#include <iostream>
#include <frc/DigitalInput.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <units/voltage.h>


class Hood : public frc2::PIDSubsystem {
public:
    Hood();

    double GetMeasurement() override;

    void UseOutput(double output, double setpoint) override;

    double GetEncoder();

    void ResetEncoders();

    bool MagnetDetected();

    void SetPID(double p, double i, double d);

    double m_DeltaPosition;
    double m_Position;
    double m_PositionBefore;

    enum state {
        Init,
        haut_Direction,
        bas_Direction,
        bh_Direction,
        StopSecure
        // Ready,
    };
    Hood::state m_state = Hood::state::Init;

private:
    frc::DutyCycleEncoder m_encoderHood{0};
    frc::DigitalInput m_SensorHall{8};
    units::volt_t kS{0.46};
    units::unit_t <frc::SimpleMotorFeedforward<units::meter>::kv_unit> kV{3.62};
    units::unit_t <frc::SimpleMotorFeedforward<units::meter>::ka_unit> kA{0.05};

    frc::SimpleMotorFeedforward <units::meter> feedforward{
            0.46_V,
            (3.62_V * 1_s) / 1_m,
            (0.05_V * (1_s * 1_s)) / 1_m
    };


    rev::CANSparkMax m_HoodMotor{1, rev::CANSparkMax::MotorType::kBrushless};
};
