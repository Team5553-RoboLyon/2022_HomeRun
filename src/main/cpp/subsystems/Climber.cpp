#include "subsystems/Climber.h"

Climber::Climber()
{
    m_NeoMotor.RestoreFactoryDefaults();
}

void Climber::ActiveMotor(double speed) { m_NeoMotor.Set(speed); }

double Climber::GetEncoderValue() { return m_NeoMotorEncoder.GetPosition(); }
