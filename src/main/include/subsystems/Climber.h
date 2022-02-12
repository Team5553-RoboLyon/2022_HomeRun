// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/SparkMaxRelativeEncoder.h>

#include "lib/wrappers/CANSparkMaxWrapper.h"
#include "Constants.h"

class Climber : public frc2::SubsystemBase
{
public:
    Climber();
    void ActiveMotor(double speed);
    double GetEncoderValue();
    void SetSetpoint(double setpoint);

private:
    CANSparkMaxWrapper m_NeoMotor{CLIMBER_NEO_MOTOR_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::SparkMaxRelativeEncoder m_NeoMotorEncoder = m_NeoMotor.GetEncoder();
    rev::SparkMaxPIDController m_NeoMotorPIDController = m_NeoMotor.GetPIDController();
};