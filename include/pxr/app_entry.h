/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <iostream>

/**
 * @brief Defines the main entry point macro for Pixel Runtime applications.
 *
 * This macro creates and runs a user-defined App subclass, wrapped in a try-catch block
 * to ensure clean error reporting. It serves as the recommended way to launch apps built
 * with the Pixel Runtime framework.
 *
 * Example usage:
 * @code
 * #include "pxr/pixel_runtime.h"
 *
 * class MyApp : public pxr::App {
 *     void setup() override {
 *         setSize(320, 240);
 *         setPixelSize(2);
 *     }
 *
 *     void update() override {
 *         drawPixel(10, 10, pxr::Color::Red);
 *     }
 * };
 *
 * PXR_MAIN(MyApp)
 * @endcode
 *
 * @param AppClass Your application class that inherits from pxr::App.
 */
#define PXR_MAIN(AppClass)                                                                                             \
	int main() {                                                                                                       \
		try {                                                                                                          \
			AppClass app;                                                                                              \
			app.run();                                                                                                 \
		} catch (const std::exception &e) {                                                                            \
			std::cerr << "Fatal error: " << e.what() << '\n';                                                          \
			return EXIT_FAILURE;                                                                                       \
		}                                                                                                              \
		return EXIT_SUCCESS;                                                                                           \
	}
