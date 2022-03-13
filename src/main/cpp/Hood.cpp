// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Hood.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>

Hood::Hood()
        : PIDSubsystem(frc2::PIDController{0.035, 0.008, 0.0004}) {
    m_encoderHood.SetDistancePerRotation(-(58 / 4.2));

    Enable();
    SetSetpoint(0.0);

    m_HoodMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_HoodMotor.SetInverted(true);
    GetController().SetIntegratorRange(-5, 5);

    m_hallSecurity.setInverted(true);//TODO verifier ca mais je pense que c'est vrai

}

void Hood::ResetEncoders() {
    while (!m_encoderHood.IsConnected()) {
    }
    m_encoderHood.Reset();
}

double Hood::GetMeasurement() {
    return GetEncoder();
}

void Hood::UseOutput(double output, double setpoint) {
    switch (m_state) {
        case Hood::state::Init:
            if (m_hallSecurity.MagnetDetected()) {
                m_state = Hood::state::Ready;
                ResetEncoders();
                SetSetpoint(0.0);
            } else {
                SetSetpoint(-60.0);
                if (!m_hallSecurity.ShouldIStop(GetMeasurement(), wpi::sgn(output)){
                m_HoodMotor.Set(std::clamp(output, -0.1, 0.1));
            } else {
                m_HoodMotor.Set(0.0);
            }
            break;

        case Hood::state::Ready:
            if (m_hallSecurity.ShouldIStop(GetMeasurement(), wpi::sgn(output)) {
                m_HoodMotor.SetVoltage(units::volt_t(output) + feedforward.Calculate(10_mps, 20_mps_sq));
            } else {
                m_HoodMotor.Set(0.0);
            }
            break;
        default:
            break;
    }
    frc::SmartDashboard::PutNumber("outputHood", output);
}

double Hood::GetEncoder() {
    return m_encoderHood.GetDistance();
}

void Hood::SetPID(double p, double i, double d) {
    this->GetController().SetP(p);
    this->GetController().SetI(i);
    this->GetController().SetD(d);
}
