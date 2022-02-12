#include "subsystems/Climber.h"

Climber::Climber()
{
    m_NeoMotor.RestoreFactoryDefaults();

    m_NeoMotorPIDController.SetP(CLIMBER_PID_P);
    m_NeoMotorPIDController.SetI(CLIMBER_PID_I);
    m_NeoMotorPIDController.SetD(CLIMBER_PID_D);

    m_NeoMotorEncoder.SetPosition(0);
    m_NeoMotorEncoder.SetPositionConversionFactor(CLIMBER_ENCODER_CONVERSION_FACTOR);
}

void Climber::ActiveMotor(double speed) { m_NeoMotor.Set(speed); }

double Climber::GetEncoderValue() { return m_NeoMotorEncoder.GetPosition(); }

void Climber::SetSetpoint(double setpoint) { m_NeoMotorPIDController.SetReference(setpoint, rev::ControlType::kPosition); }
