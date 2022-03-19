#include <gtest/gtest.h>

#include <frc/DoubleSolenoid.h>
#include <frc/simulation/CTREPCMSim.h>
#include <frc/simulation/SimDeviceSim.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <rev/sim/CANSparkMax.h>

#include "subsystems/Drivetrain.h"
#include "Constants.h"

class DrivetrainTest : public testing::Test
{
protected:
    Drivetrain drivetrain;
    frc::sim::SimDeviceSim RightMotor{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_RIGHT_ID) + "]").c_str()};
    frc::sim::SimDeviceSim RightMotorFollower{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID) + "]").c_str()};
    frc::sim::SimDeviceSim LeftMotor{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_LEFT_ID) + "]").c_str()};
    frc::sim::SimDeviceSim LeftMotorFollower{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID) + "]").c_str()};
};

void callbackt(const char *valueName, HAL_SimValueHandle handle, int value, const HAL_Value *HALValue)
{
    spdlog::debug("{} = {}", valueName, value);
}
TEST_F(DrivetrainTest, MotorRightFollowerTest)
{
    drivetrain.Drive(0.76, 0.5, 0.2, Drivetrain::PTOState::Driving);
    EXPECT_EQ(RightMotorFollower.GetDouble("Setpoint").Get(), RightMotor.GetDouble("Setpoint").Get()); // Motor must be at speed
}

TEST_F(DrivetrainTest, MotorLeftFollowerTest)
{
    drivetrain.Drive(0.76, 0.5, 0.2, Drivetrain::PTOState::Driving);
    EXPECT_EQ(LeftMotorFollower.GetDouble("Setpoint").Get(), LeftMotor.GetDouble("Setpoint").Get()); // Motor must be at speed
}

/*
TEST_F(DrivetrainTest, MotorCorrectSpeedTest)
{
    drivetrain.Drive(0.76, 0.5, 0.2);
    EXPECT_EQ(RightMotor.GetDouble("Setpoint").Get(), 0.76); // Motor must be at speed
    EXPECT_EQ(LeftMotor.GetDouble("Setpoint").Get(), 0.5);   // Motor must be at speed
    EXPECT_EQ(FalconMotor.GetDouble("Setpoint").Get(), 0.2); // Motor must be at speed
}

TEST_F(DrivetrainTest, MotorOverspeedTest)
{
    drivetrain.Drive(1.5, 1.5, 1.5);
    EXPECT_EQ(RightMotor.GetDouble("Setpoint").Get(), 1);  // Motor must be at speed
    EXPECT_EQ(LeftMotor.GetDouble("Setpoint").Get(), 1);   // Motor must be at speed
    EXPECT_EQ(FalconMotor.GetDouble("Setpoint").Get(), 1); // Motor must be at speed
}
*/
