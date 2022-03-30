
#include "subsystems/Drivetrain.h"

Drivetrain::Drivetrain(Gearbox *gearbox)
{
    m_gearbox = gearbox;
}

void Drivetrain::Periodic()
{
}

void Drivetrain::Stop()
{
}

void Drivetrain::Enable()
{
    m_enabled = true;
}

void Drivetrain::Disable()
{
    m_enabled = false;
}

double Drivetrain::GetEnabled()
{
    return m_enabled;
}

Gearbox *Drivetrain::GetGearbox()
{
    return m_gearbox;
}

/**
 * @brief Sets the speed of the left, right and lateral motors for OMNI_BASE
 * @warning  Does not work if the robot is TANK_BASE
 *
 * @param right Right wheels pourcentage
 * @param left Left wheels pourcentage
 * @param lateral Lateral pourcentage
 */
void Drivetrain::Drive(double right, double left)
{
    m_gearbox->SetEveryone(right, left, Gearbox::PTOState::Driving);
}