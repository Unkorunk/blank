//
// Created by unkorunk on 20.02.2020.
//

#pragma once

#include <vector>
#include <set>

template <typename BaseClass>
class ITreeStructure {
public:
    ITreeStructure() = default;

    virtual ~ITreeStructure() = default;

    void addChild(BaseClass* child) {
        if (addChildCallback(child)) {
            children.insert(child);
        }
    }

    void removeChild(BaseClass* child) {
        auto iter = children.find(child);
        if (iter != children.end()) {
            if (removeChildCallback(child)) {
                children.erase(iter);
            }
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
    T *getChild() const {
        for (BaseClass *child : children) {
            T *obj = dynamic_cast<T *>(child);
            if (obj != nullptr) {
                return obj;
            }
        }
        return nullptr;
    }

    std::vector<BaseClass *> getChildren() {
        return std::vector<BaseClass *>(children.begin(), children.end());
    }

private:
    template <typename... Args>
    void addChildren(BaseClass* child) {
        this->addChild(child);
    }
    template <typename... Args>
    void removeChildren(BaseClass* child) {
        this->removeChild(child);
    }

    std::set<BaseClass *> children;

protected:

    virtual bool addChildCallback(BaseClass* child) { return true; }
    virtual bool removeChildCallback(BaseClass* child) { return true; }

};
