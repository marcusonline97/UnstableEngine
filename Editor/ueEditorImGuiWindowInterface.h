#pragma once

#include "../Engine/Core/ueGameEngine.h"
#include <ImGui/imgui.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>

class ueEditorWindowInterface
{
public:
	explicit ueEditorWindowInterface(std::string window_name) : window_name{ std::move(window_name) } {}
};