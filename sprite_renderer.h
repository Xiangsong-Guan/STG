#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

#include <box2d/box2d.h>
#include <glm/glm.hpp>

class SpriteRenderer
{
public:
    unsigned int ID;

    glm::vec3 Color;

    SpriteRenderer();
    SpriteRenderer(const SpriteRenderer &) = delete;
    SpriteRenderer(SpriteRenderer &&) = default;
    SpriteRenderer &operator=(const SpriteRenderer &) = delete;
    SpriteRenderer &operator=(SpriteRenderer &&) = delete;
    ~SpriteRenderer();

    void Init(unsigned int id, b2Body *body, const Shader &shader, const Texture &sprite);
    void ChangeShader(const Shader &shader);
    void ChangeSprite(const Texture &sprite);
    void Draw(float forward_time);

private:
    static constexpr float SCALE_FACTOR = 50.f;
    static constexpr float TIME_STEP = 1.f / 60.f;

    Shader shader;
    Texture sprite;

    GLuint quad_vao, vbo;

    b2Body *physics;

    void init_render_data();
};

#endif