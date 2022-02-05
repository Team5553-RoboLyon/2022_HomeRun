#include <gtest/gtest.h>

#include <frc/DoubleSolenoid.h>
#include <frc/simulation/SimDeviceSim.h>
#include <frc/simulation/CTREPCMSim.h>

#include "subsystems/Intake.h"
#include "Constants.h"

class IntakeTest : public testing::Test
{
protected:
  Intake intake;                                       // create our intake
  frc::sim::SimDeviceSim intakeMotor{"SPARK MAX [7]"}; // create our intake motor
  frc::sim::CTREPCMSim PCM;
};

TEST_F(IntakeTest, CloseTest)
{
  intake.Close();
  EXPECT_EQ(true, PCM.GetSolenoidOutput(INTAKE_SOLENOID_1_ID));  // Forward channel must be 0 for closed
  EXPECT_EQ(false, PCM.GetSolenoidOutput(INTAKE_SOLENOID_2_ID)); // Reverse channel must be 1 for closed
}

TEST_F(IntakeTest, OpenTest)
{
  intake.Open();
  EXPECT_EQ(false, PCM.GetSolenoidOutput(INTAKE_SOLENOID_1_ID)); // Forward channel must be 1 for opened
  EXPECT_EQ(true, PCM.GetSolenoidOutput(INTAKE_SOLENOID_2_ID));  // Reverse channel must be 0 for opened
}

TEST_F(IntakeTest, MotorForwardTest)
{
  intake.ActiveMotor();
  intakeMotor.EnumerateValues()
  //EXPECT_EQ(INTAKE_MOTOR_SPEED, intakeMotor.("MotorControl")); // Motor must be at speed
}