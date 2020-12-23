#pragma once
#include <utility>
#include <vector>
#include <memory>
#include "Observable.h"


namespace turbohiker {

    enum class EntityAIState {
        Invalid = 0,
        Default = 1,
        SpeedUp = 2,
        SlowDown = 3,
        RunR = 4,
        RunL = 5,
        Yell = 6,
        UnYell = 7,
        Stuck = 8,
        Idle = 9
    };

    enum class EntityType {
        Invalid = 0,
        Player = 1,
        RacingHiker = 2,
        StaticHikerActive = 3,
        StaticHikerInactive = 4,
        MovingHikerActive = 5, // Hiker/obstacle moving towards player
        MovingHikerInactive = 6,
        World = 7,
        Tile = 8
    };

    class Entity : public Observable {
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
        virtual bool doTypeSpecificAction() = 0;
        virtual void move(const std::pair<double, double>& offset);

        virtual EntityType getType() const = 0;

        virtual EntityAIState getCurState() const;

        virtual void setCurState(EntityAIState curState);

        bool isCurrentlyColliding() const;

        void setIsCurrentlyColliding(bool _isCurrentlyColliding);

//        int getScore() const;
//
//        void setScore(int score);

    private:
        std::pair<double, double> position {0.0, 0.0}; // x, y position (should be the middle of the entity by default)
        std::pair<double, double> velocity {0.0, 0.0}; // x, y velocity
        std::pair<double, double> size {1.0, 1.0}; // x = width, y = height
        std::pair<double, double> origin {0.0, 0.0}; // x = width, y = height

        EntityAIState curState = EntityAIState::Idle;

        bool currentlyColliding = false;
//        int score = 0;
    };
}
