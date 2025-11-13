#pragma once
#include "Core/ueBuildConfig.in.h"
#include "Core/ueGameEngine.h"
#include <ImGui/imgui.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>

class ueEditorWindowInterface
{
public:
    explicit ueEditorWindowInterface(std::string window_name)
        : window_name{ std::move(window_name) } {
    }

    virtual ~ueEditorWindowInterface() = default;

    virtual void update(ueGameEngine& ge) = 0;

    virtual void openWindow() { isOpened = true; }

    virtual void closeWindow() { isOpened = false; }

    [[nodiscard]] bool opened() const { return isOpened; }

    const std::string& windowName() { return window_name; }

protected:
    std::string window_name;
    bool isOpened = true;

};