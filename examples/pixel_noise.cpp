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
	void setup() override {
		setTitle("Pixel Noise - Pixel Runtime Demo");
		setSize(640, 480);
		setPixelSize(2);
		setVSync(true);
	}

	void update() override {
		const int w = getWidth();
		const int h = getHeight();
		const uint64_t frame = getFrameCount();

		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				const uint32_t hash = pxr::math::pseudoRandom(x, y, frame);
				const int r = hash & 0xFF;
				const int g = (hash >> 8) & 0xFF;
				const int b = (hash >> 16) & 0xFF;
				drawPixel(x, y, r, g, b);
			}
		}

		std::cout << "\rFPS: " << getFps() << std::flush;
	}
};

/// @brief Macro that defines the entry point and launches the app.
PXR_MAIN(PixelNoise)
