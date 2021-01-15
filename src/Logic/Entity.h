#pragma once
#include "Observable.h"
#include <memory>
#include <utility>
#include <vector>

namespace turbohiker {

enum class EntityAIState
{
        Invalid = 0,
        Default = 1,
        SpeedUp = 2,
        SlowDown = 3,
        RunR = 4,
        RunL = 5,
        Yell = 6,
        UnYell = 7,
        Stuck = 8,
        Finished = 9,
        Idle = 10
};

enum class EntityType
{
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

class Entity : public Observable
{
public:
        /**
         * Default Constructor
         */
        Entity() = default;
        /**
         * Default copy constructor
         * @param cpy other entity
         */
        Entity(const Entity& cpy) = default;
        /**
         * Default Destructor
         */
        virtual ~Entity() = default;

        /**
         * Sets position of said entity to the provided position
         * @param _position a tuple containing doubles indicating the position
         */
        virtual void setPosition(const std::pair<double, double>& _position);

        /**
         * Sets velocity of said entity to the provided velocity
         * @param _velocity a tuple containing doubles indicating the velocity
         */
        virtual void setVelocity(const std::pair<double, double>& _velocity);

        /**
         * Sets size of said entity to the provided size
         * @param _size a tuple containing doubles indicating the set
         */
        virtual void setSize(const std::pair<double, double>& _size);

        /**
         * Sets origin of said entity to the provided origin (relative to entity size)
         * @param _origin a tuple containing doubles indicating the new origin
         */
        virtual void setOrigin(const std::pair<double, double>& _origin);

        /**
         * Getter for the entity's position
         * @return tuple containing doubles indicating position
         */
        virtual const std::pair<double, double>& getPosition() const;

        /**
         * Getter for the entity's velocity
         * @return tuple containing doubles indicating velocity
         */
        virtual const std::pair<double, double>& getVelocity() const;

        /**
         * Getter for the entity's size
         * @return tuple containing doubles indicating size
         */
        virtual const std::pair<double, double>& getSize() const;

        /**
         * Display function which handles the drawing of this entity.
         */
        virtual void display() = 0;

        /**
         * Update function, handles things such as input control and movement
         * @param dTime time between frames, this is a fixed timestep by default. Used to have uniform movement (not
         * tied to fps)
         */
        virtual void update(float dTime) = 0;

        /**
         * Attempts to do an action specific to each entity type.
         * @return whether the action resulted in success or not
         */
        virtual bool doTypeSpecificAction() = 0;

        /**
         * Method to move the entity by an offset \n
         * Thus the entity is moved relative to its position
         * @param offset a tuple of doubles as the offset
         */
        virtual void move(const std::pair<double, double>& offset);

        /**
         * Getter for the type of entity
         * @return which type the callee entity is.
         */
        virtual EntityType getType() const = 0;

        /**
         * Getter for the Entity State
         * @return the current state that the entity is in
         */
        virtual EntityAIState getCurState() const;

        /**
         * Sets the state of said entity to the provided state
         * @param curState an EntityAIState Enum
         */
        virtual void setCurState(EntityAIState curState);

        /**
         * Method to check whether the entity is currently colliding with another entity or not
         * @return true if entity is colliding otherwise false
         */
        bool isCurrentlyColliding() const;

        /**
         * Sets the collision state of said entity to the provided boolean
         * @param _isCurrentlyColliding true if entity is colliding otherwise false
         */
        void setIsCurrentlyColliding(bool _isCurrentlyColliding);

private:
        std::pair<double, double> position{0.0, 0.0}; // x, y position (should be the middle of the entity by default)
        std::pair<double, double> velocity{0.0, 0.0}; // x, y velocity
        std::pair<double, double> size{1.0, 1.0};     // x = width, y = height
        std::pair<double, double> origin{0.0, 0.0};   // x = width, y = height

        EntityAIState curState = EntityAIState::Idle;

        bool currentlyColliding = false;
};
} // namespace turbohiker
