#include <gtest/gtest.h>

#include <frc/DoubleSolenoid.h>
#include <frc/simulation/CTREPCMSim.h>
#include <frc/simulation/SimDeviceSim.h>
#include <rev/sim/CANSparkMax.h>

#include "subsystems/Drivetrain.h"
#include "Constants.h"

class DrivetrainTest : public testing::Test
{
protected:
    Drivetrain drivetrain;                                                                                                                      // create our intake
    frc::sim::SimDeviceSim RightMotor{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_RIGHT_ID) + "]").c_str()};                  // create our intake motor
    frc::sim::SimDeviceSim RightMotorFollower{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_RIGHT_FOLLOWER_ID) + "]").c_str()}; // create our intake motor
    frc::sim::SimDeviceSim LeftMotor{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_LEFT_ID) + "]").c_str()};                    // create our intake motor
    frc::sim::SimDeviceSim LeftMotorFollower{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_NEO_MOTOR_LEFT_FOLLOWER_ID) + "]").c_str()};   // create our intake motor
#if IS_DRIVETRAIN_OMNIBASE
    frc::sim::SimDeviceSim FalconMotor{("WRAPPER::SPARK MAX [" + std::to_string(DRIVETRAIN_FALCON_MOTOR_OMNI_ID) + "]").c_str()};
#endif
};

TEST_F(DrivetrainTest, MotorRightFollowerTest)
{
    drivetrain.Drive(0.76, 0.0, 0.0);
    std::cout << RightMotorFollower.GetDouble("Setpoint").Get() << ":" << RightMotor.GetDouble("Setpoint").Get() << std::endl;
    EXPECT_EQ(RightMotorFollower.GetDouble("Setpoint").Get(), RightMotor.GetDouble("Setpoint").Get()); // Motor must be at speed
}