#pragma once
#include "Entity.h"

namespace turbohiker {

class PassingHiker2 : public Entity
{
public:
        void display() override;
        void update(float dTime) override;
        bool doTypeSpecificAction() override;

        /**
         * Method to see wether the Static Hiker is active or not (yelled at or not)
         * @return bool isActive
         */
        bool isActive() const;

        /**
         * Setter for the isActive flag of the Static Hiker
         * @param active boolean to which the flag should be set
         */
        void setActive(bool active);
        virtual void spawn(double playerY);

        EntityType getType() const override;

private:
        bool active = true;
};

} // namespace turbohiker
