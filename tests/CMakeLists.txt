
add_compile_definitions(DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")

function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE gamelib Catch2::Catch2)
    add_test(NAME ${name} COMMAND ${name})

endfunction()

add_test_executable(test_moveAbleObject)
add_test_executable(test_player)
add_test_executable(test_cameraCalculations)
add_test_executable(test_coinMath)
add_test_executable(test_spikeMath)
add_test_executable(test_mapFileReader)