//
// Created by paul on 29/04/24.
//

#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <string>

 class ConfigReader
{
public:
    static std::string getValue(const std::string& key);
};

#endif //CONFIGREADER_H
