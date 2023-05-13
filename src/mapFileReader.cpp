
#include "mapFileReader.hpp"

std::string MapFileReader::read(const std::filesystem::path &path) { //
    std::ifstream myFile;
    std::string pathStr = path.string();

    if (file_missing_.find(pathStr) !=
        file_missing_.end()) { //Checking if the file has been tried opened before, and if didn't exist then it still won't exist now.
        return "The file still doesn't exist. \n";
    } else if (cache_.count(pathStr)) {  //Checking if key path exists in cache
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
            std::string lineValue;

            //TODO:DRY Try to shorten this? Make Exeception handeling

            getline(ssLine, keyValue, ',');

            getline(ssLine, lineValue, ',');
            boxParams.Position.x = static_cast<float> (std::atof(lineValue.c_str()));
            getline(ssLine, lineValue, ',');
            boxParams.Position.y = static_cast<float> (std::atof(lineValue.c_str()));
            getline(ssLine, lineValue, ',');
            boxParams.Position.z = static_cast<float> (std::atof(lineValue.c_str()));

            getline(ssLine, lineValue, ',');
            boxParams.Size.x = static_cast<float> (std::atof(lineValue.c_str()));
            getline(ssLine, lineValue, ',');
            boxParams.Size.y = static_cast<float> (std::atof(lineValue.c_str()));
            getline(ssLine, lineValue, ',');
            boxParams.Size.z = static_cast<float> (std::atof(lineValue.c_str()));
            //try to read up on boost library
            mapData.insert({keyValue, boxParams});

        }

        myFile.close();

        return "File has been read \n";
    }

    file_missing_.insert(pathStr);

    return  "Does not exist \n";
}
