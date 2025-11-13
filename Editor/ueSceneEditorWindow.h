#pragma once

#include "../Engine/Core/ueBuildConfig.in.h"

#include "ueEditorImGuiWindowInterface.h"

#include "../Engine/Core/ueGameEngine.h"
#include "../Engine/Tools/ueCamera.h"


#include <ImGuizmo/ImGuizmo.h>

class ueSceneEditorWindow : public ueEditorWindowInterface
{
public:
	ueSceneEditorWindow(const std::string& window_name, std::shared_ptr<ueFramebufferInterface>& framebuffer);
};