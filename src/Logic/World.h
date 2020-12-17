#pragma once
#include "Entity.h"
#include "Player.h"
#include <set>
#include <vector>
#include <memory>


namespace turbohiker {

    class World : public Entity {
    private:
        using EntityRef = std::unique_ptr<Entity>;
        using SharedEntityRef = std::shared_ptr<Entity>;

        void setPosition(const std::pair<double, double> &_position) override {}
        void setVelocity(const std::pair<double, double> &_velocity) override {}
        void setSize(const std::pair<double, double> &_size) override {}
        const std::pair<double, double> &getPosition() const override { return Entity::getPosition(); }
        const std::pair<double, double> &getVelocity() const override { return Entity::getVelocity(); }
        const std::pair<double, double> &getSize() const override { return Entity::getSize(); }
        double getCollisionForce(EntityType typeOne, EntityType typeTwo);

    public:
        World() = default;

        ~World() = default;

        void display() override;
        void update(float dt) override;
        bool doTypeSpecificAction() override;

        void move(const std::pair<double, double>& offset) override;

        EntityType getType() const override { return EntityType::World; }

        bool addEntity(EntityRef ent);
        std::set<EntityRef> &getEntities();

        bool addTile(EntityRef ent);
        std::set<EntityRef> &getTiles();

        std::pair<double, double> getPlayerSize();
        std::pair<double, double> getPlayerPosition();
        std::pair<double, double> getPlayerVelocity();
        const std::unique_ptr<Entity> &getPlayerPtr();

        float getSpeed() const;

        void setSpeed(float speed);

        bool checkCollision(const EntityRef &entOne, const EntityRef &entTwo);

        virtual bool removeNearestObstacle();

        bool hasYelled() const;

        void removeObstacles(double bottomY);

        void setYelled(bool yelled);

        void movePlayer(const std::pair<double, double> &offset);
    private:

        std::set<EntityRef> worldEntities;

        std::set<EntityRef> worldTiles;

        float speed = 0.0f;

        bool yelled = false;
    };

}
