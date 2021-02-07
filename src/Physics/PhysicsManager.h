#pragma once

#include <box2d/b2_world.h>

#include "IManager.h"

class PhysicsManager : public IManager {
public:
    explicit PhysicsManager(Blank* blank);
    virtual ~PhysicsManager() = default;

    void start() override;
    void update(float delta_time) override;

private:
    b2World world = b2World(b2Vec2(0.0f, -9.81f));

};
