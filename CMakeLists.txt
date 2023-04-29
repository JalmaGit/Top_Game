cmake_minimum_required(VERSION 3.15)
project(Top_Game)

set(CMAKE_CXX_STANDARD 17)

option(THREEPP_BUILD_TESTS "Build test suite" ON)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)

add_executable(Top_Game main.cpp include/playerHandler.hpp tests/test_player.cpp include/cameraHandler.hpp)
target_link_libraries(Top_Game PUBLIC gamelib imgui::imgui)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)
if (THREEPP_BUILD_TESTS)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.8
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)
endif ()