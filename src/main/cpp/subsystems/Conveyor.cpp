#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_FeederMotor.ConfigFactoryDefault();
    m_ConveyorMotor.RestoreFactoryDefaults();

    m_ConveyorMotor.SetSmartCurrentLimit(SMART_LIMIT_CURRENT_NEO);

    m_FeederMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_FeederMotor.ConfigClosedloopRamp(0.5);
    m_ConveyorMotor.SetClosedLoopRampRate(0.5);

    m_ConveyorMotor.EnableVoltageCompensation(10);
    m_FeederMotor.EnableVoltageCompensation(10);

    m_FeederMotor.SetInverted(true);
    m_ConveyorMotor.SetInverted(false);
}

void Conveyor::StopAllMotors()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
    m_ConveyorMotor.Set(0);
}

void Conveyor::ActiveFeedingMotor()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, FEEDER_MOTOR_SPEED);
}

void Conveyor::UnblockConveyorMotor()
{
    m_ConveyorMotor.Set(-0.5);
}

void Conveyor::UnblockFeedingMotor()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.5);
}

void Conveyor::ActiveConveyorMotor()
{
    m_ConveyorMotor.Set(CONVEYOR_MOTOR_SPEED);
}

void Conveyor::StopFeedingMotor()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Conveyor::StopConveyorMotor()
{
    m_ConveyorMotor.Set(0);
}
