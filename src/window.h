/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <string>
#include "pxr/types.h"

struct GLFWwindow;

namespace pxr {

	/**
	 * @brief Manages an OpenGL window and context using GLFW.
	 *
	 * Handles window creation, event polling, buffer swapping, vsync, and access to dimensions.
	 */
	class Window {
	public:
		/**
		 * @brief Constructs a Window object.
		 */
		Window();

		/**
		 * @brief Destroys the window and terminates GLFW.
		 */
		~Window();

		/**
		 * @brief Creates a new window with the specified dimensions and title.
		 * @param width Width of the window in pixels.
		 * @param height Height of the window in pixels.
		 * @param title Window title string.
		 * @param vsync Whether to enable vertical sync.
		 */
		void create(int width, int height, const std::string &title, bool vsync);

		/**
		 * @brief Destroys the window and its OpenGL context.
		 */
		void destroy();

		/**
		 * @brief Polls GLFW events. Should be called once per frame.
		 */
		void pollEvents() const;

		/**
		 * @brief Swaps the front and back buffers.
		 */
		void swapBuffers() const;

		/**
		 * @brief Enables or disables vertical synchronization (vsync).
		 * @param enabled True to enable vsync, false to disable.
		 */
		void setVSync(bool enabled);

		/**
		 * @brief Sets the window title.
		 * @param title New window title.
		 */
		void setTitle(const std::string &title);

		/**
		 * @brief Sets the window dimensions.
		 * @param width New width in pixels.
		 * @param height New height in pixels.
		 */
		void setSize(int width, int height);

		/**
		 * @brief Checks whether the window should close (e.g., user pressed the close button).
		 * @return True if the window should close.
		 */
		[[nodiscard]] bool shouldClose() const;

		/**
		 * @brief Returns the current window width in pixels.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Returns the current window height in pixels.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * @brief Returns the current window size as a Size struct.
		 */
		[[nodiscard]] Size getSize() const;

		/**
		 * @brief Returns the current window title string.
		 */
		[[nodiscard]] const std::string &getTitle() const;

		/**
		 * @brief Checks if vsync is currently enabled.
		 */
		[[nodiscard]] bool isVSyncEnabled() const;

		/**
		 * @brief Returns the raw GLFW window handle.
		 */
		[[nodiscard]] GLFWwindow *getHandle() const;

	private:
		GLFWwindow *handle = nullptr; ///< Native GLFW window handle.
		int width = 640; ///< Current window width.
		int height = 480; ///< Current window height.
		std::string title = "Pixel Runtime"; ///< Current window title.
		bool vsyncEnabled = true; ///< Whether vsync is enabled.
	};

} // namespace pxr
