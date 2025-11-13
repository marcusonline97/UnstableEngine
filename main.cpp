#include <iostream>

#include <Windows.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
//Temp fix for rendering
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

//Temporary Add 
#include "Components/PrimitiveShapes/Cube.h"
//Custom Implementation
#include "Window/DarkMode.c"

const GLint WIDTH = 1980, HEIGHT = 1980;

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
	SetGLFWTitleBarDarkMode(window, true);   // Enable dark title bar

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
	//DarkMode for the window
	HWND hwnd = GetActiveWindow();
	SetGLFWTitleBarDarkMode(window, true);   // Enable dark title bar	
	//Init IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	glEnable(GL_DEPTH_TEST);

	// Create cube and persistent state outside loop
	Cube cube;
	float angle = 0.0f;
	glm::vec3 axis(0.5f, 1.0f, 0.0f);

	bool autoRotate = false;
	float rotationSpeed = 90.0f; // degrees per second

	// time tracking for smooth rotation
	float lastTime = static_cast<float>(glfwGetTime());

	while (!glfwWindowShouldClose(window))
	{
		// time
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);
		//ImGui Starts
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();



		// Render 3D scene once
		glViewport(0, 0, bufferWidth, bufferHeight);


		// ImGui UI: rotation controls
		ImGui::Begin("UE Controls");
		ImGui::Text("Cube Rotation Controls");

		ImGui::Separator();
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	std::cout << "Closing An Unstable Engine" << "\n";

	return 0;
}