#ifndef GAME_EVENT_H
#define GAME_EVENT_H

// #include <glm/glm.hpp>
#include <glad/glad.h>

enum class GameEventCode : unsigned int
{
    // NULL
    NO_MORE_GAME_EVENT,

    STG_FIRE,
    STG_CEASE,
    STG_CHANGE,
    STG_SYNC,
    STG_FORCE_SYNC_REQUEST,
    STG_FORCE_SYNC_RESPONE,

    GAME_EVENT_NUM
};

// union GameEventdata {
//     int i;
//     float f;
//     glm::vec2 v2;
// };

// class GameEvent
// {
// public:
//     int Event;
//     GameEventdata Data;

//     GameEvent(int e, GameEventdata d) : Event(e), Data(d) {}
//     GameEvent(int e) : Event(e) {}
//     GameEvent();
//     ~GameEvent();
// };
// typedef int GameEvent;

class GameEventBus
{
private:
    static constexpr int MAX_INTERNAL_EVENTS_N = 8;

    GameEventCode events[MAX_INTERNAL_EVENTS_N];
    GameEventCode loop_events[MAX_INTERNAL_EVENTS_N];
    int events_n;
    int processed;
    int loop_events_n;
    int loop_processed;

public:
    GameEventBus();
    GameEventBus(const GameEventBus &) = delete;
    GameEventBus(GameEventBus &&) = delete;
    GameEventBus &operator=(const GameEventBus &) = delete;
    GameEventBus &operator=(GameEventBus &&) = delete;
    ~GameEventBus() = default;

    int AddEvent(GameEventCode e);
    int AddLoopEvent(GameEventCode e);
    GameEventCode Next();
    GameEventCode LoopNext();
    void Clear();
    void LoopClear();
};

#endif