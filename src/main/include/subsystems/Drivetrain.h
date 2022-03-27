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

#include <frc/DigitalInput.h>

#include "lib/RobotError.h"
#include "Constants.h"
#include <units/angle.h>

class Drivetrain : public frc2::SubsystemBase
{
public:
    enum class PTOState
    {
        Climbing,
        Driving,
        None
    };

    Drivetrain();

    void Periodic() override;

    void Stop();

    void Drive(double right, double left, double lateral, PTOState ptoConfigurationRequired);

    void GetEncoderValues(double (&encoderValues)[3]);

    double GetFalconSimulatedOutput();

    static std::string PTOStateIndexToString(PTOState ptoConfiguration);

    PTOState GetPTOState();

    void SetPTOState(PTOState ptoConfiguration);

    void ResetEncoderClimber();

    void EnableClimber();

    void DisableClimber();

    void EnableRotatingArms();

    void DisableRotatingArms();

    void UseOutputClimber(double outputClimber, double setpointClimber);

    double GetMeasurementClimber();

    void SetSetpointClimber(double setpointClimber);

    double GetSetpointClimber();

    void ChangeDrivePosition();
    bool DrivePosition = true;

private:
    CANSparkMaxWrapper m_NeoMotorRight{DRIVETRAIN_NEO_MOTOR_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorRightFollower{DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID,
                                               rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorLeft{DRIVETRAIN_NEO_MOTOR_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    CANSparkMaxWrapper m_NeoMotorLeftFollower{DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID,
                                              rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    ctre::phoenix::motorcontrol::can::TalonFX m_FalconMotor{DRIVETRAIN_FALCON_MOTOR_OMNI_ID};

    frc::DoubleSolenoid m_solenoid{frc::PneumaticsModuleType::CTREPCM, DRIVETRAIN_SOLENOID_ID_FORWARD,
                                   DRIVETRAIN_SOLENOID_ID_REVERSE};
    PTOState m_ptoState = PTOState::None;

    enum state_Climber
    {
        init,
        goTo0,
        enable,
        disable,
    };

    enum state_RotatingArms
    {
        initRotate,
        goTo0Rotate,
        enableRotate,
        disableRotate,
    };
    state_Climber m_state_Climber = Drivetrain::state_Climber::init;
    state_RotatingArms m_state_RotatingArms = Drivetrain::state_RotatingArms::initRotate;

    frc::ProfiledPIDController<units::degree> m_pidcontroller{
        CLIMBER_PID_P, CLIMBER_PID_I, CLIMBER_PID_D,
        frc::TrapezoidProfile<units::degree>::Constraints{5_deg / 1_s, 10_deg / (1_s * 1_s)}};
    frc::Encoder m_encoderClimber{12, 13};
    HallSecurity m_HallSensorClimber{4};
    double m_setPointClimber = 0.0;

    frc::Encoder m_encoderRotatingArms{14, 15};
    frc::DigitalInput m_HallSensorRotatingArmRight{19};
    frc::DigitalInput m_HallSensorRotatingArmLeft{2};
};