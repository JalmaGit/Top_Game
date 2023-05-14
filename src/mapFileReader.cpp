
#include "mapFileReader.hpp"

std::string MapFileReader::read(const std::filesystem::path &path) { //
    std::ifstream myFile;
    std::string pathStr = path.string();

    if (file_missing_.find(pathStr) !=
        file_missing_.end()) {
        return "The file still doesn't exist. \n";
    } else if (cache_.count(pathStr)) {
        return "The file has already been opened before \n";
    }

    myFile.open(path);

    if (myFile.is_open()) {
        std::string line;
        std::string lineOutput;

        std::getline(myFile, line);
        cache_.insert({pathStr, line});

        while (std::getline(myFile, line)) {
            BoxParameters boxParams;

            std::stringstream ssLine(line);
            std::string keyValue;

            std::getline(ssLine, keyValue, ',');

            parseVectorData(boxParams.position, ssLine);
            parseVectorData(boxParams.size, ssLine);

            mapData.insert({keyValue, boxParams});
        }
        myFile.close();

        return "File has been read \n";
    }
    file_missing_.insert(pathStr);

    return "Does not exist \n";
}

void MapFileReader::parseVectorData(threepp::Vector3 &vectorData,
                                    std::stringstream &ssLine) {
    std::string lineValue;

    std::getline(ssLine, lineValue, ',');
    vectorData.x = static_cast<float> (std::atof(lineValue.c_str()));

    std::getline(ssLine, lineValue, ',');
    vectorData.y = static_cast<float> (std::atof(lineValue.c_str()));

    std::getline(ssLine, lineValue, ',');
    vectorData.z = static_cast<float> (std::atof(lineValue.c_str()));
}
