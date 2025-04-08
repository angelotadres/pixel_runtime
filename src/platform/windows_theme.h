/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#pragma once

#ifdef _WIN32

struct GLFWwindow;

namespace pxr {

	/**
	 * @brief Applies the system dark/light theme to a GLFW window (Windows only).
	 *
	 * This function uses Windows APIs to query the current system theme and applies
	 * immersive dark mode (if supported) to the specified window.
	 *
	 * @param window A valid GLFWwindow pointer.
	 */
	void applySystemThemeToWindow(GLFWwindow *window);

} // namespace pxr

#endif // _WIN32
