#pragma once
#include "Entity.h"
#include "World.h"
#include <memory>


namespace turbohiker {


    class GameAI {
    public:
        static GameAI &instantiateAI(std::shared_ptr<World> worldPtr);
        static GameAI &getInstance();
        static void updateHiker(std::shared_ptr<Entity>& hiker, float dTime);

    private:
        GameAI() = default;
        ~GameAI() = default;

    private:
        static GameAI sharedInstance;
        void _updateHiker(std::shared_ptr<Entity>& hiker, float dTime);
        std::weak_ptr<World> _world;

    private:
        void _updateMovingHiker(std::shared_ptr<Entity> &hiker, float dTime);
        void _updateRacer(std::shared_ptr<Entity> &hiker, float dTime);

        /**
         * Function to get all entities within an entity's sight.\n
         * The entity's sight is a 2 x 2 square around the entity\n
         * @param hiker The entity for which you want to calculate the sight\n
         * @return A vector with pointers to each visible entity within the described sight size\n
         */
        std::vector<std::shared_ptr<Entity>> getEntitiesInSight(std::shared_ptr<Entity> &hiker);

    };

}


