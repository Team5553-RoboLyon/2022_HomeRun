#include <frc2/command/SubsystemBase.h>

#include "subsystems/Gearbox.h"

class Climber : public frc2::SubsystemBase
{

public:
    Climber(Gearbox *gearbox);
    void Periodic() override;
    void Stop();
    void MoveRotatingArms(double speed);
    void MoveClimber(double speed);

    void ResetEncoder();
    void Enable();
    void Disable();

    double GetMeasurement();
    void UseOutput(double output, double setpoint);
    void SetSetpoint(double setpoint);
    double GetSetpoint();

private:
    Gearbox *m_gearbox;
    enum state_Climber
    {
        initClimber,
        goTo0Climber,
        enableClimber,
        disableClimber,
    };
    enum state_RotatingArms
    {
        initRotatingArms,
        goTo0RotatingArms,
        enableRotatingArms,
        disableRotatingArms,
    };
    state_Climber m_state_Climber = Climber::state_Climber::initClimber;
    state_RotatingArms m_state_RotatingArms = Climber::state_RotatingArms::initRotatingArms;

    frc::ProfiledPIDController<units::degree> m_pidcontroller{
        CLIMBER_PID_P, CLIMBER_PID_I, CLIMBER_PID_D,
        frc::TrapezoidProfile<units::degree>::Constraints{5_deg / 1_s, 10_deg / (1_s * 1_s)}};
    frc::Encoder m_encoderClimber{10, 11};
    HallSecurity m_HallSensor{4};

    double m_setPoint = 0.0;

    frc::Encoder m_encoderRotatingArms{12, 13};
    frc::DigitalInput m_HallSensorRotatingArmRight{19};
    frc::DigitalInput m_HallSensorRotatingArmLeft{2};
};
