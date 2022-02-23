#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_ConveyorEntryMotor.ConfigFactoryDefault();
    m_ConveyorMotor.RestoreFactoryDefaults();
    m_ConveyorExitMotor.ConfigFactoryDefault();

    m_ConveyorEntryMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_ConveyorExitMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);

    m_ConveyorEntryMotor.SetInverted(false);
    m_ConveyorMotor.SetInverted(false);
    m_ConveyorExitMotor.SetInverted(false);
}

void Conveyor::StopAllMotors()
{
    m_ConveyorEntryMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ConveyorMotor.Set(0);
    m_ConveyorExitMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}

void Conveyor::ActiveEntryMotor(double speed)
{
    m_ConveyorEntryMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Conveyor::ActiveExitMotor(double speed)
{
    m_ConveyorExitMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Conveyor::ActiveConveyorMotor(double speed)
{
    m_ConveyorMotor.Set(speed);
}

void Conveyor::StopEntryMotor()
{
    m_ConveyorEntryMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Conveyor::StopExitMotor()
{
    m_ConveyorExitMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Conveyor::StopConveyorMotor()
{
    m_ConveyorMotor.Set(0);
}
