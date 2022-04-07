#include "subsystems/Climber.h"

Climber::Climber(Gearbox *gearbox)
{
    m_gearbox = gearbox;
}

void Climber::Periodic()
{
    double outputClimber = m_pidcontroller.Calculate(units::degree_t{GetMeasurement()}, units::degree_t{m_setPoint});
    UseOutput(outputClimber, GetSetpoint());
    spdlog::trace("Drivetrain::Periodic()");
}
void Climber::Stop()
{
    spdlog::trace("Drivetrain::Stop()");
    m_gearbox->StopEveryOne(Gearbox::PTOState::Climbing);
}
void Climber::MoveRotatingArms(double speed) {}
void Climber::MoveClimber(double speed) {}

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
void Climber::UseOutput(double output, double setpoint)
{

    spdlog::trace("Drivetrain::UseOutput()");
    m_gearbox->SetRight(output, Gearbox::PTOState::Climbing);
    m_gearbox->SetLeft(0.1, Gearbox::PTOState::Climbing);
}
void Climber::SetSetpoint(double setpoint)
{
    spdlog::trace("Drivetrain::SetSetpointClimber(double setpointClimber)");
    m_setPoint = setpoint;
}
double Climber::GetSetpoint()
{
    spdlog::trace("Drivetrain::GetSetpointClimber()");
    return m_setPoint;
}

bool Climber::GetEnabled()
{
    return m_enabled;
}