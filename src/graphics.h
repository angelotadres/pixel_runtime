/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include "pxr/surface.h"
#include "pxr/types.h"

namespace pxr {

	/**
	 * @brief Handles GPU-side rendering of pixel data from a Surface.
	 *
	 * The Graphics class manages OpenGL texture creation, PBOs for asynchronous
	 * data transfer, shader compilation, and rendering of a fullscreen quad.
	 */
	class Graphics {
	public:
		/**
		 * @brief Constructs a new Graphics object.
		 */
		Graphics();

		/**
		 * @brief Destructor. Automatically calls destroy().
		 */
		~Graphics();

		/**
		 * @brief Initializes GPU resources using the given surface.
		 *
		 * This sets up textures, buffers, and shaders based on the surface size.
		 * Must be called before calling upload().
		 *
		 * @param surface A surface whose dimensions define the rendering target size.
		 */
		void initialize(const Surface &surface);

		/**
		 * @brief Uploads pixel data from a surface to the GPU texture.
		 *
		 * The surface dimensions must match the one used in initialize().
		 *
		 * @param surface The surface to upload.
		 */
		void upload(const Surface &surface);

		/**
		 * @brief Renders the uploaded texture to the screen.
		 *
		 * @param pixelSize Reserved for future pixel-scaling effects. Currently unused.
		 */
		void render(int pixelSize);

		/**
		 * @brief Reinitializes GPU resources if surface size has changed.
		 *
		 * If the dimensions are different, resources are destroyed and recreated.
		 *
		 * @param surface The surface to match new dimensions with.
		 */
		void resize(const Surface &surface);

	private:
		/**
		 * @brief Creates an OpenGL texture of given size.
		 * @param width Texture width.
		 * @param height Texture height.
		 */
		void createTexture(int width, int height);

		/**
		 * @brief Creates two Pixel Buffer Objects for async pixel uploads.
		 */
		void createPBOs();

		/**
		 * @brief Creates a fullscreen quad using a VAO and VBO.
		 */
		void createQuad();

		/**
		 * @brief Compiles and links the default shader program.
		 */
		void createShaders();

		/**
		 * @brief Destroys all OpenGL resources.
		 */
		void destroy();

		unsigned int texture = 0; ///< OpenGL texture handle.
		unsigned int pbo[2] = {0, 0}; ///< Pixel Buffer Objects (double-buffered).
		unsigned int vao = 0; ///< Vertex Array Object.
		unsigned int vbo = 0; ///< Vertex Buffer Object.
		unsigned int shaderProgram = 0; ///< Shader program used for rendering.

		int currentPBO = 0; ///< Index of currently active PBO.
		int width = 0; ///< Width of current texture.
		int height = 0; ///< Height of current texture.
	};

} // namespace pxr
