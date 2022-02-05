#include "subsystems/Intake.h"

Intake::Intake()
{
    m_IntakeMotor.SetInverted(true);
}

void Intake::ActiveMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::VictorSPXControlMode::PercentOutput, INTAKE_MOTOR_SPEED);
}

void Intake::UnblockMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::VictorSPXControlMode::PercentOutput, -INTAKE_MOTOR_DEBLOQUED_SPEED);
}

void Intake::StopMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::VictorSPXControlMode::PercentOutput, 0.0);
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
