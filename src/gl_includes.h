/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#pragma once

/**
 * @file gl_includes.h
 * @brief Centralized include for OpenGL (GLAD) and GLFW.
 *
 * This file ensures the correct inclusion order for GLAD and GLFW.
 *
 * GLAD must be included before any OpenGL-related headers (including GLFW),
 * because it defines all the OpenGL function pointers and types.
 * Failing to do so can result in build errors or undefined behavior on some platforms.
 *
 * Always include this file instead of including <glad/glad.h> and <GLFW/glfw3.h> manually.
 */

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
