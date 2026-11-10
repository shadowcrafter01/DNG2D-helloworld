cmake_minimum_required(VERSION 3.24)
project(ENG2D-helloworld VERSION 0.1.0 LANGUAGES C CXX)

# some var for vscode may or may not do anything lol
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(DNG2D_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    DNG2D
    GIT_REPOSITORY https://github.com/shadowcrafter01/DNG2D.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(DNG2D)

add_executable(ENG2D-helloworld src/main.cpp)

target_include_directories(
    ENG2D-helloworld
    PUBLIC
        "include"
)

target_compile_features(
    ENG2D-helloworld
    PRIVATE
        cxx_std_20
)

target_link_libraries(
    ENG2D-helloworld
    PRIVATE
        DNG2D::DNG2D
)

# use this to copy your assets folder to the build directory so the built program runs
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# copies the required .dll files to the build directory so the built .exe can actually run
if(WIN32)

    add_custom_command(
        TARGET ENG2D-helloworld
        POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:ENG2D-helloworld>"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_image::SDL3_image>"
            "$<TARGET_FILE_DIR:ENG2D-helloworld>"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>"
            "$<TARGET_FILE_DIR:ENG2D-helloworld>"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_mixer::SDL3_mixer>"
            "$<TARGET_FILE_DIR:ENG2D-helloworld>"
    )

endif()

# links some stuff that lets the .exe run on machines without gcc installed
if(MINGW)
    target_link_options(ENG2D-helloworld PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()