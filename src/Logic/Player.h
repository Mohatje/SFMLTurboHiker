#pragma once
#include "Entity.h"

namespace turbohiker {

    class Player : public Entity {
    public:
        void display() override;
        void update(float dTime) override;
        void doTypeSpecificAction() override;
        bool yellAtObstacle();

        EntityType getType() const override { return EntityType::Player; }
    private:
    };

}