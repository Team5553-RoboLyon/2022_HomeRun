// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Gearbox.h"

Gearbox::Gearbox()
{
    spdlog::trace("Gearbox()");
    m_NeoMotorRight.RestoreFactoryDefaults();
    m_NeoMotorRightFollower.RestoreFactoryDefaults();
    m_NeoMotorLeft.RestoreFactoryDefaults();
    m_NeoMotorLeftFollower.RestoreFactoryDefaults();

    m_NeoMotorLeft.SetOpenLoopRampRate(0.3);
    m_NeoMotorRight.SetOpenLoopRampRate(0.3);
    m_NeoMotorLeftFollower.SetOpenLoopRampRate(0.3);
    m_NeoMotorRightFollower.SetOpenLoopRampRate(0.3);

    m_NeoMotorLeft.EnableVoltageCompensation(10);
    m_NeoMotorRight.EnableVoltageCompensation(10);
    m_NeoMotorLeftFollower.EnableVoltageCompensation(10);
    m_NeoMotorRightFollower.EnableVoltageCompensation(10);

    m_NeoMotorLeft.SetSmartCurrentLimit(SMART_LIMIT_CURRENT_NEO);
    m_NeoMotorLeftFollower.SetSmartCurrentLimit(SMART_LIMIT_CURRENT_NEO);
    m_NeoMotorRight.SetSmartCurrentLimit(SMART_LIMIT_CURRENT_NEO);
    m_NeoMotorRightFollower.SetSmartCurrentLimit(SMART_LIMIT_CURRENT_NEO);

    m_NeoMotorRightFollower.Follow(m_NeoMotorRight);
    m_NeoMotorLeftFollower.Follow(m_NeoMotorLeft);

    m_NeoMotorLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorLeftFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_NeoMotorRightFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_NeoMotorLeft.SetInverted(true);
    m_NeoMotorLeftFollower.SetInverted(true);
    m_NeoMotorRight.SetInverted(false);
    m_NeoMotorRightFollower.SetInverted(false);

    m_NeoMotorLeft.GetEncoder().SetPosition(0);
    m_NeoMotorLeftFollower.GetEncoder().SetPosition(0);
    m_NeoMotorRight.GetEncoder().SetPosition(0);
    m_NeoMotorRightFollower.GetEncoder().SetPosition(0);

    m_solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void Gearbox::Periodic()
{
    spdlog::trace("Gearbox::Periodic()");
}

void Gearbox::Stop()
{
    spdlog::trace("Gearbox::Stop()");
    m_NeoMotorLeft.StopMotor();
    m_NeoMotorRight.StopMotor();
}

/**
 * @brief Sets the speed of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 * @param lateral Lateral pourcentage
 */
void Gearbox::SetEveryone(double right, double left, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetEveryone() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetEveryone({}, {}, {})", right, left, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.Set(left);
        m_NeoMotorRight.Set(right);
    }
}

void Gearbox::SetLeft(double left, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetLeft() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetLeft({}, {}, {})", 0.0, left, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.Set(left);
    }
}
void Gearbox::SetRight(double right, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetRight() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetRight({}, {}, {})", right, 0.0, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorRight.Set(right);
    }
}
void Gearbox::StopEveryOne(PTOState ptoConfigurationRequired)
{
    StopLeft(ptoConfigurationRequired);
    StopRight(ptoConfigurationRequired);
}

void Gearbox::StopLeft(PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::StopLeft() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::StopLeft()");
        m_NeoMotorLeft.StopMotor();
    }
}

void Gearbox::StopRight(PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::StopRight() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::StopRight()");
        m_NeoMotorRight.StopMotor();
    }
}
/**
 * @brief Gets the encoder values of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param encoderValues Array of 3 doubles where the encoder values will be stored
 */
void Gearbox::GetEncoderValues(double (&encoderValues)[2])
{
    spdlog::trace("Gearbox::GetEncoderValues()");
    encoderValues[0] = m_NeoMotorLeft.GetEncoder().GetPosition();
    encoderValues[1] = m_NeoMotorRight.GetEncoder().GetPosition();
}

std::string Gearbox::PTOStateIndexToString(PTOState ptoConfiguration)
{
    switch (ptoConfiguration)
    {
    case PTOState::Driving:
        return "Driving";
    case PTOState::Climbing:
        return "Climbing";
    default:
        return "None";
    }
}

Gearbox::PTOState Gearbox::GetPTOState()
{
    return m_ptoState;
}

void Gearbox::SetPTOState(PTOState ptoState)
{
    switch (ptoState)
    {
    case PTOState::Driving:
        m_solenoid.Set(frc::DoubleSolenoid::Value::kForward);
        m_ptoState = ptoState;
        break;
    case PTOState::Climbing:
        m_solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
        m_ptoState = ptoState;

        break;
    default:
        m_solenoid.Set(frc::DoubleSolenoid::Value::kOff);
        m_ptoState = PTOState::None;
        break;
    }
}