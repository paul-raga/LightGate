//
// Created by paul on 29/04/24.
//

#include "../include/ConfigReader.h"
#include <fstream>

#define FILEPATH "/home/paul/Gateway_0.0.1/config.txt"  //TODO change to /home/root/Gate/config.txt for embedded devices

std::string ConfigReader::getValue(const std::string& key)
{
    std::ifstream file(FILEPATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Find the position of the '=' character
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                // Extract key and value
                std::string currentKey = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                // Trim leading and trailing whitespace
                currentKey.erase(0, currentKey.find_first_not_of(" \t"));
                currentKey.erase(currentKey.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                // Check if the current key matches the desired key
                if (currentKey == key) {
                    file.close();
                    return value;
                }
            }
        }
        file.close();
    }
    return ""; // Key not found
}
