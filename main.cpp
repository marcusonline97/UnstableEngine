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

		// Update rotation using deltaTime
		if (autoRotate) {
			angle += rotationSpeed * deltaTime;
		}

		// Ensure axis is valid
		if (glm::length(axis) < 1e-6f) axis = glm::vec3(0.0f, 1.0f, 0.0f);

		// Render 3D scene once
		glViewport(0, 0, bufferWidth, bufferHeight);


		// ImGui UI: rotation controls
		ImGui::Begin("UE Controls");
		ImGui::Text("Cube Rotation Controls");

		if (ImGui::Button("Rotate Left")) {
			angle -= 10.0f;
		}
		ImGui::SameLine();
		if (ImGui::Button("Rotate Right")) {
			angle += 10.0f;
		}

		ImGui::Checkbox("Auto Rotate", &autoRotate);
		ImGui::SliderFloat("Rotation Speed (deg/s)", &rotationSpeed, 0.0f, 720.0f);
		ImGui::InputFloat3("Axis", &axis[0]);
		if (ImGui::Button("Reset Rotation")) {
			angle = 0.0f;
			axis = glm::vec3(0.5f, 1.0f, 0.0f);
			rotationSpeed = 90.0f;
			autoRotate = false;
		}
		ImGui::Separator();
		ImGui::End();

		// Setup camera matrices (example)
		glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)bufferWidth / (float)bufferHeight,
			0.1f, 100.0f);


		// Update rotation if autoRotate is enabled
		if (autoRotate) {
			angle += rotationSpeed * deltaTime;
		}

		// Ensure axis is not zero to avoid undefined rotation
		if (glm::length(axis) < 1e-6f) axis = glm::vec3(0.0f, 1.0f, 0.0f);

		cube.SetRotation(angle, axis);
		cube.Render(view, projection);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	std::cout << "Closing An Unstable Engine" << "\n";

	return 0;
}