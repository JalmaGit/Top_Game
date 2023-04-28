
add_compile_definitions(DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")

function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE threepp::threepp Catch2::Catch2)
    target_include_directories(${name} PUBLIC "${CMAKE_SOURCE_DIR}/include")
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_test_executable(test_moveAbleObject)
add_test_executable(test_player)