
cmake_minimum_required(VERSION 3.22.1)

project(RenderEngine)

file(GLOB RENDERENGINE_SRC Cpp/source/*.cpp)

add_library(RenderEngine SHARED ${RENDERENGINE_SRC})

target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Cpp/include)

# OpenGL ES 3.0
find_library(EGL-lib EGL)
find_library(GLESv3-lib GLESv3)

target_link_libraries(RenderEngine
    ${EGL-lib}
    ${GLESv3-lib}
)