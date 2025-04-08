/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#include "input.h"
#include "error_handling.h"

namespace pxr {

	void Input::initialize(GLFWwindow *handle) {
		PXR_ASSERT(handle, "GLFW window is null");
		window = handle;
	}

	void Input::poll() {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		mouseX = static_cast<int>(x);
		mouseY = static_cast<int>(y);
	}

	bool Input::isKeyPressed(KeyCode key) const { return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS; }

	bool Input::isMousePressed(MouseButton button) const {
		return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
	}

	int Input::getMouseWindowX() const { return mouseX; }

	int Input::getMouseWindowY() const { return mouseY; }

} // namespace pxr
