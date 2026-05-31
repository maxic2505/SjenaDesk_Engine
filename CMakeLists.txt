cmake_minimum_required(VERSION 3.10.0)
project(Engine LANGUAGES C)

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
    target_sources(Engine PRIVATE src/SjenaDeskEngine/Input/Input_Windows.c)
endif()


# Engine - Linux
if(UNIX)
    target_sources(Engine PRIVATE src/SjenaDeskEngine/Graphics/Graphics_Linux.c)
    target_sources(Engine PRIVATE src/SjenaDeskEngine/Input/Input_Linux.c)
endif()

target_include_directories(Engine PUBLIC include)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

