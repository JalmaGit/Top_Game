cmake_minimum_required(VERSION 3.15)
project(Top_Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)

add_executable(Top_Game main.cpp)
target_link_libraries(Top_Game PUBLIC gamelib imgui::imgui)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_subdirectory(tests)


