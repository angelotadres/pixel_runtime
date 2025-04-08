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

namespace pxr {

	/**
	 * @brief Represents an RGBA color using 32-bit packed storage.
	 *
	 * Stores 8-bit red, green, blue, and alpha channels in a single 32-bit integer (0xAARRGGBB).
	 * Provides convenient constructors, component accessors, and predefined color constants.
	 */
	struct Color {
	private:
		uint32_t value; ///< Internal storage format: 0xAARRGGBB

	public:
		/**
		 * @brief Constructs a color from RGBA components.
		 * @param red Red component (0–255).
		 * @param green Green component (0–255).
		 * @param blue Blue component (0–255).
		 * @param alpha Alpha component (0–255), defaults to 255 (opaque).
		 */
		explicit constexpr Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255) :
			value((static_cast<uint32_t>(alpha) << 24) | (red << 16) | (green << 8) | blue) {}

		/// @brief Red channel (0–255).
		[[nodiscard]] constexpr uint8_t r() const { return (value >> 16) & 0xFF; }

		/// @brief Green channel (0–255).
		[[nodiscard]] constexpr uint8_t g() const { return (value >> 8) & 0xFF; }

		/// @brief Blue channel (0–255).
		[[nodiscard]] constexpr uint8_t b() const { return value & 0xFF; }

		/// @brief Alpha channel (0–255).
		[[nodiscard]] constexpr uint8_t a() const { return (value >> 24) & 0xFF; }

		/// @brief Returns the packed 32-bit color value (0xAARRGGBB).
		[[nodiscard]] constexpr uint32_t toUInt32() const { return value; }

		/// @brief Equality operator.
		[[nodiscard]] constexpr bool operator==(const Color &other) const { return value == other.value; }

		/// @brief Inequality operator.
		[[nodiscard]] constexpr bool operator!=(const Color &other) const { return value != other.value; }

		// Common predefined colors (opaque)
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
	};

	// Static color definitions
	inline constexpr Color Color::Black{0, 0, 0};
	inline constexpr Color Color::White{255, 255, 255};
	inline constexpr Color Color::Red{255, 0, 0};
	inline constexpr Color Color::Green{0, 255, 0};
	inline constexpr Color Color::Blue{0, 0, 255};
	inline constexpr Color Color::Cyan{0, 255, 255};
	inline constexpr Color Color::Yellow{255, 255, 0};
	inline constexpr Color Color::Magenta{255, 0, 255};

} // namespace pxr
