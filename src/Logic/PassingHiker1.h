#pragma once
#include "Entity.h"

namespace turbohiker {

    class PassingHiker1 : public Entity {
    public:
        void display() override;
        void update(float dTime) override;
        bool doTypeSpecificAction() override;

        bool isActive() const;

        void setActive(bool active);

        EntityType getType() const override;
    private:
        bool active = true;
    };

}