//
// Created by eymeric on 13/03/2022.
//

#include "HallSecurity.h"


HallSecurity::HallSecurity(int hallDIO, double tolerance) {
    m_SensorHall = new frc::DigitalInput{hallDIO};
    m_tolerance = tolerance;
}

HallSecurity::HallSecurity(int hallDIO) {
    m_SensorHall = new frc::DigitalInput{hallDIO};
    m_tolerance = 0.3;
}

HallSecurity::~HallSecurity() {
    delete m_SensorHall;
}

void HallSecurity::setInverted(bool inverted) {
    m_inverted = inverted;
}

bool HallSecurity::ShouldIStop(double currentPosition, int outputSigne) {
    if (m_inverted) {
        outputSigne = -outputSigne;
    }
    m_DeltaPosition = currentPosition - m_PositionBefore;
    if (m_DeltaPosition > -m_tolerance && m_DeltaPosition < m_tolerance) {
        m_DeltaPosition = 0;
    }
    m_PositionBefore = currentPosition;
    bool retour = false;
    switch (m_state) {
        case HallSecurity::state::maxMin_Direction:
            spdlog::info(stateToString(m_state));
            if (MagnetDetected()) {
                if (m_DeltaPosition > 0) {
                    if (outputSigne > 0) {
                        retour = true;
                    }
                    m_state = HallSecurity::state::max_Direction;
                } else if (m_DeltaPosition < 0) {
                    if (outputSigne < 0) {
                        retour = true;
                    }
                    m_state = HallSecurity::state::min_Direction;
                }
            }
            break;
        case HallSecurity::state::min_Direction:
            spdlog::info(stateToString(m_state));
            if (outputSigne < 0) {
                retour = true;
            }
            if (!MagnetDetected()) {
                m_state = HallSecurity::state::maxMin_Direction;
            }
            break;

        case HallSecurity::state::max_Direction:
            spdlog::info(stateToString(m_state));
            if (outputSigne > 0) {
                retour = true;
            }
            if (!MagnetDetected()) {
                m_state = HallSecurity::state::maxMin_Direction;
            }
            break;
        default:
            break;
    }
    return retour;
}

bool HallSecurity::MagnetDetected() {
    return !m_SensorHall->Get();
}

std::string HallSecurity::stateToString(HallSecurity::state state) {
    switch (state) {
        case HallSecurity::state::min_Direction:
            return "min_Direction";
        case HallSecurity::state::max_Direction:
            return "max_Direction";
        case HallSecurity::state::maxMin_Direction:
            return "maxMin_Direction";
        default:
            return "";
    }
}
