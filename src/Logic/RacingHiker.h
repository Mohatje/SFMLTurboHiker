#pragma once
#include "Entity.h"

namespace turbohiker {
class RacingHiker : public Entity
{
public:
        void display() override;
        void update(float dTime) override;
        bool doTypeSpecificAction() override;

        EntityType getType() const override { return EntityType::RacingHiker; }

private:
        bool action = false;
        bool isMovingR = false;
        bool isMovingL = false;

        bool resetAIState = true;

        /**
         * Private Debugging method
         * @param pretext pretext
         */
        void printState(char* pretext);
};
} // namespace turbohiker
