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

class mapFileReader {

public: //Taken some kode from: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

    std::unordered_map<std::string, BoxParameters> mapData;

    std::optional<std::string> read(const std::filesystem::path &path);

private: //Using this to improve performance
    std::unordered_map<std::string, std::string> cache_;
    //Key points towards the value.
    //The key is the path, and the value is what's been saved from the file.

    std::unordered_set<std::string> file_missing_; //I will keep this for future reference
    //Optimized so that if the file has been searched for at some point, and it didn't exist.
    //It won't try to search for the same file again.

};

#endif //TOP_GAME_MAPFILEREADER_HPP
