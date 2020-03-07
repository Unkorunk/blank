//
// Created by unkorunk on 05.03.2020.
//

#pragma once

class Blank;
class IScene;
class GameObject;

namespace Component {
    class IComponent {
        friend class ::GameObject;
        friend class ::IScene;
    public:
        virtual ~IComponent() = default;

        virtual void start() {}
        virtual void update() {}

    private:
        GameObject *parent = nullptr;
        Blank* blank;

    protected:
        IComponent() = default;

        GameObject *getParent() const {
            return parent;
        }

        Blank* getBlank() const {
            return blank;
        }

    };
}
