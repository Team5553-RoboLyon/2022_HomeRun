// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <lib/wrappers/CANSparkMaxWrapper.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

#include "Constants.h"

class Intake : public frc2::SubsystemBase
{
public:
    Intake();
    void ActiveMotor();
    void UnblockMotor();
    void StopMotor();
    void Close();
    void Open();
    void ChangePosition();

private:
    bool IntakePosition = true;
    ctre::phoenix::motorcontrol::can::VictorSPX m_IntakeMotor{INTAKE_MOTOR_CAN_ID};
    frc::DoubleSolenoid m_IntakeSolenoid{frc::PneumaticsModuleType::CTREPCM, INTAKE_SOLENOID_ID_FORWARD, INTAKE_SOLENOID_ID_REVERSE};
};
