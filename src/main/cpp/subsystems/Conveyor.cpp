#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_FeederMotor.ConfigFactoryDefault();
    m_ConveyorMotor.RestoreFactoryDefaults();

    m_FeederMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_FeederMotor.SetInverted(false);
    m_ConveyorMotor.SetInverted(false);
}

void Conveyor::StopAllMotors()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ConveyorMotor.Set(0);
}

void Conveyor::ActiveFeedingMotor(double speed)
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Conveyor::ActiveConveyorMotor(double speed)
{
    m_ConveyorMotor.Set(speed);
}

void Conveyor::StopFeedingMotor()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Conveyor::StopConveyorMotor()
{
    m_ConveyorMotor.Set(0);
}
