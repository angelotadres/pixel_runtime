/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include <iostream>
#include "pxr/pixel_runtime.h"

/**
 * @class PixelMandelbrot
 * @brief A simple interactive Mandelbrot viewer.
 *
 * Demonstrates per-pixel rendering and input handling with Pixel Runtime.
 * Use W, A, S, D keys to pan the view.
 * Use Up/Down arrow keys to zoom in and out.
 * Renders a colored Mandelbrot set in real time.
 */
class PixelMandelbrot final : public pxr::App {
	//--------------------------------------------------------------------------
	// Members
	//--------------------------------------------------------------------------

	double offsetX = 0.0; ///< Current pan X offset in complex plane.
	double offsetY = 0.0; ///< Current pan Y offset in complex plane.
	double scale = 0.0; ///< Complex-plane units per screen pixel.

	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------

	/**
	 * @brief Configures the app window and view settings.
	 */
	void setup() override {
		setTitle("Pixel Mandelbrot - Pixel Runtime Demo");
		setSize(150, 100); // Virtual resolution
		setPixelSize(8); // Each pixel is drawn as a 10×10 square
		setVSync(true); // Enable vsync

		// View spans 4 units across the smaller axis
		scale = 4.0 / std::min(getWidth(), getHeight());
	}

	/**
	 * @brief Called once per frame. Handles input and rendering.
	 */
	void update() override {
		handleInput();
		renderMandelbrot();
		std::cout << "\rFPS: " << getFps() << std::flush;
	}

	//--------------------------------------------------------------------------
	// Helpers
	//--------------------------------------------------------------------------

	/**
	 * @brief Handles input for panning and zooming.
	 */
	void handleInput() {
		const double panSpeed = 200.0 * getDeltaTime() * scale;
		if (isKeyPressed(pxr::KeyCode::W))
			offsetY += panSpeed;
		if (isKeyPressed(pxr::KeyCode::S))
			offsetY -= panSpeed;
		if (isKeyPressed(pxr::KeyCode::A))
			offsetX -= panSpeed;
		if (isKeyPressed(pxr::KeyCode::D))
			offsetX += panSpeed;

		const double zoomSpeed = 8.0 * getDeltaTime() * scale;
		if (isKeyPressed(pxr::KeyCode::UpArrow))
			scale *= (1.0 - zoomSpeed);
		if (isKeyPressed(pxr::KeyCode::DownArrow))
			scale *= (1.0 + zoomSpeed);
	}

	/**
	 * @brief Renders the Mandelbrot set to the surface.
	 */
	void renderMandelbrot() {
		const int width = getWidth();
		const int height = getHeight();
		constexpr int maxIter = 100;

		for (int y = 0; y < height; ++y) {
			const double imag = (y - height / 2) * scale + offsetY;

			for (int x = 0; x < width; ++x) {
				const double real = (x - width / 2) * scale + offsetX;

				// Mandelbrot iteration
				int iter = 0;
				double zr = 0.0, zi = 0.0;
				while ((zr * zr + zi * zi <= 4.0) && (iter < maxIter)) {
					double temp = zr * zr - zi * zi + real;
					zi = 2.0 * zr * zi + imag;
					zr = temp;
					++iter;
				}

				// Color mapping
				int r, g, b;
				if (iter == maxIter) {
					r = g = b = 0; // Inside the set = black
				} else {
					const double t = static_cast<double>(iter) / maxIter;
					r = static_cast<int>(9 * (1 - t) * t * t * t * 255);
					g = static_cast<int>(15 * (1 - t) * (1 - t) * t * t * 255);
					b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
				}

				drawPixel(x, y, r, g, b);
			}
		}
	}
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelMandelbrot)
