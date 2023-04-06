cmake_minimum_required(VERSION 3.15)
project(Top_Game)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Top_Game main.cpp
        cppfiles/geometryCreation.cpp
        cppfiles/world.cpp
        cppfiles/player.cpp)

target_link_libraries(Top_Game PRIVATE threepp::threepp imgui::imgui)
target_include_directories(Top_Game PUBLIC "${CMAKE_SOURCE_DIR}/include")

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")