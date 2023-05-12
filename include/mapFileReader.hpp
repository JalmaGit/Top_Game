#ifndef TOP_GAME_MAPFILEREADER_HPP
#define TOP_GAME_MAPFILEREADER_HPP

#include <filesystem>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <threepp/math/Vector3.hpp>

struct BoxParameters {
    threepp::Vector3 Position;
    threepp::Vector3 Size;
};

//File Reader has been taken from exercise 3 and has been modified

class mapFileReader {

public: //Taken some kode from: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

    std::unordered_map<std::string, BoxParameters> mapData;

    std::optional<std::string> read(const std::filesystem::path &path);

private: //Using this to improve performance
    std::unordered_map<std::string, std::string> cache_;

    std::unordered_set<std::string> file_missing_;

};

#endif //TOP_GAME_MAPFILEREADER_HPP
