#ifndef GAME_H
#define GAME_H

#include "game_event.h"
#include "input_processor.h"
#include "charactor.h"
#include "sprite_renderer.h"

#include <box2d/box2d.h>
#include <glad/glad.h>

// Represents the current state of the game
enum class GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    SHOULD_CLOSE
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
private:
    static constexpr float TIME_STEP = 1.f / 60.f;
    static constexpr int VELOCITY_ITERATIONS = 6;
    static constexpr int POSITION_ITERATIONS = 2;

    static constexpr unsigned int MAX_ENTITIES = 2048;
    static constexpr unsigned int MAX_INPUT_CONNECTION = 8;

    InputProcessor input_processors[MAX_INPUT_CONNECTION];
    unsigned int input_processor_n;
    GameEventBus game_event_bus[MAX_ENTITIES];
    unsigned int entities_n;
    STGCharactor charactors[MAX_ENTITIES];
    unsigned int charactors_n;
    SpriteRenderer sprite_renderers[MAX_ENTITIES];
    unsigned int sprite_renderers_n;

    b2World *world;

public:
    // Game state
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;

    // Constructor/Destructor
    Game() = delete;
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game();

    Game(GLuint width, GLuint height);

    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // GameLoop
    void ProcessInput();
    void Update();
    void Render(float forward_time, float cur_time);
};

#endif