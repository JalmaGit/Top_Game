cmake_minimum_required(VERSION 3.15)
project(threepp_vcpkg_test)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui assimp::assimp)
target_link_libraries(test PRIVATE ${BULLET_LIBRARIES})
file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")