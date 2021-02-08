#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(Blank *blank) : IManager(blank) {}

void PhysicsManager::start() {
    world = std::make_unique<b2World>(b2Vec2(0.0f, -9.81f * this->getScaleFactor()));
}

void PhysicsManager::update(float delta_time) {
    this->world->Step(delta_time, 20, 20);
}

b2World* PhysicsManager::getWorld() {
    return this->world.get();
}

float PhysicsManager::getScaleFactor() const {
    return 10.0f;
}
