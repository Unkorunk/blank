#include "Physics.h"
#include "Blank.h"

namespace Component {
    void Physics::start() {
        transform = this->getParent()->getComponent<Transform>();
        physics = this->getBlank()->getManager<PhysicsManager>();

        transform->setTransformUpdateCallback(std::bind(&Physics::transformUpdateCallback, this, std::placeholders::_1));

        b2BodyDef body_def;
        body_def.type = (this->is_static_body ? b2_staticBody : b2_dynamicBody);
        body_def.position.Set(
            transform->getX() * physics->getScaleFactor(),
            transform->getY() * physics->getScaleFactor()
        );
        body_def.angle = transform->getRotation().getZ();
        body = physics->getWorld()->CreateBody(&body_def);

        b2PolygonShape polygon_shape;
        polygon_shape.SetAsBox(
            transform->getWidth() / 2.0f * physics->getScaleFactor(),
            transform->getHeight() / 2.0f * physics->getScaleFactor(),
            b2Vec2(
                transform->getWidth() / 2.0f * physics->getScaleFactor(),
                -transform->getHeight() / 2.0f * physics->getScaleFactor()
            ),
            0.0f
        );

        fixture = body->CreateFixture(&polygon_shape, this->is_static_body ? 0.0f : 1.0f);
    }

    void Physics::update() {
        b2Vec2 position = body->GetPosition();

        transform->setX(position.x / physics->getScaleFactor());
        transform->setY(position.y / physics->getScaleFactor());
        transform->setRotation(
            Vector3f(
                transform->getRotation().getX(),
                transform->getRotation().getY(),
                body->GetAngle()
            )            
        );
    }

    void Physics::setIsStaticBody(bool is_static_body) {
        this->is_static_body = is_static_body;
        if (body && fixture) {
            body->SetType(this->is_static_body ? b2_staticBody : b2_dynamicBody);
            fixture->SetDensity(this->is_static_body ? 0.0f : 1.0f);

            if (!this->is_static_body) {
                body->ResetMassData();
            }
        }
    }

    bool Physics::getIsStaticBody() const {
        return this->is_static_body;
    }

    void Physics::transformUpdateCallback(Transform* transform) {
        body->SetTransform(
            b2Vec2(
                transform->getX() * physics->getScaleFactor(),
                transform->getY() * physics->getScaleFactor()
            ),
            transform->getRotation().getZ()
        );
    }

    void Physics::addForce(const Vector2f& force) {
        body->ApplyForceToCenter(force.toBox2D(), true);
    }

    void Physics::addForce(const Vector2f& force, const Vector2f& point) {
        body->ApplyForce(force.toBox2D(), point.toBox2D(), true);
    }

    b2Body* Physics::getBody() const {
        return this->body;
    }

    b2Fixture* Physics::getFixture() const {
        return this->fixture;
    }
}
