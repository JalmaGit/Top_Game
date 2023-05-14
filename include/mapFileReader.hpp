#ifndef TOP_GAME_MAPFILEREADER_HPP
#define TOP_GAME_MAPFILEREADER_HPP

#include <filesystem>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include <threepp/math/Vector3.hpp>

struct BoxParameters {
    threepp::Vector3 position;
    threepp::Vector3 size;
};

//File Reader has been taken from exercise 3 and has been modified

class MapFileReader {

public: //Taken some kode from: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

    std::unordered_map<std::string, BoxParameters> mapData;

    std::string read(const std::filesystem::path &path);

private:
    static void parseVectorData(threepp::Vector3& vectorData, std::stringstream& ssLine);

    //Using this to improve performance
    std::unordered_map<std::string, std::string> cache_;

    std::unordered_set<std::string> file_missing_;
};

#endif //TOP_GAME_MAPFILEREADER_HPP
