
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

class Shooter : public frc2::SubsystemBase
{
public:
    void Set(double speed);
    void Init();

private:
    ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotorLeft{3};
    ctre::phoenix::motorcontrol::can::TalonFX m_ShooterMotorRight{4};
    double m_speedShooter;
};