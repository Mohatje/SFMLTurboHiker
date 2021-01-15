#pragma once
#include "Entity.h"
#include "World.h"
#include <memory>

namespace turbohiker {

class GameAI
{
public:
        // Public interfaces for the user to interact with the GameAI class

        /**
         * Method to instantiate the GameAI object with the needed requirements. \n
         * Should be used only once at the start of the game.
         * @param worldPtr shared pointer to the world object
         * @return GameAI Instance
         */
        static GameAI& instantiateAI(std::shared_ptr<World> worldPtr);

        /**
         * Method to get the singleton instance of the GameAI Object
         * @return GameAI Instance
         */
        static GameAI& getInstance();

        /**
         * Static method to update a hiker with an AI decision
         * @param hiker Entity on which the AI logic is applied
         * @param dTime Frametime used to have uniform updates
         */
        static void updateHiker(std::shared_ptr<Entity>& hiker, float dTime);

private:
        GameAI() = default;
        ~GameAI() = default;

private:
        static GameAI sharedInstance;
        void _updateHiker(std::shared_ptr<Entity>& hiker, float dTime);
        std::weak_ptr<World> _world;

private:
        // Actual implementation

        void _updateMovingHiker(std::shared_ptr<Entity>& hiker, float dTime);
        void _updateRacer(std::shared_ptr<Entity>& hiker, float dTime);

        /**
         * Function to get all entities within an entity's sight.\n
         * The entity's sight is a 2 x 2 square around the entity
         * @param hiker The entity for which you want to calculate the sight
         * @return A vector with pointers to each visible entity within the described sight size
         */
        std::vector<std::shared_ptr<Entity>> getEntitiesInSight(std::shared_ptr<Entity>& hiker);

        void avoidObstacle(std::shared_ptr<Entity>& hiker, std::shared_ptr<Entity>& ent);
};

} // namespace turbohiker
