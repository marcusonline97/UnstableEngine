#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>
#include <dwmapi.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#pragma comment(lib, "dwmapi.lib")

// Function to toggle dark mode on the title bar of a GLFW window
void SetGLFWTitleBarDarkMode(GLFWwindow* window, bool enableDark)
{
    if (window == NULL) return;

    HWND hwnd = glfwGetWin32Window(window);
    if (hwnd == NULL) return;

    // Attribute constant for dark mode (Windows 10 build 17763+)
    const DWORD DWMWA_USE_IMMERSIVE_DARK_MODE = 20;

    BOOL useDark = enableDark ? TRUE : FALSE;

    HRESULT hr = DwmSetWindowAttribute(
        hwnd,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &useDark,
        sizeof(useDark)
    );

    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to set dark mode on title bar.", L"Error", MB_OK | MB_ICONERROR);
    }
}
