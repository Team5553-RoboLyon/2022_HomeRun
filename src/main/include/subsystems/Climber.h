#pragma once

#include <frc2/command/SubsystemBase.h>

#include "subsystems/Gearbox.h"

class Climber : public frc2::SubsystemBase
{

public:
    Climber(Gearbox *gearbox);
    void Stop();
    void MoveRotatingArms(double speed);
    void MoveClimber(double speed);

    void ResetEncoder();
    void Enable();
    void Disable();

    double GetMeasurement();
    double GetSetpoint();
    bool GetEnabled();

private:
    Gearbox *m_gearbox;
    frc::Encoder m_encoderClimber{CLIMBER_LINEAR_ENCODER_ID_A, CLIMBER_LINEAR_ENCODER_ID_B};

    bool m_enabled = false;

    frc::Encoder m_encoderRotatingArms{CLIMBER_ROTATING_ENCODER_ID_A, CLIMBER_ROTATING_ENCODER_ID_B};
};
