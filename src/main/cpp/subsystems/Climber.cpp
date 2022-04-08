#include "subsystems/Climber.h"

Climber::Climber(Gearbox *gearbox)
{
    m_gearbox = gearbox;
    Disable();
}

void Climber::Stop()
{
    spdlog::trace("Drivetrain::Stop()");
    m_gearbox->StopEveryOne(Gearbox::PTOState::Climbing);
}
void Climber::MoveRotatingArms(double speed)
{
    m_gearbox->SetLeft(speed, Gearbox::PTOState::Climbing);
}
void Climber::MoveClimber(double speed)
{
    m_gearbox->SetRight(speed, Gearbox::PTOState::Climbing);
}

void Climber::ResetEncoder()
{
    spdlog::trace("Drivetrain::ResetEncoderClimber()");
    m_encoderClimber.Reset();
}
void Climber::Enable()
{
    m_enabled = true;
    m_gearbox->SetPTOState(Gearbox::PTOState::Climbing);
}
void Climber::Disable()
{
    m_enabled = false;
    m_gearbox->SetPTOState(Gearbox::PTOState::Driving);
}

double Climber::GetMeasurement()
{
    spdlog::trace("Drivetrain::GetMeasurementClimber()");
    return m_encoderClimber.GetDistance();
}

bool Climber::GetEnabled()
{
    return m_enabled;
}