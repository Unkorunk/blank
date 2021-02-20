//
// Created by unkorunk on 07.03.2020.
//

#pragma once

class Blank;

class IManager {
public:
    virtual ~IManager() = default;

    virtual void start() {}
    virtual void update(float delta_time) {}
    virtual void lateUpdate() {}

private:
    Blank* blank;

protected:
    explicit IManager(Blank *blank) : blank(blank) {}

    Blank* getBlank() const {
        return blank;
    }

};

