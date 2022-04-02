// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Gearbox.h"

Gearbox::Gearbox()
{
    // TODO samrtcurent a 45 sans voltage compensation
    spdlog::trace("Gearbox()");
    m_NeoMotorRight.RestoreFactoryDefaults();
    m_NeoMotorRightFollower.RestoreFactoryDefaults();
    m_NeoMotorLeft.RestoreFactoryDefaults();
    m_NeoMotorLeftFollower.RestoreFactoryDefaults();

    m_NeoMotorLeft.SetOpenLoopRampRate(0.6);
    m_NeoMotorRight.SetOpenLoopRampRate(0.6);
    m_NeoMotorLeftFollower.SetOpenLoopRampRate(0.6);
    m_NeoMotorRightFollower.SetOpenLoopRampRate(0.6);

    // m_NeoMotorLeft.EnableVoltageCompensation(11);
    // m_NeoMotorRight.EnableVoltageCompensation(11);
    // m_NeoMotorLeftFollower.EnableVoltageCompensation(11);
    // m_NeoMotorRightFollower.EnableVoltageCompensation(11);

    m_NeoMotorLeft.SetSmartCurrentLimit(45);
    m_NeoMotorLeftFollower.SetSmartCurrentLimit(45);
    m_NeoMotorRight.SetSmartCurrentLimit(45);
    m_NeoMotorRightFollower.SetSmartCurrentLimit(45);

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

    m_solenoid.Set(frc::DoubleSolenoid::Value::kForward);
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

void Gearbox::InitTeleopPeriod()
{
    m_NeoMotorRightFollower.Follow(m_NeoMotorRight);
    m_NeoMotorLeftFollower.Follow(m_NeoMotorLeft);
}

/**
 * @brief Sets the speed of the left, right and lateral motors for TANK_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
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

void Gearbox::SetVoltageEveryone(units::voltage::volt_t right, units::voltage::volt_t left, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageEveryone() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageEveryone({}, {}, {})", right, left, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.SetVoltage(left);
        m_NeoMotorRight.SetVoltage(right);
    }
}

void Gearbox::SetVoltageLeft(units::voltage::volt_t left, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageLeft() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageLeft({}, {}, {})", 0.0, left, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.SetVoltage(left);
    }
}
void Gearbox::SetVoltageRight(units::voltage::volt_t right, PTOState ptoConfigurationRequired)
{
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageRight() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageLeft({}, {}, {})", right, 0.0, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorRight.SetVoltage(right);
    }
}

void Gearbox::SetVoltageEveryone(units::voltage::volt_t r1, units::voltage::volt_t r2, units::voltage::volt_t l1, units::voltage::volt_t l2, PTOState ptoConfigurationRequired)
{
    if (!frc::DriverStation::IsAutonomous())
    {
        spdlog::critical("Gearbox::SetVoltageEveryone() Robot is not in Autonomous mode !!!!");
        return;
    }
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageEveryone() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageEveryone({}, {}, {}, {}, {})", r1, r2, l1, l2, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.SetVoltage(l1);
        m_NeoMotorLeftFollower.SetVoltage(l2);
        m_NeoMotorRight.SetVoltage(r1);
        m_NeoMotorRightFollower.SetVoltage(r2);
    }
}

void Gearbox::SetVoltageLeft(units::voltage::volt_t l1, units::voltage::volt_t l2, PTOState ptoConfigurationRequired)
{
    if (!frc::DriverStation::IsAutonomous())
    {
        spdlog::critical("Gearbox::SetVoltageLeft() Robot is not in Autonomous mode !!!!");
        return;
    }

    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageLeft() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageLeft({}, {}, {})", l1, l2, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorLeft.SetVoltage(l1);
        m_NeoMotorLeftFollower.SetVoltage(l2);
    }
}
void Gearbox::SetVoltageRight(units::voltage::volt_t r1, units::voltage::volt_t r2, PTOState ptoConfigurationRequired)
{
    if (!frc::DriverStation::IsAutonomous())
    {
        spdlog::critical("Gearbox::SetVoltageRight() Robot is not in Autonomous mode !!!!");
        return;
    }
    if (ptoConfigurationRequired != m_ptoState)
    {
        spdlog::warn("Gearbox::SetVoltageRight() Asked to move with PTO in \"{}\" while current state is \"{}\"", PTOStateIndexToString(ptoConfigurationRequired), PTOStateIndexToString(m_ptoState));
    }
    else
    {
        spdlog::trace("Gearbox::SetVoltageLeft({}, {}, {})", r1, r2, PTOStateIndexToString(ptoConfigurationRequired));
        m_NeoMotorRight.SetVoltage(r1);
        m_NeoMotorRightFollower.SetVoltage(r2);
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
 * @brief Gets the encoder values of the left and right external encoders
 *
 * @param encoderValues Array of 2 doubles where the encoder values will be stored
 */
void Gearbox::GetEncoderValues(double (&encoderValues)[2])
{
    spdlog::trace("Gearbox::GetEncoderValues()");
    encoderValues[0] = m_encodeurExterneGauche.GetRaw();
    encoderValues[1] = m_encodeurExterneDroite.GetRaw();
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