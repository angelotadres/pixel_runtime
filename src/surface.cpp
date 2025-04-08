/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "pxr/surface.h"
#include <algorithm>
#include "error_handling.h"

namespace pxr {

	Surface::Surface(int width, int height, Color backgroundColor) :
		width(width), height(height), pixels(width * height, backgroundColor.toUInt32()) {
		PXR_ASSERT(width > 0 && height > 0, "Surface dimensions must be positive.");
	}

	void Surface::clear(const Color &color) { std::ranges::fill(pixels, color.toUInt32()); }

	void Surface::setPixel(int x, int y, Color color) {
		PXR_ASSERT(isInBounds(x, y), "setPixel() out of bounds.");
		pixels[y * width + x] = color.toUInt32();
	}

	void Surface::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) { setPixel(x, y, Color(r, g, b)); }

	Color Surface::getPixel(int x, int y) const {
		PXR_ASSERT(isInBounds(x, y), "getPixel() out of bounds.");
		return Color(pixels[y * width + x]);
	}

	void Surface::blitTo(Surface &target, int dstX, int dstY) const {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				int tx = dstX + x;
				int ty = dstY + y;
				if (target.isInBounds(tx, ty)) {
					target.setPixel(tx, ty, getPixel(x, y));
				}
			}
		}
	}

	const std::vector<uint32_t> &Surface::getPixels() const { return pixels; }

	const uint32_t *Surface::data() const { return pixels.data(); }

	int Surface::getWidth() const { return width; }

	int Surface::getHeight() const { return height; }

	Size Surface::getSize() const { return Size{width, height}; }

	Surface::Surface(Surface &&other) noexcept :
		width(other.width), height(other.height), pixels(std::move(other.pixels)) {
		other.width = 0;
		other.height = 0;
	}

	Surface &Surface::operator=(Surface &&other) noexcept {
		if (this != &other) {
			width = other.width;
			height = other.height;
			pixels = std::move(other.pixels);
			other.width = 0;
			other.height = 0;
		}
		return *this;
	}

	bool Surface::isInBounds(int x, int y) const { return x >= 0 && y >= 0 && x < width && y < height; }

} // namespace pxr
