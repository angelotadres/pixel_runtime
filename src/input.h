/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include "gl_includes.h"
#include "pxr/input_codes.h"

namespace pxr {

	/**
	 * @brief Handles keyboard and mouse input using GLFW.
	 *
	 * This class provides access to key/mouse states and mouse position
	 * in raw window-space pixel coordinates.
	 */
	class Input {
	public:
		/**
		 * @brief Initializes input handling with a GLFW window.
		 * @param handle A valid GLFW window pointer.
		 */
		void initialize(GLFWwindow *handle);

		/**
		 * @brief Updates internal mouse position. Call once per frame.
		 */
		void poll();

		/**
		 * @brief Checks whether a keyboard key is currently pressed.
		 * @param key The key to check.
		 * @return True if pressed, false otherwise.
		 */
		[[nodiscard]] bool isKeyPressed(KeyCode key) const;

		/**
		 * @brief Checks whether a mouse button is currently pressed.
		 * @param button The mouse button to check.
		 * @return True if pressed, false otherwise.
		 */
		[[nodiscard]] bool isMousePressed(MouseButton button) const;

		/**
		 * @brief Returns the current X position of the mouse in window-space pixels.
		 */
		[[nodiscard]] int getMouseWindowX() const;

		/**
		 * @brief Returns the current Y position of the mouse in window-space pixels.
		 */
		[[nodiscard]] int getMouseWindowY() const;

	private:
		GLFWwindow *window = nullptr; ///< GLFW window pointer.
		int mouseX = 0; ///< Cached X mouse position in window space.
		int mouseY = 0; ///< Cached Y mouse position in window space.
	};

} // namespace pxr
