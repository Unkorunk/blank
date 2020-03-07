//
// Created by unkorunk on 07.03.2020.
//

#pragma once

class Blank;

class IManager {
public:
    virtual ~IManager() = default;

    virtual void start() {}
    virtual void update() {}

private:
    Blank* blank;

protected:
    explicit IManager(Blank *blank) : blank(blank) {}

    Blank* getBlank() const {
        return blank;
    }

};

