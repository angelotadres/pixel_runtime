# ─────────────────────────────────────────────────────────────
# External Dependencies Configuration
#
# This file sets up external dependencies for Pixel Runtime
# using CMake's FetchContent module. Dependencies are downloaded
# automatically at build time.
# ─────────────────────────────────────────────────────────────

include(FetchContent)

# ─────────────────────────────────────────────────────────────
# GLFW - Cross-platform windowing and input handling
# Abstracted internally by Pixel Runtime.
# ─────────────────────────────────────────────────────────────
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# ─────────────────────────────────────────────────────────────
# GLAD - OpenGL function loading
# Abstracted internally by Pixel Runtime.
# ─────────────────────────────────────────────────────────────
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# ─────────────────────────────────────────────────────────────
# GLM - Header-only vector and matrix math library
# Exposed publicly to allow direct use by Pixel Runtime users.
# ─────────────────────────────────────────────────────────────
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)
