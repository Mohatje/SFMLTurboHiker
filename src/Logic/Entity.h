#pragma once
#include <utility>

namespace turbohiker {

    enum class EntityType {
        Invalid = 0,
        Player = 1,
        RacingHiker = 2,
        StaticHiker = 3,
        MovingHiker = 4, // Hiker/obstacle moving towards player
        World = 5,
        Tile = 6
    };

    class Entity {
    public:
        Entity() = default;
        Entity(const Entity &cpy) = default;
        virtual ~Entity() = default;

        virtual void setPosition(const std::pair<double, double> &_position);
        virtual void setVelocity(const std::pair<double, double> &_velocity);
        virtual void setSize(const std::pair<double, double> &_size);
        virtual void setOrigin(const std::pair<double, double> &_origin);

        virtual const std::pair<double, double> &getPosition() const;
        virtual const std::pair<double, double> &getVelocity() const;
        virtual const std::pair<double, double> &getSize() const;

        virtual void display() = 0;
        virtual void update(float dTime) = 0;
        virtual void doTypeSpecificAction() = 0;
        virtual void move(const std::pair<double, double>& offset);

        virtual EntityType getType() const = 0;

    private:
        std::pair<double, double> position {0.0, 0.0}; // x, y position (should be the middle of the entity by default)
        std::pair<double, double> velocity {0.0, 0.0}; // x, y velocity
        std::pair<double, double> size {1.0, 1.0}; // x = width, y = height
        std::pair<double, double> origin {0.0, 0.0}; // x = width, y = height
    };
}
