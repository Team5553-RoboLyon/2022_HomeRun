// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <spdlog/spdlog.h>
#include "lib/wrappers/CANSparkMaxWrapper.h"
#include <frc/DoubleSolenoid.h>
#include <frc/Encoder.h>
#include <robolyon/HallSecurity.h>
#include <frc/DriverStation.h>

#include <frc/DigitalInput.h>

#include "lib/RobotError.h"
#include "Constants.h"
#include <units/angle.h>

class Gearbox : public frc2::SubsystemBase
{
public:
    enum class PTOState
    {
        Climbing,
        Driving,
        None
    };

    Gearbox();

    void Periodic();

    void Stop();

    void InitTeleopPeriod();

    void SetEveryone(double right, double left, PTOState ptoConfigurationRequired);
    void SetLeft(double left, PTOState ptoConfigurationRequired);
    void SetRight(double right, PTOState ptoConfigurationRequired);

    void SetVoltageEveryone(units::voltage::volt_t right, units::voltage::volt_t left, PTOState ptoConfigurationRequired);
    void SetVoltageLeft(units::voltage::volt_t left, PTOState ptoConfigurationRequired);
    void SetVoltageRight(units::voltage::volt_t right, PTOState ptoConfigurationRequired);

    void SetVoltageEveryone(units::voltage::volt_t r1, units::voltage::volt_t r2, units::voltage::volt_t l1, units::voltage::volt_t l2, PTOState ptoConfigurationRequired);
    void SetVoltageLeft(units::voltage::volt_t l1, units::voltage::volt_t l2, PTOState ptoConfigurationRequired);
    void SetVoltageRight(units::voltage::volt_t r1, units::voltage::volt_t r2, PTOState ptoConfigurationRequired);

    void StopEveryOne(PTOState ptoConfigurationRequired);
    void StopLeft(PTOState ptoConfigurationsRequired);
    void StopRight(PTOState ptoConfigurationRequired);

    void GetEncoderValues(double (&encoderValues)[2]);

    static std::string PTOStateIndexToString(PTOState ptoConfiguration);

    PTOState GetPTOState();

    void SetPTOState(PTOState ptoConfiguration);

private:
    CANSparkMaxWrapper m_NeoMotorRight{DRIVETRAIN_MOTOR_RIGHT_CAN_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorRightFollower{DRIVETRAIN_MOTOR_RIGHT_FOLLOWER_CAN_ID,
                                               rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorLeft{DRIVETRAIN_MOTOR_LEFT_CAN_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorLeftFollower{DRIVETRAIN_MOTOR_LEFT_FOLLOWER_CAN_ID,
                                              rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    frc::DoubleSolenoid m_solenoid{frc::PneumaticsModuleType::CTREPCM, DRIVETRAIN_SOLENOID_ID_FORWARD,
                                   DRIVETRAIN_SOLENOID_ID_REVERSE};

    frc::Encoder m_encodeurExterneDroite{DRIVETRAIN_ENCODER_EXTERN_RIGHT_A_ID, DRIVETRAIN_ENCODER_EXTERN_RIGHT_B_ID, false, frc::Encoder::k4X};
    frc::Encoder m_encodeurExterneGauche{DRIVETRAIN_ENCODER_EXTERN_LEFT_A_ID, DRIVETRAIN_ENCODER_EXTERN_LEFT_B_ID, true, frc::Encoder::k4X};

    PTOState m_ptoState = PTOState::Driving;
};
