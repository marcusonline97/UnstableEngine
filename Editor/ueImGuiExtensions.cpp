
#include <ImGui/imgui_internal.h>
#include "ueImGuiExtensions.h"

static ImVector<ImRect> s_GroupPanelLabelStack;


void ImGui::BeginGroupPanel(const char* name, const ImVec2& size)
{
	ImGui::BeginGroup();

	auto itemSpacing = ImGui::GetStyle().ItemSpacing;


}

void ImGui::EndGroupPanel()
{

}
