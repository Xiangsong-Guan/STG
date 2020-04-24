#include "charactor.h"

void STGCharactor::Init(unsigned int id)
{
    ID = id;
}

void STGCharactor::Update(GameEventBus &internal)
{
    // update stg actor status according to input event and self logic
    GameEventCode e = internal.Next();
    while (e != GameEventCode::NO_MORE_GAME_EVENT)
    {
        internal.AddLoopEvent(e);
        e = internal.Next();
    }
    internal.Clear();
}