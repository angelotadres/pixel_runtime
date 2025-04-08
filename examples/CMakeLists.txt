# ─────────────────────────────────────────────────────────────
# Examples CMake Configuration
#
# Defines example apps demonstrating core Pixel Runtime features.
# Each example builds as a standalone executable linked to the
# Pixel Runtime library.
# ─────────────────────────────────────────────────────────────

# ─────────────────────────────────────────────────────────────
# Example: Pixel Hello
# Minimal app demonstrating basic setup and FPS display.
# ─────────────────────────────────────────────────────────────
add_executable(pxr_pixel_hello pixel_hello.cpp)
target_link_libraries(pxr_pixel_hello PRIVATE pixel_runtime)

# ─────────────────────────────────────────────────────────────
# Example: Pixel Mandelbrot
# Interactive Mandelbrot fractal explorer demonstrating pixel drawing.
# ─────────────────────────────────────────────────────────────
add_executable(pxr_pixel_mandelbrot pixel_mandelbrot.cpp)
target_link_libraries(pxr_pixel_mandelbrot PRIVATE pixel_runtime)

# ─────────────────────────────────────────────────────────────
# Example: Pixel Noise
# Animated pseudo-random RGB noise illustrating pixel manipulation.
# ─────────────────────────────────────────────────────────────
add_executable(pxr_pixel_noise pixel_noise.cpp)
target_link_libraries(pxr_pixel_noise PRIVATE pixel_runtime)

# ─────────────────────────────────────────────────────────────
# Example: Pixel Paint
# Interactive painting application showing mouse input handling.
# ─────────────────────────────────────────────────────────────
add_executable(pxr_pixel_paint pixel_paint.cpp)
target_link_libraries(pxr_pixel_paint PRIVATE pixel_runtime)

# ─────────────────────────────────────────────────────────────
# Example: Pixel Square
# Animated rotating square demonstrating transformations and geometry.
# ─────────────────────────────────────────────────────────────
add_executable(pxr_pixel_square pixel_square.cpp)
target_link_libraries(pxr_pixel_square PRIVATE pixel_runtime)
