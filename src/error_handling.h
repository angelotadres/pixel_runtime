/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#pragma once

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#ifdef DEBUG
/**
 * @brief Runtime assertion macro (debug mode).
 * Prints detailed error info and aborts on failure.
 */
#define PXR_ASSERT(cond, msg)                                                                                          \
	do {                                                                                                               \
		if (!(cond))                                                                                                   \
			pxr::handleDebugError(#cond, __FILE__, __LINE__, msg);                                                     \
	} while (0)
#else
/**
 * @brief Runtime assertion macro (release mode).
 * Logs error and exits cleanly.
 */
#define PXR_ASSERT(cond, msg)                                                                                          \
	do {                                                                                                               \
		if (!(cond))                                                                                                   \
			pxr::handleReleaseError(msg);                                                                              \
	} while (0)
#endif

namespace pxr {

	/**
	 * @brief Optional user-defined callback for error logging.
	 * Can be set via setErrorCallback().
	 */
	using ErrorCallback = std::function<void(const std::string &message)>;

	/// Global error callback. Called on failure if set.
	inline ErrorCallback errorCallback = nullptr;

	/**
	 * @brief Sets a custom error logging callback.
	 * @param cb Function to handle error messages.
	 */
	inline void setErrorCallback(ErrorCallback cb) { errorCallback = std::move(cb); }

	/**
	 * @brief Handles assertion failure in debug mode.
	 * @param expr The failed expression.
	 * @param file Source file name.
	 * @param line Line number.
	 * @param message Custom error message.
	 */
	inline void handleDebugError(const char *expr, const char *file, int line, const char *message) {
		std::string msg = "[Pixel Runtime] Assertion failed: ";
		msg += expr;
		msg += "\nLocation: ";
		msg += file;
		msg += ":";
		msg += std::to_string(line);
		msg += "\nReason: ";
		msg += message;

		if (errorCallback) {
			errorCallback(msg);
		} else {
			std::cerr << msg << std::endl;
		}

		std::abort();
	}

	/**
	 * @brief Handles fatal error in release mode.
	 * @param message Error message to display or log.
	 */
	inline void handleReleaseError(const char *message) {
		std::string msg = "[Pixel Runtime] Fatal error: ";
		msg += message;

		if (errorCallback) {
			errorCallback(msg);
		} else {
			std::cerr << msg << std::endl;
		}

		std::exit(EXIT_FAILURE);
	}

} // namespace pxr
