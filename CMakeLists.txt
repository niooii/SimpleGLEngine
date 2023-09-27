cmake_minimum_required(VERSION 3.27)
project(GLGameEngine)

set(CMAKE_CXX_STANDARD 20)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_net REQUIRED)
find_package(SDL_ttf REQUIRED)
# manually get the include path for SDL_gpu
set(SDL2_GPU_INCLUDE_DIRS "/usr/include/SDL2")
set(GLM_INCLUDE_DIRS "/usr/include/glm")

# Include directories
include_directories(
        #my own shit
        "include"
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_PATH}
        ${SDL_MIXER_INCLUDE_DIRS}
        ${SDL_NET_INCLUDE_DIRS}
        ${SDL_TTF_INCLUDE_DIRS}
        ${SDL2_GPU_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)

# Set the output directory for executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# List of source files
set(SOURCE_FILES
        main.cpp
        include/Utils/Timer.cpp
        include/Window.cpp
        include/Window.h
        include/Camera.cpp
        include/Camera.h
        include/Shader.cpp
        include/Shader.h
        include/GameObject.cpp
        include/GameObject.h
)

# Create the executable
add_executable(GLGameEngine ${SOURCE_FILES})

# link glew
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(GLGameEngine ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES})

# Link libraries to the executable
target_link_libraries(GLGameEngine
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL_MIXER_LIBRARIES}
        ${SDL_NET_LIBRARIES}
        ${SDL_TTF_LIBRARIES}

        # Manually link SDL2_gpu library
        "/usr/lib/libSDL2_gpu.so"
)