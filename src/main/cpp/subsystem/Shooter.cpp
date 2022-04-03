#include "subsystem/Shooter.h"

void Shooter::Set(double speed)
{
    m_ShooterMotorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    m_ShooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void Shooter::Init()
{
    m_ShooterMotorLeft.ConfigFactoryDefault();
    m_ShooterMotorRight.ConfigFactoryDefault();

    m_ShooterMotorLeft.SetInverted(true);
    m_ShooterMotorRight.SetInverted(false);

    m_ShooterMotorLeft.ConfigVoltageCompSaturation(SHOOTER_VOLTAGE_COMPENSATION);
    m_ShooterMotorRight.ConfigVoltageCompSaturation(SHOOTER_VOLTAGE_COMPENSATION);

    m_ShooterMotorLeft.EnableVoltageCompensation(true);
    m_ShooterMotorRight.EnableVoltageCompensation(true);
}