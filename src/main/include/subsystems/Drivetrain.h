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
    void Drive(double right, double left);
    void Enable();
    void Disable();
    double GetEnabled();
    Gearbox *GetGearbox();

private:
    bool m_enabled = false;
    Gearbox *m_gearbox;
};