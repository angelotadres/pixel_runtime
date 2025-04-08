/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "window.h"
#include "error_handling.h"
#include "gl_includes.h"
#ifdef _WIN32
#include "platform/windows_theme.h"
#endif

namespace pxr {

	Window::Window() = default;

	Window::~Window() { destroy(); }

	void Window::create(int w, int h, const std::string &t, bool vsync) {
		if (!glfwInit()) {
			PXR_ASSERT(false, "Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		width = w;
		height = h;
		title = t;
		vsyncEnabled = vsync;

		handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		PXR_ASSERT(handle != nullptr, "Failed to create GLFW window");

#ifdef _WIN32
		pxr::applySystemThemeToWindow(handle);
#endif

		glfwMakeContextCurrent(handle);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			PXR_ASSERT(false, "Failed to initialize GLAD");
		}

		setVSync(vsyncEnabled);
	}

	void Window::destroy() {
		if (handle) {
			glfwDestroyWindow(handle);
			handle = nullptr;
		}
		glfwTerminate();
	}

	void Window::pollEvents() const { glfwPollEvents(); }

	void Window::swapBuffers() const { glfwSwapBuffers(handle); }

	void Window::setVSync(bool enabled) {
		vsyncEnabled = enabled;
		glfwSwapInterval(vsyncEnabled ? 1 : 0);
	}

	void Window::setTitle(const std::string &newTitle) {
		title = newTitle;
		if (handle) {
			glfwSetWindowTitle(handle, title.c_str());
		}
	}

	void Window::setSize(int w, int h) {
		width = w;
		height = h;
		if (handle) {
			glfwSetWindowSize(handle, width, height);
		}
	}

	bool Window::shouldClose() const { return glfwWindowShouldClose(handle); }

	int Window::getWidth() const { return width; }

	int Window::getHeight() const { return height; }

	Size Window::getSize() const { return Size{width, height}; }

	const std::string &Window::getTitle() const { return title; }

	bool Window::isVSyncEnabled() const { return vsyncEnabled; }

	GLFWwindow *Window::getHandle() const { return handle; }

} // namespace pxr
