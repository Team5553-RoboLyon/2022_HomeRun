// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include "Constants.h"

class Feeder : public frc2::SubsystemBase
{
public:
    Feeder();

private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_FeederMotor{FEEDER_MOTOR_ID};
};