//
// Created by unkorunk on 20.02.2020.
//

#ifndef BLANK_GAME_ITREESTRUCTURE_H
#define BLANK_GAME_ITREESTRUCTURE_H

#include <set>
#include <functional>

#include "Component.h"

namespace GUI {
    class ITreeStructure {
    public:
        virtual ~ITreeStructure() = default;

        void addChild(Component* child);
        void removeChild(Component* child);

        template <typename... Args>
        void addChildren(Component* child, Args... args) {
            this->addChild(child);
            addChildren(std::forward<Args>(args)...);
        }

        template <typename... Args>
        void removeChildren(Component* child, Args... args) {
            this->removeChild(child);
            removeChildren(std::forward<Args>(args)...);
        }

        template <typename T>
        T *getChild() {
            for (Component *child : children) {
                T *obj = dynamic_cast<T *>(child);
                if (obj != nullptr) {
                    return obj;
                }
            }
            return nullptr;
        }

        template <typename F, typename... Args>
        void execute(F&& func, Args&&... args) {
            for (Component *child : children) {
                std::bind(func, child, std::forward<Args>(args)...)();
            }
        }

    private:
        template <>
        void addChildren(GUI::Component* child) {
            this->addChild(child);
        }
        template <>
        void removeChildren(GUI::Component* child) {
            this->removeChild(child);
        }

        std::set<Component *> children;

    protected:
        ITreeStructure() = default;

    };
}

#endif //BLANK_GAME_ITREESTRUCTURE_H
