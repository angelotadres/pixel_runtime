/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include <cstdint>
#include <iostream>
#include "pxr/pixel_runtime.h"

/**
 * @class PixelNoise
 * @brief Animated pseudo-random RGB noise using Pixel Runtime.
 *
 * This example demonstrates:
 * - Per-frame surface updates
 * - A fast, hash-based pseudo-random color generator
 * - Full CPU-side rendering (no GPU shaders involved)
 *
 * The surface is filled with new noise each frame using a mix-hash function.
 */
class PixelNoise final : public pxr::App {
	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------

	/**
	 * @brief Called once during app startup.
	 *
	 * Sets window title, dimensions, pixel scaling, and enables vsync.
	 */
	void setup() override {
		setTitle("Pixel Noise - Pixel Runtime Demo");
		setSize(640, 480);
		setPixelSize(2);
		setVSync(true);
	}

	/**
	 * @brief Called once per frame to update the surface.
	 *
	 * Fills the surface with random RGB colors using a simple pseudo-random function.
	 */
	void update() override {
		const int w = getWidth();
		const int h = getHeight();
		const uint64_t frame = getFrameCount();

		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				const uint32_t hash = pseudoRandom(x, y, frame);

				const uint8_t r = hash & 0xFF;
				const uint8_t g = (hash >> 8) & 0xFF;
				const uint8_t b = (hash >> 16) & 0xFF;

				drawPixel(x, y, r, g, b);
			}
		}

		std::cout << "\rFPS: " << getFps() << std::flush;
	}

	//--------------------------------------------------------------------------
	// Helpers
	//--------------------------------------------------------------------------

	/**
	 * @brief Generates a pseudo-random 32-bit value based on position and frame.
	 *
	 * Uses mixed hashing of x, y, and frame for fast, repeatable noise.
	 *
	 * @param x Pixel x-coordinate.
	 * @param y Pixel y-coordinate.
	 * @param frame Frame number.
	 * @return A pseudo-random 32-bit integer.
	 */
	[[nodiscard]] static uint32_t pseudoRandom(int x, int y, uint64_t frame) {
		constexpr uint64_t HASH_X = 374761393u;
		constexpr uint64_t HASH_Y = 668265263u;
		constexpr uint64_t HASH_T = 14466617u;
		constexpr uint64_t HASH_MUL = 1274126177u;

		uint64_t hash = static_cast<uint64_t>(x) * HASH_X + static_cast<uint64_t>(y) * HASH_Y + frame * HASH_T;

		hash = (hash ^ (hash >> 13)) * HASH_MUL;
		return static_cast<uint32_t>(hash ^ (hash >> 16));
	}
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelNoise)
