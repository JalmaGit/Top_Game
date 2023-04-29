set(sources
        "geometryCreation.cpp"
        "world.cpp"
        "player.cpp"
        playerVisualizer.cpp playerVisualizer.hpp)

add_library(gamelib "${sources}")
target_link_libraries(gamelib PUBLIC threepp::threepp)
target_include_directories(gamelib PUBLIC "${CMAKE_SOURCE_DIR}/include")