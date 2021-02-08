#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "IComponent.h"
#include "Transform.h"
#include "Physics/PhysicsManager.h"

namespace Component {
    class Physics : public IComponent {
    public:
        virtual ~Physics() = default;

        void start() override;
        void update() override;

        void setIsStaticBody(bool is_static_body);
        bool getIsStaticBody() const;

        void addForce(const Vector2f& force);
        void addForce(const Vector2f& force, const Vector2f& point);

        b2Body* getBody() const;
        b2Fixture* getFixture() const;

    private:
        Transform* transform;
        PhysicsManager* physics;

        b2Body* body;
        b2Fixture* fixture;

        bool is_static_body = false;

        void transformUpdateCallback(Transform* transform);

    };
}
