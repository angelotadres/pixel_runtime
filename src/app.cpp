/*
 * Part of the Pixel Runtime project - https://github.com/angelotadres/pixel_runtime
 *
 * Copyright (c) 2025 Angelo Tadres
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#include "pxr/app.h"

#include <chrono>
#include <memory>

#include "error_handling.h"
#include "graphics.h"
#include "input.h"
#include "window.h"

namespace pxr {

	App::App() = default;
	App::~App() = default;

	//--------------------------------------------------------------------------
	// Entry Point
	//--------------------------------------------------------------------------

	void App::run() {
		using Clock = std::chrono::steady_clock;
		auto lastTime = Clock::now();
		float fpsTimer = 0.0f;
		int fpsCounter = 0;

		inSetupPhase = true;
		setup();
		inSetupPhase = false;

		window = std::make_unique<Window>();
		input = std::make_unique<Input>();
		graphics = std::make_unique<Graphics>();
		surface = std::make_unique<Surface>(width, height, backgroundColor);

		window->create(surface->getWidth() * pixelSize, surface->getHeight() * pixelSize, title, vsyncEnabled);
		input->initialize(window->getHandle());
		graphics->initialize(*surface);

		while (!shouldExit && !window->shouldClose()) {
			auto currentTime = Clock::now();
			std::chrono::duration<float> delta = currentTime - lastTime;
			deltaTime = delta.count();
			lastTime = currentTime;

			window->pollEvents();
			input->poll();

			update();

			graphics->upload(*surface);
			graphics->render(pixelSize);
			window->swapBuffers();

			frameCount++;
			fpsCounter++;
			fpsTimer += deltaTime;

			if (fpsTimer >= 1.0f) {
				fps = static_cast<float>(fpsCounter) / fpsTimer;
				fpsCounter = 0;
				fpsTimer = 0.0f;
			}
		}

		destroy();
		window->destroy();
	}

	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------

	void App::destroy() {
		// Optional cleanup hook
	}

	//--------------------------------------------------------------------------
	// Setup-Time Configuration
	//--------------------------------------------------------------------------

	void App::setVSync(bool enabled) {
		enforceSetupCall("setVSync");
		vsyncEnabled = enabled;
	}

	void App::setSize(int w, int h) {
		enforceSetupCall("setSize");
		width = w;
		height = h;
	}

	void App::setPixelSize(int size) {
		enforceSetupCall("setPixelSize");
		pixelSize = size;
	}

	void App::setTitle(const std::string &t) {
		enforceSetupCall("setTitle");
		title = t;
	}

	//--------------------------------------------------------------------------
	// App Control
	//--------------------------------------------------------------------------

	void App::exit() { shouldExit = true; }

	bool App::isRunning() const { return !shouldExit && !window->shouldClose(); }

	bool App::isInSetupPhase() const { return inSetupPhase; }

	//--------------------------------------------------------------------------
	// Window & Config Info
	//--------------------------------------------------------------------------

	bool App::isVSyncEnabled() const { return window->isVSyncEnabled(); }

	int App::getWidth() const { return surface ? surface->getWidth() : width; }

	int App::getHeight() const { return surface ? surface->getHeight() : height; }

	Size App::getSize() const { return surface ? surface->getSize() : Size{width, height}; }

	int App::getPixelSize() const { return pixelSize; }

	int App::getWindowWidth() const { return window ? window->getWidth() : width * pixelSize; }

	int App::getWindowHeight() const { return window ? window->getHeight() : height * pixelSize; }

	Size App::getWindowSize() const { return window ? window->getSize() : Size{width * pixelSize, height * pixelSize}; }

	const std::string &App::getTitle() const { return window ? window->getTitle() : title; }

	//--------------------------------------------------------------------------
	// Drawing
	//--------------------------------------------------------------------------

	void App::background(const Color &color) {
		backgroundColor = color;
		if (surface) {
			surface->clear(backgroundColor);
		}
	}

	void App::background(int r, int g, int b) { background(Color(r, g, b)); }

	void App::drawPixel(int x, int y, const Color &color) {
		if (surface) {
			surface->setPixel(x, y, color);
		}
	}

	void App::drawPixel(int x, int y, int r, int g, int b, int a) { drawPixel(x, y, Color(r, g, b, a)); }

	void App::drawSurface(const Surface &src, int x, int y) {
		if (surface) {
			src.blitTo(*surface, x, y);
		}
	}

	//--------------------------------------------------------------------------
	// Input Handling
	//--------------------------------------------------------------------------

	bool App::isKeyPressed(KeyCode key) const { return input && input->isKeyPressed(key); }

	bool App::isMousePressed(MouseButton button) const { return input && input->isMousePressed(button); }

	int App::getMouseX() const { return input ? input->getMouseWindowX() / pixelSize : 0; }

	int App::getMouseY() const { return input ? input->getMouseWindowY() / pixelSize : 0; }

	int App::getMouseWindowX() const { return input ? input->getMouseWindowX() : 0; }

	int App::getMouseWindowY() const { return input ? input->getMouseWindowY() : 0; }

	//--------------------------------------------------------------------------
	// Timing Info
	//--------------------------------------------------------------------------

	uint64_t App::getFrameCount() const { return frameCount; }

	float App::getFps() const { return fps; }

	float App::getDeltaTime() const { return deltaTime; }

	//--------------------------------------------------------------------------
	// Internal Helpers
	//--------------------------------------------------------------------------

	void App::enforceSetupCall(const char *funcName) const {
		PXR_ASSERT(inSetupPhase, (std::string(funcName) + " must be called inside setup()").c_str());
	}

} // namespace pxr
