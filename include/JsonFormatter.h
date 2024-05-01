//
// Created by paul on 26/03/24.
//
#include <string>

#ifndef STRUCTURETEST_JSONFORMATTER_H
#define STRUCTURETEST_JSONFORMATTER_H

class JsonFormatter{
public:
    /**
     * sequence specific string constructor to build a Json-like string to be sent by an MQTT client
     * @param the place in the package
     * @return a string matching the component at a certain place in the package
     */
   static std::string getString(int value);
};

#endif //STRUCTURETEST_JSONFORMATTER_H
