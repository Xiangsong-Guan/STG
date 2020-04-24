#include "game_event.h"

GameEventBus::GameEventBus()
{
    events_n = 0;
    processed = 0;
    loop_events_n = 0;
    loop_processed = 0;
}

int GameEventBus::AddEvent(GameEventCode e)
{
    if (events_n < MAX_INTERNAL_EVENTS_N)
    {
        events[events_n] = e;
        events_n += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

int GameEventBus::AddLoopEvent(GameEventCode e)
{
    if (loop_events_n < MAX_INTERNAL_EVENTS_N)
    {
        loop_events[loop_events_n] = e;
        loop_events_n += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

GameEventCode GameEventBus::Next()
{
    if (processed < events_n)
    {
        processed += 1;
        return events[processed - 1];
    }
    else
    {
        processed = 0;
        return GameEventCode::NO_MORE_GAME_EVENT;
    }
}

GameEventCode GameEventBus::LoopNext()
{
    if (loop_processed < loop_events_n)
    {
        loop_processed += 1;
        return loop_events[loop_processed - 1];
    }
    else
    {
        loop_processed = 0;
        return GameEventCode::NO_MORE_GAME_EVENT;
    }
}

void GameEventBus::Clear()
{
    processed = 0;
    events_n = 0;
}

void GameEventBus::LoopClear()
{
    loop_processed = 0;
    loop_events_n = 0;
}
