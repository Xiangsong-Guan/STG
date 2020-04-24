#ifndef STG_CHARACTOR_H
#define STG_CHARACTOR_H

#include "game_event.h"

#include <box2d/box2d.h>

class STGCharactor
{
private:
    b2Body *physics;

public:
    unsigned int ID;

    // some STG status

    STGCharactor() = default;
    STGCharactor(const STGCharactor &) = default;
    STGCharactor(STGCharactor &&) = default;
    STGCharactor &operator=(const STGCharactor &) = delete;
    STGCharactor &operator=(STGCharactor &&) = delete;
    ~STGCharactor() = default;

    void Init(unsigned int ID);
    void Update(GameEventBus &internal);
};

#endif