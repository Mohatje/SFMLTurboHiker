#pragma once
#include "Entity.h"
#include "Player.h"
#include <deque>
#include <memory>
#include <set>
#include <vector>

namespace turbohiker {

class World : public Entity
{
private:
        using EntityRef = std::unique_ptr<Entity>;
        using SharedEntityRef = std::shared_ptr<Entity>;

        void setPosition(const std::pair<double, double>& _position) override {}
        void setVelocity(const std::pair<double, double>& _velocity) override {}
        void setSize(const std::pair<double, double>& _size) override {}
        const std::pair<double, double>& getPosition() const override { return Entity::getPosition(); }
        const std::pair<double, double>& getVelocity() const override { return Entity::getVelocity(); }
        const std::pair<double, double>& getSize() const override { return Entity::getSize(); }
        double getCollisionForce(EntityType typeOne, EntityType typeTwo);

public:
        /**
         * Default constructor
         */
        World() = default;

        /**
         * Default destructor
         */
        ~World() override = default;

        void display() override;
        void update(float dt) override;
        bool doTypeSpecificAction() override;
        void move(const std::pair<double, double>& offset) override;
        EntityType getType() const override { return EntityType::World; }

        /**
         * Method which displays all world tiles (terrain) onto the game window
         */
        virtual void displayTiles();

        /**
         * Method which displays all world entities (players, hikers, ...) onto the game window
         */
        virtual void displayEntities();

        /**
         * Method which adds Entities to the world entity vector
         * @param ent entity which needs to be added to the world
         */
        void addEntity(EntityRef ent);

        /**
         * Getter for the world entities
         * @return world entities
         */
        std::vector<SharedEntityRef>& getEntities();

        /**
         * Method which adds (Terrain) Tiles to the world tile vector
         * @param ent The to be added tile entity
         */
        void addTile(EntityRef ent);

        /**
         * Getter for the world tiles
         * @return world tiles
         */
        std::vector<SharedEntityRef>& getTiles();

        /**
         * Get the playable Player's size
         * @return player size
         */
        std::pair<double, double> getPlayerSize();

        /**
         * Get the playable Player's position
         * @return player position
         */
        std::pair<double, double> getPlayerPosition();

        /**
         * Get the playable Player's velocity
         * @return player velocity
         */
        std::pair<double, double> getPlayerVelocity();

        /**
         * Get the playable Player's pointer
         * @return player pointer
         */
        const SharedEntityRef& getPlayerPtr();

        /**
         * Get the world speed ( current world movement speed (vertical) )
         * @return speed value in float
         */
        float getSpeed() const;

        /**
         * Set the world speed ( world movement speed (vertical) )
         * @param speed value in float
         */
        void setSpeed(float speed);

        /**
         * Method which checks collisions between two entities and attempts to resolve these collisions \n
         * Based on the AABB Collision detection and collision resolution
         * @param entOne First entity to check
         * @param entTwo Second entity to check
         * @return true if the entities are colliding, false otherwise
         */
        bool checkCollision(const SharedEntityRef& entOne, const SharedEntityRef& entTwo);

        /**
         * Method that `removes` the nearest obstacle to said caller \n
         * This method is used to get rid of static hikers or slow down moving hikers when yelling \n
         * Note that there is a certain range which the entity has to be in before it can be removed
         * @param entPos position of the entity
         * @return true if an obstacle has been removed, false otherwise
         */
        virtual bool removeNearestObstacle(const std::pair<double, double>& entPos);

        /**
         * Getter for the yelled boolean
         * @return boolean yelled
         */
        bool hasYelled() const;

        /**
         * Removes obstacles below a certain Y value\n
         * Function is used to remove obstacles / tiles which we cannot see anymore.
         * @param bottomY bottom y-value of the current view
         */
        void removeObstacles(double bottomY);

        /**
         * Setter for the yelled boolean
         * @param yelled boolean
         */
        void setYelled(bool yelled);

        /**
         * Placing a certain Y value constraint (finish line) above which no entity shall arrive.
         * @param yConstraint self explanatory
         */
        void clearEntitiesAbove(double yConstraint);

        /**
         * Method to check whether there are any entities who reached the finish line
         * @param finishLine finish line y value
         * @return true if every entity in the game has finished, false otherwise
         */
        bool checkForFinish(double finishLine);

        /**
         * Method to observe the order in which the entities are currently situated, and communicates it to their
         * Observers
         */
        virtual void observeOrder();

private:
        std::vector<SharedEntityRef> worldEntities;
        std::deque<SharedEntityRef> worldEntityDeque;

        std::vector<SharedEntityRef> worldTiles;

        SharedEntityRef player;

        float speed = 0.0f;

        bool yelled = false;
};

} // namespace turbohiker
