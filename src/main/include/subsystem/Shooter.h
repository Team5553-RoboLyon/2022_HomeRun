
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>
#include "Constants.h"

class Shooter : public frc2::SubsystemBase
{
public:
    void Set(double speed);
    void Init();

private:
    ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotorLeft{SHOOTER_MOTOR_LEFT_CAN_ID};
    ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotorRight{SHOOTER_MOTOR_RIGHT_CAN_ID};
    double m_speedShooter;
};