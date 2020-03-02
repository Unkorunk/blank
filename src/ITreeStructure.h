//
// Created by unkorunk on 20.02.2020.
//

#ifndef BLANK_GAME_ITREESTRUCTURE_H
#define BLANK_GAME_ITREESTRUCTURE_H

#include <set>

template <typename BaseClass>
class ITreeStructure {
public:
    virtual ~ITreeStructure() = default;

    void addChild(BaseClass* child) {
        children.insert(child);
    }

    void removeChild(BaseClass* child) {
        auto iter = children.find(child);
        if (iter != children.end()) {
            children.erase(iter);
        }
    }

    template <typename... Args>
    void addChildren(BaseClass* child, Args... args) {
        this->addChild(child);
        addChildren(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void removeChildren(BaseClass* child, Args... args) {
        this->removeChild(child);
        removeChildren(std::forward<Args>(args)...);
    }

    template <typename T>
    T *getChild() {
        for (BaseClass *child : children) {
            T *obj = dynamic_cast<T *>(child);
            if (obj != nullptr) {
                return obj;
            }
        }
        return nullptr;
    }

private:
    template <>
    void addChildren(BaseClass* child) {
        this->addChild(child);
    }
    template <>
    void removeChildren(BaseClass* child) {
        this->removeChild(child);
    }

    std::set<BaseClass *> children;

protected:
    ITreeStructure() = default;

};


#endif //BLANK_GAME_ITREESTRUCTURE_H
