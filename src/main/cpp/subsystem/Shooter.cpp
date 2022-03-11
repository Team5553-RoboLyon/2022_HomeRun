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

    m_ShooterMotorLeft.ConfigVoltageCompSaturation(11.0);
    m_ShooterMotorRight.ConfigVoltageCompSaturation(11.0);
}
