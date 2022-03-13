#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_ConveyorFeedingMotor.ConfigFactoryDefault();
    m_ConveyorMotor.RestoreFactoryDefaults();

    m_ConveyorFeedingMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_ConveyorFeedingMotor.SetInverted(false);
    m_ConveyorMotor.SetInverted(false);
}

void Conveyor::StopAllMotors()
{
    m_ConveyorFeedingMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ConveyorMotor.Set(0);
}

void Conveyor::ActiveFeedingMotor(double speed)
{
    m_ConveyorFeedingMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Conveyor::ActiveConveyorMotor(double speed)
{
    m_ConveyorMotor.Set(speed);
}

void Conveyor::StopFeedingMotor()
{
    m_ConveyorFeedingMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Conveyor::StopConveyorMotor()
{
    m_ConveyorMotor.Set(0);
}
