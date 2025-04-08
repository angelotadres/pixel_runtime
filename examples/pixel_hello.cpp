/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include <iostream>
#include <pxr/pixel_runtime.h>

/**
 * @class PixelHello
 * @brief A simple bare-bones application.
 *
 * This example demonstrates how to create a basic app using Pixel Runtime.
 * It sets up a window and renders frames while printing the current FPS.
 *
 * Inherits from pxr::App and overrides `setup()` and `update()`:
 * - `setup()` configures the window and surface.
 * - `update()` prints the current FPS to the console every frame.
 */
class PixelHello final : public pxr::App {

	/**
	 * @brief Configures the app window and settings.
	 *
	 * Called once before the main loop starts.
	 */
	void setup() override {
		setTitle("Pixel Runtime - Pixel Hello Demo");
		setSize(640, 480); // Virtual canvas size
		setPixelSize(2); // Each "pixel" is 2×2 screen pixels
		setVSync(true); // Enable vertical sync
	}

	/**
	 * @brief Called every frame to perform rendering or logic.
	 *
	 * This version simply prints the FPS to the console.
	 */
	void update() override { std::cout << "\rFPS: " << getFps() << std::flush; }
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelHello)
