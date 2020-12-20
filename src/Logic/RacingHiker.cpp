#include "RacingHiker.h"
#include <iostream>

namespace turbohiker {


    void RacingHiker::display() {   }

    void RacingHiker::update(float dTime) {
        auto curVelocity = getVelocity();

        // Velocity decay, analogous to player
        curVelocity.first -= ( curVelocity.first * 8.0 * dTime );
        curVelocity.second -= ( curVelocity.second * 8.0 * dTime );

        if (getCurState() == EntityAIState::SpeedUp) {
            curVelocity.second += 40.0 * dTime;
        }

        if (getCurState() == EntityAIState::SlowDown) {
            curVelocity.second -= 30.0 * dTime;
        }

        if (getCurState() == EntityAIState::RunL) {
            curVelocity.first -= 20.0 * dTime;
        }

        if (getCurState() == EntityAIState::RunR) {
            curVelocity.first += 20.0 * dTime;
        }

        if (getCurState() == EntityAIState::Yell) {
            action = true;
        }

        if (getCurState() == EntityAIState::UnYell) {
            action = false;
        }

        setVelocity(curVelocity);
        move( {curVelocity.first * dTime, curVelocity.second * dTime} );
        setCurState(EntityAIState::Idle);
    }

    bool RacingHiker::doTypeSpecificAction() {
        return action;
    }

}