#include "subsystems/Shooter.h"

Shooter::Shooter()
{
    m_FalconMotor.ConfigFactoryDefault();
    m_FalconMotorFollower.ConfigFactoryDefault();

    m_FalconMotor.SetInverted(true);
    m_FalconMotorFollower.SetInverted(false);

    m_FalconMotor.ConfigVoltageCompSaturation(11);
    m_FalconMotorFollower.ConfigVoltageCompSaturation(11);

    m_FalconMotorFollower.Follow(m_FalconMotor);
}

void Shooter::Shoot(double speed)
{
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}