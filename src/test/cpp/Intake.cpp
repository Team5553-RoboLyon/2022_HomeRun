#include <gtest/gtest.h>

#include <frc/DoubleSolenoid.h>
#include <frc/simulation/CTREPCMSim.h>
#include <ctre/phoenix/motorcontrol/TalonFXSimCollection.h>

#include "subsystems/Intake.h"
#include "Constants.h"

class IntakeTest : public testing::Test
{
protected:
  Intake intake;                                                                                                                    // create our intake
  frc::sim::CA simMotor{Constants::Intake::MOTOR_PORT};                                                                             // create our simulation PWM
  frc::sim::CTREPCMSim simPiston{frc::PneumaticsModuleType::CTREPCM, Constants::Intake::PISTON_FWD, Constants::Intake::PISTON_REV}; // create our simulation solenoid
};

TEST_F(IntakeTest, DoesntWorkWhenClosed)
{
  intake.Retract();                           // close the intake
  intake.Activate(0.5);                       // try to activate the motor
  EXPECT_DOUBLE_EQ(0.0, simMotor.GetSpeed()); // make sure that the value set to the motor is 0
}

TEST_F(IntakeTest, WorksWhenOpen)
{
  intake.Deploy();
  intake.Activate(0.5);
  EXPECT_DOUBLE_EQ(0.5, simMotor.GetSpeed());
}

TEST_F(IntakeTest, RetractTest)
{
  intake.Retract();
  EXPECT_EQ(frc::DoubleSolenoid::Value::kReverse, simPiston.Get());
}

TEST_F(IntakeTest, DeployTest)
{
  intake.Deploy();
  EXPECT_EQ(frc::DoubleSolenoid::Value::kForward, simPiston.Get());
}