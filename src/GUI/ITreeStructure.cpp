//
// Created by unkorunk on 20.02.2020.
//

#include "ITreeStructure.h"

namespace GUI {
    void ITreeStructure::addChild(GUI::Component *child) {
        children.insert(child);
    }

    void ITreeStructure::removeChild(GUI::Component *child) {
        auto iter = children.find(child);
        if (iter != children.end()) {
            children.erase(iter);
        }
    }
}