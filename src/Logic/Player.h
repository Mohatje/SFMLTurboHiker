#pragma once
#include "Entity.h"

namespace turbohiker {

    class Player : public Entity {
    public:
        void display() override;
        void update(float dTime) override;
        bool doTypeSpecificAction() override;

        EntityType getType() const override { return EntityType::Player; }
    private:
    };

}