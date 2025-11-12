#pragma once

//#include "ueBuildConfig.h"

//#if UE_BUILD_EDITOR
#define IMGUI_DEFINE_MATH_OPERATORS

#include "ImGui/imgui.h"

namespace ImGui
{
    void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
    void EndGroupPanel();
}

//#endif UE_BUILD_EDITOR