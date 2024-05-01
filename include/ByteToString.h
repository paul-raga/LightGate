//
// Created by paul on 25/03/24.
//
#include <string>

#ifndef STRUCTURETEST_BYTETOSTRING_MAP_H
#define STRUCTURETEST_BYTETOSTRING_MAP_H

class ByteToString{
public:
    /**
     *
     * @param the uint8_t that you want to be formatted into a string
     * @return the string representation of uint8_t
     */
    static std::string getValue(uint8_t value);

};

#endif //STRUCTURETEST_BYTETOSTRING_MAP_H
