#include "game.h"
#include "resource_manger.h"

#include <GLFW/glfw3.h>

Game::Game(GLuint width, GLuint height) : State(GameState::GAME_ACTIVE), Keys(), Width(width), Height(height), input_processor_n(1), entities_n(1), charactors_n(1), sprite_renderers_n(1) {}

Game::~Game()
{
    delete world;
}

void Game::Init()
{
    // initialize components
    // here just initialize whole game sturct and setup menu, game will be load when it is actully begin
    // A event bus is actully a entity's core, its index is entity's id

    // DEBUG
    // make world
    world = new b2World(b2Vec2(0.f, 0.f));
    // add player char, id: 1
    entities_n += 1;
    input_processor_n += 1;
    charactors_n += 1;
    sprite_renderers_n += 1;
    charactors[1].Init(1);
    // make body
    b2CircleShape circle;
    circle.m_p.Set(0.f, 0.f);
    circle.m_radius = .1f;
    b2BodyDef bd;
    bd.type = b2_kinematicBody;
    bd.position.Set(0.f, 0.f);
    bd.fixedRotation = true;
    bd.userData = charactors + 1;
    b2Body *body = world->CreateBody(&bd);
    b2FixtureDef fd;
    fd.shape = &circle;
    fd.userData = game_event_bus + 1;
    body->CreateFixture(&fd);
    // connect input
    input_processors[1].Init(1, body);
    input_processors[1].SetCommand(INPUT_MOVE_UP, GLFW_KEY_W);
    input_processors[1].SetCommand(INPUT_MOVE_DOWN, GLFW_KEY_S);
    input_processors[1].SetCommand(INPUT_MOVE_LEFT, GLFW_KEY_A);
    input_processors[1].SetCommand(INPUT_MOVE_RIGHT, GLFW_KEY_D);
    input_processors[1].SetCommand(INPUT_SHOOT, GLFW_KEY_Z);
    input_processors[1].SetCommand(INPUT_CHANGE, GLFW_KEY_LEFT_SHIFT);
    input_processors[1].SetCommand(INPUT_SYNC, GLFW_KEY_X);
    input_processors[1].SetCommand(INPUT_FORCE_SYNC, GLFW_KEY_C);
    // add sprite
    Shader &sprite_shader = ResourceManager::LoadShader("shader/sprite.vert", "shader/sprite.frag", nullptr, "sprite");
    sprite_shader.Use();
    sprite_shader.SetMatrix4("projection", glm::ortho(0.f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.f));
    sprite_shader.SetInteger("image", 0);
    sprite_renderers[1].Init(1, body, sprite_shader, ResourceManager::LoadTexture("art/char/player.png", GL_TRUE, "player"));
}

void Game::Update()
{
    if (State == GameState::GAME_ACTIVE)
    {
        // logic first
        // everything share physical body, so input and AI just control physical
        // use event bus control timer or other compoent
        for (unsigned int i = charactors_n - 1; i > 0; i--)
            charactors[i].Update(game_event_bus[input_processors[i].ID]); // tobe edit, stgcharactor just store state and have a hit function for colloision to call and have a single logic script to update
        // shoot comp not in stgchar, it is another comp

        // physics follows, physics may only let World step forward,
        //
        // all physics access and modify should dircetly to physical body,
        // that means logic part have full rw access to physical body, while
        // renderer just read some status, these things should not use event
        // system, because they happenned so frequently
        //
        // collision detected by physical engine, logic part using callback
        // to handle simple collision (such as get some damage, change status...).
        // this means physical body is intergrate in logic part, callback just call
        // body's specific function with each other's infomation
        //
        // meanwhile, logic and renderer do not dircetly access each other,
        // renderer usully has its own render logic (such as when hitten, turn to
        // some color and blink), charactor logic (or main logic / logic in short)
        // just send some events to render logic, let render logic determine how to
        // show the game

        world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        // also anime
    }
    else if (State == GameState::GAME_MENU)
    {
        // gui process only
    }
}

// input proecess is in order
void Game::ProcessInput()
{
    if (State == GameState::GAME_ACTIVE)
        for (unsigned int i = 1; i < input_processor_n; i++)
            input_processors[i].Update(game_event_bus[input_processors[i].ID], Keys);
}

void Game::Render(float forward_time, float cur_time)
{
    // draw to off-window frame
    for (unsigned int i = 1; i < sprite_renderers_n; i++)
        sprite_renderers[i].Draw(forward_time);

    // post process
}
