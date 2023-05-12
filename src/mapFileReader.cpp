
#include "mapFileReader.hpp"

std::optional <std::string> mapFileReader::read(const std::filesystem::path &path) { //
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

        std::getline(myFile, line);
        lineOutput = line;

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
        cache_.insert({pathStr, lineOutput});
        myFile.close();

        return "File has been read";
    }

    file_missing_.insert(pathStr);

    std::cout << "Does not exist \n" << std::endl;
    return std::nullopt;
}
