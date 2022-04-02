// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Camera.h"
#include <frc/smartdashboard/SmartDashboard.h>

Camera::Camera() = default;

// This method will be called once per scheduler run
void Camera::Periodic() {}

void Camera::DisableLED()
{
    m_camera.SetLEDMode(photonlib::LEDMode::kOff);
}

void Camera::EnableLED() { m_camera.SetLEDMode(photonlib::LEDMode::kOn); }

void Camera::GetDistance()
{
    photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();

    if (result.HasTargets())
    {
        units::length::meter_t range = photonlib::PhotonUtils::CalculateDistanceToTarget(
            units::length::meter_t{CAMERA_HEIGHT}, units::length::meter_t{TARGET_HEIGHT}, units::angle::radian_t{CAMERA_PITCH},
            units::degree_t{result.GetBestTarget().GetPitch()});

        frc::SmartDashboard::PutNumber("distance cible", double{range});
    }
}