#include "subsystems/Intake.h"

Intake::Intake()
{
    m_IntakeMotor.SetInverted(false);
    // m_IntakeSolenoid.Set(frc::DoubleSolenoid::kForward);
}

void Intake::ActiveMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, INTAKE_MOTOR_SPEED);
}

void Intake::UnblockMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.5);
}

void Intake::StopMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Intake::Open()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
    IntakePosition = false;
    spdlog::debug("Open");
}

void Intake::Close()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kForward);
    IntakePosition = true;
    spdlog::debug("Close");
}

void Intake::ChangePosition()
{
    spdlog::debug("ChangePosition");
    if (IntakePosition)
    {
        Open();
    }
    else
    {
        Close();
    }
}
