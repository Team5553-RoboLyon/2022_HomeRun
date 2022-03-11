
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/Encoder.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

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

private:
    enum TurretState
    {
        unknownPosition,
        goTo0,
        ready,
    };
    ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{8};
    frc::Encoder m_encoderTurret{10, 11};
    frc::DigitalInput m_SensorHall{7};
    TurretState m_state = Turret::TurretState::ready;
};