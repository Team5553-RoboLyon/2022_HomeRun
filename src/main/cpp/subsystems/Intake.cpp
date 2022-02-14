#include "subsystems/Intake.h"

Intake::Intake()
{
    m_IntakeMotor.RestoreFactoryDefaults();

    m_IntakeMotor.SetInverted(true);
}

void Intake::ActiveMotor()
{
    m_IntakeMotor.Set(INTAKE_MOTOR_SPEED);
}

void Intake::UnblockMotor()
{
    m_IntakeMotor.Set(-INTAKE_MOTOR_SPEED);
}

void Intake::StopMotor()
{
    m_IntakeMotor.Set(0.0);
}

void Intake::Open()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
}

void Intake::Close()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kForward);
}

void Intake::ChangePosition()
{
    if (m_IntakeSolenoid.Get() == frc::DoubleSolenoid::kReverse)
    {
        Open();
    }
    else
    {
        Close();
    }
}
