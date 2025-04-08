/**
 * @brief Pixel Runtime math utility header, wrapping GLM and adding custom utilities.
 *
 * This file encapsulates GLM types and functions inside the pxr::math namespace,
 * providing a simplified and consistent API across the runtime.
 */

#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>

namespace pxr::math {

	// -----------------------------------------------------------------------------
	// Type Aliases
	// -----------------------------------------------------------------------------

	/** @brief 2D float vector */
	using Vec2 = glm::vec2;
	/** @brief 3D float vector */
	using Vec3 = glm::vec3;
	/** @brief 4D float vector */
	using Vec4 = glm::vec4;
	/** @brief 2D integer vector */
	using IVec2 = glm::ivec2;
	/** @brief 3D integer vector */
	using IVec3 = glm::ivec3;
	/** @brief 4x4 float matrix */
	using Mat4 = glm::mat4;

	// -----------------------------------------------------------------------------
	// Constants
	// -----------------------------------------------------------------------------

	/** @brief PI constant */
	inline constexpr float Pi = glm::pi<float>();
	/** @brief 2 * PI constant */
	inline constexpr float TwoPi = glm::two_pi<float>();
	/** @brief PI / 2 constant */
	inline constexpr float HalfPi = glm::half_pi<float>();

	// -----------------------------------------------------------------------------
	// Function Imports (GLM)
	// -----------------------------------------------------------------------------

	using glm::ceil;
	using glm::clamp;
	using glm::cross;
	using glm::distance;
	using glm::dot;
	using glm::floor;
	using glm::fract;
	using glm::length;
	using glm::max;
	using glm::min;
	using glm::mix;
	using glm::mod;
	using glm::normalize;
	using glm::sign;
	using glm::smoothstep;
	using glm::step;

	using glm::lookAt;
	using glm::ortho;
	using glm::perspective;
	using glm::rotate;
	using glm::scale;
	using glm::translate;

	// -----------------------------------------------------------------------------
	// Custom Utilities
	// -----------------------------------------------------------------------------

	/**
	 * @brief Ping-pongs a float value between a minimum and maximum range.
	 *
	 * @param t The time or input value.
	 * @param min The minimum bound.
	 * @param max The maximum bound.
	 * @return The ping-ponged value between min and max.
	 */
	inline float pingpong(float t, float min, float max) {
		float range = max - min;
		float mod = std::fmod(t, 2.0f * range);
		return min + (range - std::abs(mod - range));
	}

	/**
	 * @brief Ping-pongs an integer value between a minimum and maximum range.
	 *
	 * @param t The input value.
	 * @param min The minimum bound.
	 * @param max The maximum bound.
	 * @return The ping-ponged integer between min and max.
	 */
	inline int pingpong(int t, int min, int max) {
		int range = max - min;
		int mod = t % (2 * range);
		return min + (range - std::abs(mod - range));
	}

	/**
	 * @brief Wraps a value to the interval [min, max).
	 *
	 * @param value The value to wrap.
	 * @param min The minimum bound.
	 * @param max The maximum bound.
	 * @return Wrapped value within the range [min, max).
	 */
	inline float wrap(float value, float min, float max) {
		float range = max - min;
		return min + glm::mod(value - min, range);
	}

	/**
	 * @brief Remaps a value from one range to another.
	 *
	 * @param inMin Input range minimum.
	 * @param inMax Input range maximum.
	 * @param outMin Output range minimum.
	 * @param outMax Output range maximum.
	 * @param value The value to remap.
	 * @return Remapped value clamped to the target range.
	 */
	inline float remap(float inMin, float inMax, float outMin, float outMax, float value) {
		float t = glm::clamp((value - inMin) / (inMax - inMin), 0.0f, 1.0f);
		return glm::mix(outMin, outMax, t);
	}

	/**
	 * @brief Returns -1, 0, or 1 depending on the sign of the input.
	 *
	 * @param v Input value.
	 * @return -1 if negative, 1 if positive, 0 if zero.
	 */
	inline float signOrZero(float v) { return (v > 0.0f) - (v < 0.0f); }

	/**
	 * @brief Cubic ease-in-out interpolation function.
	 *
	 * @param t Normalized time value in [0, 1].
	 * @return Interpolated value using cubic ease in and out.
	 */
	inline float easeInOutCubic(float t) {
		t = glm::clamp(t, 0.0f, 1.0f);
		return t < 0.5f ? 4.0f * t * t * t : 1.0f - glm::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
	}

	/**
	 * @brief Bounce easing function that eases out with a bounce effect.
	 *
	 * @param t Normalized time value in [0, 1].
	 * @return Interpolated value with bounce easing.
	 */
	inline float easeOutBounce(float t) {
		t = glm::clamp(t, 0.0f, 1.0f);
		const float n1 = 7.5625f;
		const float d1 = 2.75f;

		if (t < 1 / d1) {
			return n1 * t * t;
		} else if (t < 2 / d1) {
			t -= 1.5f / d1;
			return n1 * t * t + 0.75f;
		} else if (t < 2.5f / d1) {
			t -= 2.25f / d1;
			return n1 * t * t + 0.9375f;
		} else {
			t -= 2.625f / d1;
			return n1 * t * t + 0.984375f;
		}
	}

	/**
	 * @brief Fast pseudo-random 32-bit integer generator using a hash function.
	 *
	 * Stateless hash-based RNG suitable for noise, procedural effects, etc.
	 *
	 * @param x First coordinate or seed.
	 * @param y Second coordinate or seed.
	 * @param t Third input (e.g. time/frame).
	 * @return A pseudo-random 32-bit unsigned integer.
	 */
	inline uint32_t pseudoRandom(int x, int y, uint64_t t = 0) {
		constexpr uint64_t HASH_X = 374761393u;
		constexpr uint64_t HASH_Y = 668265263u;
		constexpr uint64_t HASH_T = 14466617u;
		constexpr uint64_t HASH_MUL = 1274126177u;

		uint64_t hash = static_cast<uint64_t>(x) * HASH_X + static_cast<uint64_t>(y) * HASH_Y + t * HASH_T;

		hash = (hash ^ (hash >> 13)) * HASH_MUL;
		return static_cast<uint32_t>(hash ^ (hash >> 16));
	}


} // namespace pxr::math
