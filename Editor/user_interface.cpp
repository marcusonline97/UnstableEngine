#include "user_interface.h"

#include "Unstable_Engine.h"
#include "Input.h";
#include "Rendering/Renderer.h"
#include "game_object.h"
#include "model.h"
#include "logger.h"
#include "cubemap.h"

//External 3rd party shit
#include <imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//Standard C++
#include <mutex>
#include <iostream>
#include <cstring>

UserInterface* UserInterface::instance = nullptr;
std::mutex UserInterface::user_interface_mutex;

void UserInterface::glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW ERROR %d: %s\n", error, description);

}

UserInterface::UserInterface()
{
	unstable_engine = nullptr;
    input = nullptr;
    rendering = nullptr;
    window_viewport_width = -1;
    window_viewport_height = -1;
    texture_viewport_width = -1;
    texture_viewport_height = -1;
    texture_viewport_reduce_width_px = 10;
    texture_viewport_reduce_height_px = 30;
    first_time_viewport_fbo = true;
    passed_time_seconds = 0.0f;
    frames_per_second_ui = 0.0f;
    rendered_texture = 0;
    displayed_rendering = DisplayedColors;
    passed_time_resize = 0.0f;
    was_resized = false;
}

UserInterface::~UserInterface() {

}

UserInterface* UserInterface::get_instance()
{
    std::lock_guard<std::mutex> lock(user_interface_mutex);
    if (instance == nullptr)
    {
        instance = new UserInterface();

    }
    return instance;
}


void UserInterface::initialize()
{
    unstable_engine = UnstableEngine::get_instance();
    input = Input::get_instance();
    rendering = 
}