cmake_minimum_required(VERSION 3.10.0)
project(Engine LANGUAGES C)

# Main
add_executable(Engine main.c)

# Engine - Universal
target_sources(Engine PRIVATE
    src/SjenaDeskEngine/Graphics/Graphics.c
    src/SjenaDeskEngine/Input/Input.c
    src/SjenaDeskEngine/Math/Vector.c
    src/SjenaDeskEngine/Core.c
)

# Engine - Windows
if(WIN32)
    target_sources(Engine PRIVATE src/SjenaDeskEngine/Graphics/Graphics_Windows.c)
endif()


# Engine - Linux
if(UNIX)

endif()

target_include_directories(Engine PUBLIC include)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

