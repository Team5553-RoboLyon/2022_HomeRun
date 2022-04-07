#include "subsystems/Intake.h"

Intake::Intake()
{
    m_IntakeMotor.SetInverted(false);
    m_IntakeMotor.ConfigClosedloopRamp(INTAKE_RAMP_RATE);
    m_IntakeMotor.EnableVoltageCompensation(INTAKE_VOLTAGE_COMPENSATION);
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
}

void Intake::ActiveMotor()
{
    if (IntakePosition)
    {
        m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, INTAKE_MOTOR_SPEED);
    }
    else
    {
        StopMotor();
    }
}

void Intake::UnblockMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, INTAKE_UNBLOCK_SPEED);
}

void Intake::StopMotor()
{
    m_IntakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Intake::Open()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kForward);
    IntakePosition = false;
    spdlog::debug("Open");
}

void Intake::Close()
{
    m_IntakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
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
