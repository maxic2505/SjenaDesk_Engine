cmake_minimum_required(VERSION 3.10.0)
project(Game VERSION 0.1.0 LANGUAGES C)

# Build
set(SjenaDesk_Engine        Engine/SjenaDesk_Engine.c                      )
set(SjenaDesk_Components    Engine/SjenaDesk_Components.c                  )
set(SjenaDesk_Graphics      Engine/Graphics/SjenaDesk_Graphics.c           )
set(SjenaDesk_Input         Engine/Input/SjenaDesk_Input.c                 )

# Add
add_executable(
    ${PROJECT_NAME}

    main.c

    # Engine - Files
    ${SjenaDesk_Engine} 
    ${SjenaDesk_Components}
    ${SjenaDesk_Graphics} 
    ${SjenaDesk_Input}
)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

