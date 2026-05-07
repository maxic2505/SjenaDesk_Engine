cmake_minimum_required(VERSION 3.10.0)
project(Engine LANGUAGES C)

# Build
set(SOURCES
    main.c
    src/SjenaDeskEngine/Graphics/Graphics.c
    src/SjenaDeskEngine/Graphics/UI.c
    src/SjenaDeskEngine/Input/Input.c
    src/SjenaDeskEngine/Math/Vector.c
    src/SjenaDeskEngine/Components.c
    src/SjenaDeskEngine/Core.c
)

# Add
add_executable(Engine ${SOURCES}
)

target_include_directories(Engine PUBLIC include)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

