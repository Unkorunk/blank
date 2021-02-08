#pragma once

#include <memory>
#include <box2d/b2_world.h>

#include "IManager.h"

class PhysicsManager : public IManager {
public:
    explicit PhysicsManager(Blank* blank);
    virtual ~PhysicsManager() = default;

    void start() override;
    void update(float delta_time) override;

    b2World* getWorld();

    float getScaleFactor() const;

private:
    std::unique_ptr<b2World> world;

};
