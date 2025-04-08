/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "pxr/pixel_runtime.h"

/**
 * @class PixelPaint
 * @brief A minimal interactive painting app using Pixel Runtime.
 *
 * This app allows the user to draw by clicking and dragging the mouse.
 * Color is selected using number keys (1–7), and the canvas is pixel-based.
 *
 * Controls:
 * - Left click: draw with selected color
 * - Right click: erase (draw white)
 * - 1–7: select predefined colors
 */
class PixelPaint final : public pxr::App {
	//--------------------------------------------------------------------------
	// Members
	//--------------------------------------------------------------------------

	/// The currently selected drawing color.
	pxr::Color currentColor;

	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------

	/**
	 * @brief Initializes the canvas and sets the default color.
	 */
	void setup() override {
		setTitle("Pixel Paint - Pixel Runtime Demo");
		setSize(16, 16); // Logical canvas size (in pixels)
		setPixelSize(50); // Each pixel is drawn as 100x100 screen pixels
		setVSync(true); // Enable vsync
		background(pxr::Color::White);
		currentColor = pxr::Color::Black;
	}

	/**
	 * @brief Called once per frame. Handles input and painting.
	 */
	void update() override {
		handleColorInput();
		handleDrawingInput();
	}

	//--------------------------------------------------------------------------
	// Helpers
	//--------------------------------------------------------------------------

	/**
	 * @brief Updates the current color based on number key input.
	 */
	void handleColorInput() {
		if (isKeyPressed(pxr::KeyCode::Num1))
			currentColor = pxr::Color::Black;
		if (isKeyPressed(pxr::KeyCode::Num2))
			currentColor = pxr::Color::Red;
		if (isKeyPressed(pxr::KeyCode::Num3))
			currentColor = pxr::Color::Green;
		if (isKeyPressed(pxr::KeyCode::Num4))
			currentColor = pxr::Color::Blue;
		if (isKeyPressed(pxr::KeyCode::Num5))
			currentColor = pxr::Color::Yellow;
		if (isKeyPressed(pxr::KeyCode::Num6))
			currentColor = pxr::Color::Magenta;
		if (isKeyPressed(pxr::KeyCode::Num7))
			currentColor = pxr::Color::Cyan;
	}

	/**
	 * @brief Draws pixels based on mouse position and button state.
	 */
	void handleDrawingInput() {
		const int x = getMouseX();
		const int y = getMouseY();

		if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
			if (isMousePressed(pxr::MouseButton::Left)) {
				drawPixel(x, y, currentColor);
			} else if (isMousePressed(pxr::MouseButton::Right)) {
				drawPixel(x, y, pxr::Color::White);
			}
		}
	}
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelPaint)
