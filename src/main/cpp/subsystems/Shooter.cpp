#include "subsystems/Shooter.h"

Shooter::Shooter()
{
    m_FalconMotor.ConfigFactoryDefault();
    m_FalconMotorFollower.ConfigFactoryDefault();

    m_FalconMotor.SetInverted(false);
    m_FalconMotorFollower.SetInverted(true);

    m_FalconMotor.ConfigVoltageCompSaturation(11);
    m_FalconMotorFollower.ConfigVoltageCompSaturation(11);

    m_FalconMotorFollower.Follow(m_FalconMotor);
}

void Shooter::Shoot()
{
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.7);
}

void Shooter::StopMotors()
{
    m_FalconMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
}