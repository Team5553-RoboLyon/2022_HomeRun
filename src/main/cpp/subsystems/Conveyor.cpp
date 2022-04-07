#include "subsystems/Conveyor.h"

Conveyor::Conveyor()
{
    m_FeederMotor.ConfigFactoryDefault();
    m_ConveyorMotor.RestoreFactoryDefaults();

    m_ConveyorMotor.SetSmartCurrentLimit(CONVEYOR_CURRENT_LIMIT);

    m_FeederMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
    m_ConveyorMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

    m_FeederMotor.ConfigClosedloopRamp(FEEDER_RAMP_RATE);
    m_ConveyorMotor.SetClosedLoopRampRate(CONVEYOR_RAMP_RATE);

    m_ConveyorMotor.EnableVoltageCompensation(CONVEYOR_VOLTAGE_COMPENSATION);
    m_FeederMotor.EnableVoltageCompensation(true);
    m_FeederMotor.ConfigVoltageCompSaturation(FEEDER_VOLTAGE_COMPENSATION);

    m_FeederMotor.SetInverted(false);
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
    m_ConveyorMotor.Set(CONVEYOR_UNBLOCK_SPEED);
}

void Conveyor::UnblockFeedingMotor()
{
    m_FeederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, FEEDER_UNBLOCK_SPEED);
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
