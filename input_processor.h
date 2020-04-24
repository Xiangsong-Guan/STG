#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include "game_event.h"

#include <box2d/box2d.h>
#include <glad/glad.h>

#define INPUT_MOVE_UP 0
#define INPUT_MOVE_DOWN 1
#define INPUT_MOVE_LEFT 2
#define INPUT_MOVE_RIGHT 3
#define INPUT_SHOOT 4
#define INPUT_CHANGE 5
#define INPUT_SYNC 6
#define INPUT_FORCE_SYNC 7

class InputProcessor
{
private:
    static constexpr int INPUT_COMMANDS_NUM = 8;

    int commands[INPUT_COMMANDS_NUM];
    GLboolean state[INPUT_COMMANDS_NUM];

    b2Body *physics;

public:
    unsigned int ID;

    InputProcessor();
    InputProcessor(const InputProcessor &) = delete;
    InputProcessor(InputProcessor &&) = delete;
    InputProcessor &operator=(const InputProcessor &) = delete;
    InputProcessor &operator=(InputProcessor &&) = delete;
    ~InputProcessor() = default;

    void Init(unsigned int id, b2Body *body);

    void Update(GameEventBus &internal, const GLboolean keys[]);
    void SetCommand(int define, int key);
};

#endif