set(sources
        "Deperecated/geometryCreationOld.cpp"
        "Deperecated/worldOld.cpp"
        "Deperecated/playerOld.cpp"
        "player/playerVisualizer.cpp"
        "world/worldVisualizer.cpp"
        "world/worldLayer.cpp"
        "game.cpp"
        "keyInput.cpp"
        "raycasters.cpp"
        "spike/spikeLayer.cpp"
        "spike/spikeMath.cpp"
        "spike/spikeVisualizer.cpp"
        "player/cameraAttacher.cpp"
        "player/player.cpp"
        "player/playerCamera.cpp"
        "player/moveAble.cpp"
        "coin/coinLayer.cpp"
        "coin/coinMath.cpp"
        "coin/coinVisualizer.cpp")

add_library(gamelib "${sources}")
target_link_libraries(gamelib PUBLIC threepp::threepp)
target_include_directories(gamelib PUBLIC "${CMAKE_SOURCE_DIR}/include")