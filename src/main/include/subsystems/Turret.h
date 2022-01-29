// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

#include "Constants.h"

class Turret : public frc2::SubsystemBase
{
public:
    Turret();

private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_TurretMotor{TURRET_MOTOR_ID};
};