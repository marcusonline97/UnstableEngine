#pragma once

#include <ImGui/imgui.h>
#include <glm/glm.hpp>
// Scale an ImVec4 color
inline ImVec4 ImScale(const ImVec4& c, float s) {
    return ImVec4(c.x * s, c.y * s, c.z * s, c.w * s);
}

// Legacy / convenience alias used by user_interface.cpp
inline ImVec4 scale(const ImVec4& c, float s) {
    return ImScale(c, s);
}

// Convert ImGui color to glm::vec4
inline glm::vec4 ImVec4ToGlm(const ImVec4& c) {
    return glm::vec4(c.x, c.y, c.z, c.w);
}

// Convert glm::vec4 to ImVec4
inline ImVec4 GlmToImVec4(const glm::vec4& v) {
    return ImVec4(v.r, v.g, v.b, v.a);
}