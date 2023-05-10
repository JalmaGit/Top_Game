
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
            std::string xPValue;
            std::string yPValue;
            std::string zPValue;
            std::string xSValue;
            std::string ySValue;
            std::string zSValue;

            //TODO:DRY Try to shorten this? Make Exeception handeling

            getline(ssLine, keyValue, ',');

            getline(ssLine, xPValue, ',');
            getline(ssLine, yPValue, ',');
            getline(ssLine, zPValue, ',');
            boxParams.Position.x = static_cast<float> (std::atof(xPValue.c_str()));
            boxParams.Position.y = static_cast<float> (std::atof(yPValue.c_str()));
            boxParams.Position.z = static_cast<float> (std::atof(zPValue.c_str()));
            getline(ssLine, xSValue, ',');
            getline(ssLine, ySValue, ',');
            getline(ssLine, zSValue, ',');
            boxParams.Size.x = static_cast<float> (std::atof(xSValue.c_str()));
            boxParams.Size.y = static_cast<float> (std::atof(ySValue.c_str()));
            boxParams.Size.z = static_cast<float> (std::atof(zSValue.c_str()));

            //Try to make expecption if any number is not pressent/is a char of some sort
            //try to read up on boost library
            //DRY

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
