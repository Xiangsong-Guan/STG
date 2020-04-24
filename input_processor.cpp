#include "input_processor.h"

InputProcessor::InputProcessor() : ID(0)
{
    for (int i = 0; i < INPUT_COMMANDS_NUM; i++)
    {
        commands[i] = 0;
        state[i] = GL_FALSE;
    }
}

void InputProcessor::Init(unsigned int id, b2Body *body)
{
    ID = id;
    physics = body;
}

void InputProcessor::Update(GameEventBus &internal, const GLboolean keys[])
{
    b2Vec2 velocity(0.f, 0.f);
    if (keys[commands[INPUT_MOVE_UP]])
        velocity.y -= 1.f;
    if (keys[commands[INPUT_MOVE_DOWN]])
        velocity.y += 1.f;
    if (keys[commands[INPUT_MOVE_LEFT]])
        velocity.x -= 1.f;
    if (keys[commands[INPUT_MOVE_RIGHT]])
        velocity.x += 1.f;
    velocity.Normalize();
    physics->SetLinearVelocity(velocity);

    GLboolean flag;

    flag = keys[commands[INPUT_SHOOT]];
    if (flag && !state[INPUT_SHOOT])
        internal.AddEvent(GameEventCode::STG_FIRE);
    else if (!flag && state[INPUT_SHOOT])
        internal.AddEvent(GameEventCode::STG_CEASE);
    state[INPUT_SHOOT] = flag;

    flag = keys[commands[INPUT_CHANGE]];
    if (flag && !state[INPUT_CHANGE])
        internal.AddEvent(GameEventCode::STG_CHANGE);
    state[INPUT_CHANGE] = flag;

    flag = keys[commands[INPUT_SYNC]];
    if (flag && !state[INPUT_SYNC])
        internal.AddEvent(GameEventCode::STG_SYNC);
    state[INPUT_SYNC] = flag;

    flag = keys[commands[INPUT_FORCE_SYNC]];
    if (flag && !state[INPUT_FORCE_SYNC])
        internal.AddEvent(GameEventCode::STG_FORCE_SYNC_REQUEST);
    else if (!flag && state[INPUT_FORCE_SYNC])
        internal.AddEvent(GameEventCode::STG_FORCE_SYNC_RESPONE);
    state[INPUT_FORCE_SYNC] = flag;
}

void InputProcessor::SetCommand(int define, int key)
{
    if (define < INPUT_COMMANDS_NUM && define > -1 && key >= -1 && key <= 1024)
        commands[define] = key;
}