cmake_minimum_required(VERSION 3.15)
project(Top_Game)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)

add_executable(Top_Game main.cpp)
target_link_libraries(Top_Game PUBLIC gamelib imgui::imgui)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")