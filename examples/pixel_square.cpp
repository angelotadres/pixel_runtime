/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "pxr/pixel_runtime.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @class PixelSquare
 * @brief Rotating square rendered with manual line drawing.
 *
 * Demonstrates how to:
 * - Transform geometry using GLM
 * - Manually draw lines between points (Bresenham)
 * - Animate rotation using delta time
 * - Change color based on keyboard input
 */
class PixelSquare final : public pxr::App {
	//--------------------------------------------------------------------------
	// Members
	//--------------------------------------------------------------------------

	float rotationAngle = 0.0f; ///< Current angle of rotation (radians).
	int centerX = 0, centerY = 0; ///< Center of the square in screen space.
	const float velocity = 2.0f; ///< Rotation speed (radians per second).
	float sideLength = 0; ///< Length of the square's side.

	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------

	/**
	 * @brief Initializes the window, canvas, and square geometry.
	 */
	void setup() override {
		setTitle("Pixel Square - Pixel Runtime Demo");
		setSize(640, 480);
		setPixelSize(2);
		setVSync(false);

		centerX = getWidth() / 2;
		centerY = getHeight() / 2;
		sideLength = std::min(getWidth(), getHeight()) / 3.0f;
	}

	/**
	 * @brief Updates and draws the rotating square each frame.
	 */
	void update() override {
		background(pxr::Color::Black);

		// Build rotation matrix
		glm::mat2 rotationMatrix = {{std::cos(rotationAngle), -std::sin(rotationAngle)},
									{std::sin(rotationAngle), std::cos(rotationAngle)}};

		// Define square in local coordinates
		glm::vec2 vertices[4] = {{-sideLength / 2, -sideLength / 2},
								 {sideLength / 2, -sideLength / 2},
								 {sideLength / 2, sideLength / 2},
								 {-sideLength / 2, sideLength / 2}};

		// Apply rotation and translation
		for (auto &v: vertices) {
			v = rotationMatrix * v + glm::vec2(centerX, centerY);
		}

		// Select color based on input
		pxr::Color color = isKeyPressed(pxr::KeyCode::Space) ? pxr::Color::Magenta : pxr::Color::White;

		// Draw square edges
		for (int i = 0; i < 4; ++i) {
			drawLine(static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y),
					 static_cast<int>(vertices[(i + 1) % 4].x), static_cast<int>(vertices[(i + 1) % 4].y), color.r(),
					 color.g(), color.b());
		}

		// Update rotation
		rotationAngle += velocity * getDeltaTime();
		std::cout << "\rFPS: " << getFps() << std::flush;
	}

	//--------------------------------------------------------------------------
	// Helpers
	//--------------------------------------------------------------------------

	/**
	 * @brief Draws a line between two points using Bresenham's algorithm.
	 *
	 * @param x0 Start X.
	 * @param y0 Start Y.
	 * @param x1 End X.
	 * @param y1 End Y.
	 * @param r Red (0–255).
	 * @param g Green (0–255).
	 * @param b Blue (0–255).
	 */
	void drawLine(int x0, int y0, int x1, int y1, int r, int g, int b) {
		int x = x0, y = y0;
		int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		while (true) {
			drawPixel(x, y, r, g, b);
			if (x == x1 && y == y1)
				break;

			int e2 = 2 * err;
			if (e2 > -dy) {
				err -= dy;
				x += sx;
			}
			if (e2 < dx) {
				err += dx;
				y += sy;
			}
		}
	}
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelSquare)
