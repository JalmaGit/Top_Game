#include "mapFileReader.hpp"
#include <string>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Testing if MapFileReader can find and access the file"){
    MapFileReader file;
    std::string filePath = std::string(DATA_FOLDER) + "/mapTestData.txt";
    std::string returnValue = file.read(filePath);

    CHECK(returnValue == "File has been read \n");

    returnValue = file.read(filePath);

    CHECK(returnValue == "The file has already been opened before \n");

    returnValue = file.read ("data/doesntExist.txt");

    CHECK(returnValue == "Does not exist \n");

    returnValue = file.read("data/doesntExist.txt");

    CHECK(returnValue == "The file still doesn't exist. \n");
}

TEST_CASE("Testing if MapFileReader reads it correctly"){
    MapFileReader file;
    std::string filePath = std::string(DATA_FOLDER) + "/mapTestData.txt";
    file.read(filePath);

    REQUIRE_THAT(file.mapData.at("Test1").position.x, Catch::Matchers::WithinRel(0.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test1").position.y, Catch::Matchers::WithinRel(0.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test1").position.z, Catch::Matchers::WithinRel(0.0, 0.001));

    REQUIRE_THAT(file.mapData.at("Test1").size.x, Catch::Matchers::WithinRel(0.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test1").size.y, Catch::Matchers::WithinRel(0.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test1").size.z, Catch::Matchers::WithinRel(0.0, 0.001));

    REQUIRE_THAT(file.mapData.at("Test2").position.x, Catch::Matchers::WithinRel(100.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test2").position.y, Catch::Matchers::WithinRel(0.200, 0.001));
    REQUIRE_THAT(file.mapData.at("Test2").position.z, Catch::Matchers::WithinRel(300.0, 0.001));

    REQUIRE_THAT(file.mapData.at("Test2").size.x, Catch::Matchers::WithinRel(400.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test2").size.y, Catch::Matchers::WithinRel(500.0, 0.001));
    REQUIRE_THAT(file.mapData.at("Test2").size.z, Catch::Matchers::WithinRel(0.500, 0.001));

    CHECK(file.mapData.find("TestName - position(x") == file.mapData.end());
}