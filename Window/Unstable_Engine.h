#pragma once

#include <ImGui/imgui.h>
#include <mutex>

class UserInterface;
class Input;
class Rendering;
struct GLFWwindow;

class Shader;
class Model;
class Logger;

class UnstableEngine
{
public:
	static UnstableEngine* get_instance();
	UnstableEngine(UnstableEngine& other) = delete;
	void operator=(const UnstableEngine&) = delete;

	int run();

	GLFWwindow* window;
	const char* glsl_version;
	int glfw_major_version;
    int glfw_minor_version;
    ImVec4 clear_color;
    int window_width;
    int window_height;
    const char* window_title;

    float delta_time_seconds;
    float last_time_seconds;
    float frames_per_second;

    bool firstMouse;
    float lastX, lastY;

    Logger* logger;

private:
    UnstableEngine();
    ~UnstableEngine();

    void initialize_all_components();
    int setup_glfw();
    int setup_glad();
    void clean_gflw();

    UserInterface* user_interface;
    Input* input;
    Rendering* rendering;

    static UnstableEngine* instance;
    static std::mutex neon_engine_mutex;
};