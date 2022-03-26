// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <spdlog/spdlog.h>

#include "lib/RobotError.h"
#include "Constants.h"
#include "subsystems/Gearbox.h"

class Drivetrain : public frc2::SubsystemBase
{
public:
    Drivetrain(Gearbox *gearbox);
    void Periodic() override;
    void Stop();
    void Drive(double right, double left, double lateral);
    void Enable();
    void Disable();
    double GetEnabled();
    Gearbox *GetGearbox();

private:
    bool m_enabled = false;
    Gearbox *m_gearbox;
};
