#include "game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr float SEC_PER_UPDATE = 1.f / 60.f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// The Width of the screen
constexpr GLuint SCREEN_WIDTH = 960;
// The height of the screen
constexpr GLuint SCREEN_HEIGHT = 540;

Game STG(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	if (!glfwInit())
	{
		std::cout << "fail to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "STG", nullptr, nullptr);
	if (!window)
	{
		std::cout << "fail to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "fail to initialize GLAD" << std::endl;
		return -1;
	}

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	STG.Init();

	// LOOP
	float lag = 0.f;
	float prev_time = static_cast<float>(glfwGetTime());
	while (!glfwWindowShouldClose(window) && STG.State != GameState::SHOULD_CLOSE)
	{
		float cur_time = static_cast<float>(glfwGetTime());
		lag += cur_time - prev_time;
		prev_time = cur_time;

		STG.ProcessInput();

		while (lag >= SEC_PER_UPDATE)
		{
			STG.Update();
			lag -= SEC_PER_UPDATE;
		}

		glClearColor(0.f, 0.f, 0.f, .75f);
		glClear(GL_COLOR_BUFFER_BIT);
		STG.Render(lag / SEC_PER_UPDATE, cur_time);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			STG.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			STG.Keys[key] = GL_FALSE;
	}
}
