#include "RacingHiker.h"
#include <iostream>

namespace turbohiker {

void RacingHiker::display() {}

void RacingHiker::update(float dTime)
{
        auto curPosition = getPosition();
        auto curVelocity = getVelocity();

        // Velocity decay, analogous to player
        curVelocity.first -= (curVelocity.first * 8.0 * dTime);
        curVelocity.second -= (curVelocity.second * 8.0 * dTime);

        // Movement handling, just like with PassingHiker2 (moving hiker)
        // Based on AI movement
        switch (getCurState()) {
        case EntityAIState::Default:
                return;
        case EntityAIState::SpeedUp:
                curVelocity.second += 40.0 * dTime;
                break;
        case EntityAIState::SlowDown:
                curVelocity.second -= 30.0 * dTime;
                break;
        case EntityAIState::RunR:
                curVelocity.first += 20.0 * dTime;
                break;
        case EntityAIState::RunL:
                curVelocity.first -= 20.0 * dTime;
                break;
        case EntityAIState::Yell:
                action = true;
                break;
        case EntityAIState::UnYell:
                action = false;
                break;
        }

        setVelocity(curVelocity);
        move({curVelocity.first * dTime, curVelocity.second * dTime});

        auto posAfter = getPosition();

        // pathetic attempt at solving AI movement inconsistency, this is a very hacky way and I don't like it
        // can't afford to spend more time on this
        resetAIState = (posAfter.first <= 3.0 && posAfter.first >= -3.0) ||
                       (!(getCurState() == EntityAIState::RunL || getCurState() == EntityAIState::RunR)) ||

                       ((getCurState() == EntityAIState::RunR && curPosition.first >= 3.5) ||
                        (getCurState() == EntityAIState::RunL && curPosition.first <= -3.5));

        if (resetAIState) {
                setCurState(EntityAIState::Idle);
        }
}

bool RacingHiker::doTypeSpecificAction() { return action; }

void RacingHiker::printState(char* pretext)
{
        // debug output
        printf("%s\n", pretext);
        printf("Stuck %d\n", getCurState() == EntityAIState::Stuck);
        printf("MovingR %d\n", isMovingR);
        printf("MovingL %d\n", isMovingL);
        printf("CurPosition: %.3f, %.3f\n\n", getPosition().first, getPosition().second);
}

} // namespace turbohiker