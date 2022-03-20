// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include "Constants.h"

class Shooter : public frc2::SubsystemBase
{
public:
    Shooter();
    void Shoot(double speed);

private:
    ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{SHOOTER_FALCON_MOTOR_ID};
    ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotorFollower{SHOOTER_FALCON_MOTOR_FOLLOWER_ID};
};