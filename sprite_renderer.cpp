#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer() : ID(0), Color(glm::one<glm::vec3>()), quad_vao(0), vbo(0) {}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &quad_vao);
}

void SpriteRenderer::init_render_data()
{
    static constexpr GLfloat vertices[24] = {
        -.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -.5f, 1.0f, 0.0f,
        -.5f, -.5f, 0.0f, 0.0f,

        -.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -.5f, 1.0f, 0.0f};

    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quad_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::Init(unsigned int id, b2Body *body, const Shader &shader, const Texture &sprite)
{
    this->ID = id;
    this->physics = body;
    this->shader = shader;
    this->sprite = sprite;
    init_render_data();
}

void SpriteRenderer::ChangeShader(const Shader &shader)
{
    this->shader = shader;
}

void SpriteRenderer::ChangeSprite(const Texture &sprite)
{
    this->sprite = sprite;
}

void SpriteRenderer::Draw(float forward_time)
{
    b2Vec2 position = physics->GetPosition();
    b2Vec2 velocity = physics->GetLinearVelocity();
    float rotate = physics->GetAngle();

    // update render status then
    position += forward_time * TIME_STEP * velocity;
    position *= SCALE_FACTOR;

    // begin to draw
    shader.Use();

    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.f));
    model = glm::rotate(model, rotate, glm::vec3(0.f, 0.f, 1.f));
    model = glm::scale(model, glm::vec3(sprite.Width, sprite.Height, 1.f));

    shader.SetMatrix4("model", model);
    shader.SetVector3f("sprite_color", Color);

    sprite.Bind();

    glBindVertexArray(quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
