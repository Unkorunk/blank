#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(Blank *blank) : IManager(blank) {}

void PhysicsManager::start() {
    
}

void PhysicsManager::update(float delta_time) {
    this->world.Step(delta_time, 6, 2);
}
