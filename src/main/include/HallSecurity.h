//
// Created by eymeric on 13/03/2022.
//

#include <frc/DigitalInput.h>
#include <spdlog/spdlog.h>


class HallSecurity {

public:
    HallSecurity(int hallDIO);

    HallSecurity(int hallDIO, double tolerance);

    ~HallSecurity();

    void setInverted(bool inverted);

    bool ShouldIStop(double currentPosition, int outputSigne);

    bool MagnetDetected();

private:
    enum state {
        max_Direction,
        min_Direction,
        maxMin_Direction,
    };

    std::string stateToString(state state);

    frc::DigitalInput *m_SensorHall;
    double m_DeltaPosition = 0.0;
    double m_PositionBefore = 0.0;
    double m_tolerance;
    bool m_inverted = false;
    HallSecurity::state m_state = HallSecurity::state::maxMin_Direction;
};






