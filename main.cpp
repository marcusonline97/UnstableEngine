#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() 
{
	if (!glfwInit())
	{
		std::cout << "GLFW Failed to initialize!" << "\n";
		glfwTerminate();
		return 1;
	}

	//Setup Window Properties 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Unstable_Engine", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create window!" << "\n";
		glfwTerminate();
		return 1;
	}

	//Get FrameBuffer size
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//Set Context 
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	std::cout << "Finished Compile" << "\n";

}