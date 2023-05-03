//
// Created by Jalma on 02/05/2023.
//

#ifndef TOP_GAME_FILEREADER_HPP
#define TOP_GAME_FILEREADER_HPP

#include <filesystem>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "threepp/math/Vector3.hpp"

struct BoxParameters {
    threepp::Vector3 Position;
    threepp::Vector3 Size;
};

struct file_reader {

public: //Taken some kode from: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

    std::unordered_map<std::string, BoxParameters> mapData;

    std::optional<std::string> read(const std::filesystem::path &path) { //
        std::ifstream myFile;
        std::string pathStr = path.string();

        //Will keep the file missing for future reference
        if (file_missing_.find(pathStr) !=
            file_missing_.end()) { //Checking if the file has been tried opened before, and if didn't exist then it still won't exist now.
            std::cout << "The file still doesn't exist. \n" << std::endl;
            return std::nullopt;
        } else if (cache_.count(pathStr)) {  //Checking if key path exists in cache
            std::cout << "The file has already been opened before and it reads out: \n" << std::endl;
            return cache_.at(pathStr);
        }

        myFile.open(path);

        if (myFile.is_open()) {
            std::string line;
            std::string lineOutput;

            std::getline(myFile,line);
            lineOutput = line;

            while (std::getline(myFile, line)) {
                std::stringstream ssLine(line);
                std::string keyValue;
                std::string positionData;
                std::string sizeData;
                BoxParameters boxParams;

                getline(ssLine, keyValue, ',');
                getline(ssLine, positionData, ',');
                getline(ssLine, sizeData, ',');

                std::string xPValue;
                std::string yPValue;
                std::string zPValue;
                std::string xSValue;
                std::string ySValue;
                std::string zSValue;

                std::stringstream ssPositionData(positionData);
                getline(ssPositionData, xPValue , ':');
                getline(ssPositionData, yPValue , ':');
                getline(ssPositionData, zPValue , ':');
                boxParams.Position.x = static_cast<float> (std::atof(xPValue.c_str()));
                boxParams.Position.y = static_cast<float> (std::atof(yPValue.c_str()));
                boxParams.Position.z = static_cast<float> (std::atof(zPValue.c_str()));

                std::stringstream ssSizeData(sizeData);
                getline(ssSizeData, xSValue , ':');
                getline(ssSizeData, ySValue , ':');
                getline(ssSizeData, zSValue , ':');
                boxParams.Size.x = static_cast<float> (std::atof(xSValue.c_str()));
                boxParams.Size.y = static_cast<float> (std::atof(ySValue.c_str()));
                boxParams.Size.z = static_cast<float> (std::atof(zSValue.c_str()));

                mapData.insert({keyValue,boxParams});

            }
            cache_.insert({pathStr, lineOutput});
            myFile.close();

            return "File has been read";
        }
        file_missing_.insert(pathStr);

        std::cout << "Does not exist \n" << std::endl;
        return std::nullopt;
    };

private: //Using this to improve performance
    std::unordered_map<std::string, std::string> cache_;
    //Key points towards the value.
    //The key is the path, and the value is what's been saved from the file.

    std::unordered_set<std::string> file_missing_; //I will keep this for future reference
    //Optimized so that if the file has been searched for at some point, and it didn't exist.
    //It won't try to search for the same file again.

};

#endif //TOP_GAME_FILEREADER_HPP
