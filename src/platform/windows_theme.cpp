/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32 // Must be defined before GLFW includes
#define WIN32_LEAN_AND_MEAN

#include <dwmapi.h>
#include <windows.h>

// clang-format off
#include "gl_includes.h"
#include <GLFW/glfw3native.h> // Enables glfwGetWin32Window
// clang-format on

#include "windows_theme.h"

#define DWMWA_USE_IMMERSIVE_DARK_MODE 20

namespace pxr {

	/**
	 * @brief Queries the Windows registry to determine if dark mode is enabled.
	 *
	 * Reads the `AppsUseLightTheme` value from the user's personalization settings.
	 *
	 * @return True if dark mode is enabled, false if light mode is in use.
	 */
	static bool isSystemInDarkMode() {
		HKEY hKey;
		DWORD value = 1; // Default to light mode
		DWORD size = sizeof(value);

		if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0,
						  KEY_READ, &hKey) == ERROR_SUCCESS) {
			RegQueryValueExW(hKey, L"AppsUseLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &size);
			RegCloseKey(hKey);
		}

		return value == 0; // 0 = Dark mode
	}

	/**
	 * @brief Applies the system's dark/light theme to a GLFW window on Windows.
	 *
	 * This function attempts to enable immersive dark mode (where supported) by calling
	 * the Windows DWM API. It uses `glfwGetWin32Window()` to obtain the HWND handle.
	 *
	 * @param window A valid GLFW window pointer.
	 */
	void applySystemThemeToWindow(GLFWwindow *window) {
		HWND hwnd = glfwGetWin32Window(window);
		if (!hwnd)
			return;

		HMODULE dwmapi = LoadLibraryA("dwmapi.dll");
		if (!dwmapi)
			return;

		using DwmSetWindowAttributeFn = HRESULT(WINAPI *)(HWND, DWORD, LPCVOID, DWORD);
		auto DwmSetWindowAttribute =
				reinterpret_cast<DwmSetWindowAttributeFn>(GetProcAddress(dwmapi, "DwmSetWindowAttribute"));

		if (DwmSetWindowAttribute) {
			BOOL useDark = isSystemInDarkMode() ? TRUE : FALSE;
			DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDark, sizeof(useDark));
		}

		FreeLibrary(dwmapi);
	}

} // namespace pxr
#endif // _WIN32
