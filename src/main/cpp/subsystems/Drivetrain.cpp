// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

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
void Drivetrain::Drive(double right, double left, double lateral)
{
    m_gearbox->SetEveryone(right, left, lateral, Gearbox::PTOState::Driving);
}