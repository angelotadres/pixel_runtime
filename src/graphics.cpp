/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "graphics.h"
#include "error_handling.h"
#include "gl_includes.h"

#include <cstring>

namespace pxr {

	namespace {

		constexpr auto vertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec2 aPos;
			layout (location = 1) in vec2 aTex;

			out vec2 TexCoord;

			void main() {
				gl_Position = vec4(aPos, 0.0, 1.0);
				TexCoord = vec2(aTex.x, 1.0 - aTex.y);
			}
		)";

		constexpr auto fragmentShaderSrc = R"(
			#version 330 core
			in vec2 TexCoord;
			out vec4 FragColor;

			uniform sampler2D screenTexture;

			void main() {
				FragColor = texture(screenTexture, TexCoord);
			}
		)";

		unsigned int compileShader(unsigned int type, const char *source) {
			unsigned int shader = glCreateShader(type);
			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);

			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			PXR_ASSERT(success, "Shader compilation failed.");

			return shader;
		}

		unsigned int createShaderProgram(const char *vertexSrc, const char *fragmentSrc) {
			unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSrc);
			unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
			unsigned int program = glCreateProgram();

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);

			int success;
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			PXR_ASSERT(success, "Shader linking failed.");

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

	} // namespace

	Graphics::Graphics() = default;

	Graphics::~Graphics() { destroy(); }

	void Graphics::initialize(const Surface &surface) {
		width = surface.getWidth();
		height = surface.getHeight();

		createTexture(width, height);
		createPBOs();
		createQuad();
		createShaders();
	}

	void Graphics::createTexture(int w, int h) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Graphics::createPBOs() {
		glGenBuffers(2, pbo);

		for (int i = 0; i < 2; ++i) {
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo[i]);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, nullptr, GL_STREAM_DRAW);
		}
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	void Graphics::createQuad() {
		float vertices[] = {
				// pos       // tex
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));

		glBindVertexArray(0);
	}

	void Graphics::createShaders() { shaderProgram = createShaderProgram(vertexShaderSrc, fragmentShaderSrc); }

	void Graphics::upload(const Surface &surface) {
		PXR_ASSERT(surface.getWidth() == width && surface.getHeight() == height, "Surface size mismatch.");

		currentPBO = (currentPBO + 1) % 2;
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo[currentPBO]);

		void *ptr = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
		PXR_ASSERT(ptr != nullptr, "PBO mapping failed.");

		std::memcpy(ptr, surface.data(), width * height * 4);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	void Graphics::render(int /*pixelSize*/) {
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Graphics::resize(const Surface &surface) {
		if (surface.getWidth() == width && surface.getHeight() == height)
			return;

		destroy();
		width = surface.getWidth();
		height = surface.getHeight();
		initialize(surface);
	}

	void Graphics::destroy() {
		if (texture) {
			glDeleteTextures(1, &texture);
		}
		if (pbo[0]) {
			glDeleteBuffers(2, pbo);
		}
		if (vao) {
			glDeleteVertexArrays(1, &vao);
		}
		if (vbo) {
			glDeleteBuffers(1, &vbo);
		}
		if (shaderProgram) {
			glDeleteProgram(shaderProgram);
		}

		texture = vao = vbo = shaderProgram = 0;
		pbo[0] = pbo[1] = 0;
	}

} // namespace pxr
