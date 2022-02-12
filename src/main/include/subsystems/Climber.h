// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"

class Climber : public frc2::SubsystemBase
{
public:
    Climber();
    void ActiveMotor(double speed);

private:
    rev::CANSparkMax m_NeoMotor{CLIMBER_NEO_MOTOR_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_NeoMotorFollower{CLIMBER_NEO_MOTOR_FOLLOWER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
};