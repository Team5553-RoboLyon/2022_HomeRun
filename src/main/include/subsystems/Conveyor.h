// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <rev/CANSparkMax.h>

#include "Constants.h"

class Conveyor : public frc2::SubsystemBase
{
public:
    Conveyor();
    void StopAllMotors();
    void ActiveEntryMotor(double speed);
    void ActiveExitMotor(double speed);
    void ActiveConveyorMotor(double speed);
    void StopEntryMotor();
    void StopExitMotor();
    void StopConveyorMotor();

private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_ConveyorEntryMotor{CONVEYOR_MOTOR_ID};
    ctre::phoenix::motorcontrol::can::VictorSPX m_ConveyorExitMotor{CONVEYOR_EXIT_MOTOR_ID};
    rev::CANSparkMax m_ConveyorMotor{CONVEYOR_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
};