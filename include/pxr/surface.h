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
#include <vector>
#include "color.h"
#include "types.h"

namespace pxr {

	/**
	 * @brief Represents a 2D pixel buffer for CPU-side rendering.
	 *
	 * The Surface class stores pixel data in a 1D array and allows manipulation
	 * of individual pixels.
	 */
	class Surface {
	public:
		/**
		 * @brief Constructs a surface with the given dimensions and background color.
		 * @param width Width of the surface in pixels. Must be > 0.
		 * @param height Height of the surface in pixels. Must be > 0.
		 * @param backgroundColor Color to initialize all pixels with.
		 */
		Surface(int width, int height, Color backgroundColor = Color::Black);

		/**
		 * @brief Fills the entire surface with a single color.
		 * @param color The color used to clear the surface.
		 */
		void clear(const Color &color);

		/**
		 * @brief Sets the pixel at (x, y) to the specified color.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param color The color to set.
		 */
		void setPixel(int x, int y, Color color);

		/**
		 * @brief Sets the pixel at (x, y) using raw RGB values.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param r Red channel (0–255).
		 * @param g Green channel (0–255).
		 * @param b Blue channel (0–255).
		 */
		void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

		/**
		 * @brief Retrieves the color of the pixel at (x, y).
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @return The color of the pixel.
		 */
		[[nodiscard]] Color getPixel(int x, int y) const;

		/**
		 * @brief Copies this surface's pixel data to another surface at a given offset.
		 * @param target The destination surface.
		 * @param dstX X offset on the destination surface.
		 * @param dstY Y offset on the destination surface.
		 */
		void blitTo(Surface &target, int dstX = 0, int dstY = 0) const;

		/**
		 * @brief Provides access to the raw 32-bit pixel buffer.
		 * @return A const reference to the internal pixel data.
		 */
		[[nodiscard]] const std::vector<uint32_t> &getPixels() const;

		/**
		 * @brief Returns a raw pointer to the internal pixel data.
		 * @return Pointer to the pixel data array.
		 */
		[[nodiscard]] const uint32_t *data() const;

		/**
		 * @brief Returns the width of the surface in pixels.
		 * @return The surface width.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Returns the height of the surface in pixels.
		 * @return The surface height.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * @brief Returns the surface dimensions as a Size struct.
		 * @return A Size containing width and height.
		 */
		[[nodiscard]] Size getSize() const;

		/**
		 * @brief Copy constructor is deleted to avoid copying large pixel buffers.
		 */
		Surface(const Surface &) = delete;

		/**
		 * @brief Copy assignment is deleted to avoid unintended data duplication.
		 */
		Surface &operator=(const Surface &) = delete;

		/**
		 * @brief Move constructor. Transfers ownership of pixel data.
		 * @param other The surface to move from.
		 */
		Surface(Surface &&other) noexcept;

		/**
		 * @brief Move assignment operator. Transfers ownership of pixel data.
		 * @param other The surface to move from.
		 * @return Reference to this surface.
		 */
		Surface &operator=(Surface &&other) noexcept;

	private:
		int width = 0; ///< Width of the surface in pixels.
		int height = 0; ///< Height of the surface in pixels.
		std::vector<uint32_t> pixels; ///< Pixel buffer stored as 32-bit packed RGBA.

		/**
		 * @brief Checks whether the given pixel coordinates are within bounds.
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @return True if within bounds; false otherwise.
		 */
		[[nodiscard]] bool isInBounds(int x, int y) const;
	};

} // namespace pxr
