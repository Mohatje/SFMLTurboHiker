#include "RacingHiker.h"
#include <iostream>

namespace turbohiker {


    void RacingHiker::display() {   }

    void RacingHiker::update(float dTime) {
        auto curPosition = getPosition();
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

        if (getCurState() == EntityAIState::RunL || isMovingL) {
            curVelocity.first -= 20.0 * dTime;
        }

        if (getCurState() == EntityAIState::RunR || isMovingR) {
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



        auto posAfter = getPosition();
        double dx = posAfter.first - curPosition.first;
        double dy = posAfter.second - curPosition.second;
        if (std::abs(dx) < 0.05) {

        }
        if (std::abs(dy) < 0.02) {

        }
        setCurState(EntityAIState::Idle);
    }

    bool RacingHiker::doTypeSpecificAction() {
        return action;
    }

    void RacingHiker::printState(char* pretext) {
        printf("%s\n", pretext);
        printf("Stuck %d\n", getCurState() == EntityAIState::Stuck);
        printf("MovingR %d\n", isMovingR);
        printf("MovingL %d\n", isMovingL);
        printf("CurPosition: %.3f, %.3f\n\n", getPosition().first, getPosition().second);
    }

}