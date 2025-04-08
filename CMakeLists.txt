cmake_minimum_required(VERSION 3.20)
project(pixel_runtime VERSION 0.0.0 LANGUAGES CXX)

# ─────────────────────────────────────────────────────────────
# Build Configuration
# ─────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ─────────────────────────────────────────────────────────────
# Build Options & Dependencies
# ─────────────────────────────────────────────────────────────
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)

# ─────────────────────────────────────────────────────────────
# Project Paths
# ─────────────────────────────────────────────────────────────
set(PXR_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PXR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PXR_PUB_HEADERS ${PXR_INCLUDE_DIR}/pxr)

# ─────────────────────────────────────────────────────────────
# Source & Header Files
# ─────────────────────────────────────────────────────────────
set(PXR_SOURCES
        ${PXR_SRC_DIR}/app.cpp
        ${PXR_SRC_DIR}/window.cpp
        ${PXR_SRC_DIR}/surface.cpp
        ${PXR_SRC_DIR}/graphics.cpp
        ${PXR_SRC_DIR}/input.cpp
)

# Append Windows-specific source if compiling on Windows.
if (WIN32)
    list(APPEND PXR_SOURCES ${PXR_SRC_DIR}/platform/windows_theme.cpp)
endif()

set(PXR_HEADERS
        ${PXR_PUB_HEADERS}/app.h
        ${PXR_PUB_HEADERS}/app_entry.h
        ${PXR_PUB_HEADERS}/color.h
        ${PXR_PUB_HEADERS}/input_codes.h
        ${PXR_PUB_HEADERS}/pixel_runtime.h
        ${PXR_PUB_HEADERS}/surface.h
        ${PXR_PUB_HEADERS}/types.h
        include/pxr/math.h
)

# ─────────────────────────────────────────────────────────────
# Core Library Target
# ─────────────────────────────────────────────────────────────
add_library(pixel_runtime STATIC ${PXR_SOURCES} ${PXR_HEADERS})

target_include_directories(pixel_runtime
        PUBLIC
        $<BUILD_INTERFACE:${PXR_INCLUDE_DIR}>
        PRIVATE
        ${PXR_SRC_DIR}
        ${glad_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
)

# Platform-specific OpenGL linking
if (APPLE)
    target_link_libraries(pixel_runtime
            INTERFACE glm
            PRIVATE glfw glad "-framework OpenGL"
    )
elseif (WIN32)
    target_link_libraries(pixel_runtime
            INTERFACE glm
            PRIVATE glfw glad opengl32
    )
else()
    target_link_libraries(pixel_runtime
            INTERFACE glm
            PRIVATE glfw glad GL
    )
endif()

# ─────────────────────────────────────────────────────────────
# Optional: Examples
# ─────────────────────────────────────────────────────────────
if (PXR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
