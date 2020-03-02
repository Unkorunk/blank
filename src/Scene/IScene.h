//
// Created by unkorunk on 02.03.2020.
//

#ifndef BLANK_GAME_ISCENE_H
#define BLANK_GAME_ISCENE_H

#include "../ITreeStructure.h"
#include "../GUI/Component.h"

class IScene : public ITreeStructure<GUI::Component> {
public:
    virtual void start() = 0;
    virtual void update() = 0;

private:

protected:
    IScene() = default;

};


#endif //BLANK_GAME_ISCENE_H
