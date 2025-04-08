/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "color.h"
#include "input_codes.h"
#include "surface.h"

namespace pxr {

	/**
	 * @brief Base class for all Pixel Runtime applications.
	 *
	 * Users should inherit from this class to create custom apps.
	 * Override `setup()` to initialize the app and `update()` to define per-frame logic.
	 *
	 * The `App` class manages the main loop, input polling, drawing, timing, and window control.
	 *
	 */
	class App {
	public:
		/**
		 * @brief Constructs a new App instance.
		 */
		App();

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~App();

		/**
		 * @brief Starts the application.
		 *
		 * This initializes subsystems and enters the main loop.
		 * The `setup()` method is called once before the loop begins.
		 * The `update()` method is called every frame.
		 */
		void run();

		//--------------------------------------------------------------------------
		// Lifecycle
		//--------------------------------------------------------------------------

		/**
		 * @brief Called once at the beginning of the application.
		 *
		 * Override this method to configure the app (e.g., size, title).
		 */
		virtual void setup() = 0;

		/**
		 * @brief Called once per frame.
		 *
		 * Override this method to update logic, render to the surface, etc.
		 */
		virtual void update() = 0;

		/**
		 * @brief Called after the main loop exits.
		 *
		 * Override this method to clean up any user-defined resources.
		 * Optional to implement.
		 */
		virtual void destroy();

		//--------------------------------------------------------------------------
		// Setup-Time Configuration (must be called inside setup())
		//--------------------------------------------------------------------------

		/**
		 * @brief Enables or disables vertical sync.
		 * @param enabled True to enable vsync, false to disable.
		 */
		void setVSync(bool enabled);

		/**
		 * @brief Sets the virtual surface size in pixels.
		 * @param width Width in surface pixels.
		 * @param height Height in surface pixels.
		 */
		void setSize(int width, int height);

		/**
		 * @brief Sets the pixel scaling factor for the window.
		 * @param size Window pixels per surface pixel (e.g., 2 = 2× scaling).
		 */
		void setPixelSize(int size);

		/**
		 * @brief Sets the window title.
		 * @param title A string shown in the title bar.
		 */
		void setTitle(const std::string &title);

		//--------------------------------------------------------------------------
		// Drawing
		//--------------------------------------------------------------------------

		/**
		 * @brief Draws a pixel at (x, y) with a color.
		 * @param x X-coordinate in surface space.
		 * @param y Y-coordinate in surface space.
		 * @param color The color to draw.
		 */
		void drawPixel(int x, int y, const Color &color);

		/**
		 * @brief Draws a pixel with explicit RGBA components.
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @param r Red (0–255).
		 * @param g Green (0–255).
		 * @param b Blue (0–255).
		 * @param a Alpha (0–255, defaults to 255 = opaque).
		 */
		void drawPixel(int x, int y, int r, int g, int b, int a = 255);

		/**
		 * @brief Clears the surface with a solid color.
		 * @param color The background color.
		 */
		void background(const Color &color);

		/**
		 * @brief Clears the surface using RGB components.
		 * @param r Red (0–255).
		 * @param g Green (0–255).
		 * @param b Blue (0–255).
		 */
		void background(int r, int g, int b);

		/**
		 * @brief Draws another surface onto this surface at the given position.
		 * @param surface The surface to draw.
		 * @param x X offset in pixels.
		 * @param y Y offset in pixels.
		 */
		void drawSurface(const Surface &surface, int x = 0, int y = 0);

		//--------------------------------------------------------------------------
		// App Control
		//--------------------------------------------------------------------------

		/**
		 * @brief Requests the application to exit after the current frame.
		 */
		void exit();

		/**
		 * @brief Returns whether the application is currently running.
		 * @return True if running.
		 */
		[[nodiscard]] bool isRunning() const;

		/**
		 * @brief Returns true if the app is currently inside `setup()`.
		 */
		[[nodiscard]] bool isInSetupPhase() const;

		//--------------------------------------------------------------------------
		// Window & Config Info
		//--------------------------------------------------------------------------

		/**
		 * @brief Checks whether vsync is enabled.
		 */
		[[nodiscard]] bool isVSyncEnabled() const;

		/**
		 * @brief Returns the surface width in pixels.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Returns the surface height in pixels.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * @brief Returns the surface dimensions as a Size struct.
		 */
		[[nodiscard]] Size getSize() const;

		/**
		 * @brief Returns the pixel scaling factor (window pixels per surface pixel).
		 */
		[[nodiscard]] int getPixelSize() const;

		/**
		 * @brief Returns the window width in physical pixels.
		 */
		[[nodiscard]] int getWindowWidth() const;

		/**
		 * @brief Returns the window height in physical pixels.
		 */
		[[nodiscard]] int getWindowHeight() const;

		/**
		 * @brief Returns the window size as a Size struct (in physical pixels).
		 */
		[[nodiscard]] Size getWindowSize() const;

		/**
		 * @brief Returns the window title.
		 */
		[[nodiscard]] const std::string &getTitle() const;

		//--------------------------------------------------------------------------
		// Input Handling
		//--------------------------------------------------------------------------

		/**
		 * @brief Checks whether a keyboard key is currently pressed.
		 * @param key The key to check.
		 */
		[[nodiscard]] bool isKeyPressed(KeyCode key) const;

		/**
		 * @brief Checks whether a mouse button is currently pressed.
		 * @param button The button to check.
		 */
		[[nodiscard]] bool isMousePressed(MouseButton button) const;

		/**
		 * @brief Returns the mouse X position in surface pixels.
		 */
		[[nodiscard]] int getMouseX() const;

		/**
		 * @brief Returns the mouse Y position in surface pixels.
		 */
		[[nodiscard]] int getMouseY() const;

		/**
		 * @brief Returns the raw mouse X position in window pixels.
		 */
		[[nodiscard]] int getMouseWindowX() const;

		/**
		 * @brief Returns the raw mouse Y position in window pixels.
		 */
		[[nodiscard]] int getMouseWindowY() const;

		//--------------------------------------------------------------------------
		// Timing Info
		//--------------------------------------------------------------------------

		/**
		 * @brief Returns the total number of frames since launch.
		 */
		[[nodiscard]] uint64_t getFrameCount() const;

		/**
		 * @brief Returns the current frames-per-second (FPS).
		 */
		[[nodiscard]] float getFps() const;

		/**
		 * @brief Returns the time elapsed since last frame (in seconds).
		 */
		[[nodiscard]] float getDeltaTime() const;

	private:
		// Config state
		int width = 400;
		int height = 400;
		int pixelSize = 1;
		Color backgroundColor = Color::Black;
		std::string title = "Pixel Runtime";
		bool vsyncEnabled = true;
		bool inSetupPhase = false;
		bool shouldExit = false;

		// Timing state
		uint64_t frameCount = 0;
		float deltaTime = 0.016f;
		float fps = 0.0f;

		// Core systems
		std::unique_ptr<class Window> window;
		std::unique_ptr<class Graphics> graphics;
		std::unique_ptr<class Surface> surface;
		std::unique_ptr<class Input> input;

		/**
		 * @brief Ensures certain methods are only called inside `setup()`.
		 * @param funcName Name of the method that triggered the check.
		 */
		void enforceSetupCall(const char *funcName) const;
	};

} // namespace pxr
