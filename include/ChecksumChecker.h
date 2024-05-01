//
// Created by paul on 20/03/24.
//

#ifndef STRUCTURETEST_CHECKSUMCHECKER_H
#define STRUCTURETEST_CHECKSUMCHECKER_H

#include <cstdint>

class ChecksumChecker {

private:
    /**
     * calculates checksum with CRC16 algorithm ***** PARAMS: uint8_t data_array[] the array of data to calculate the checksum on | uint16_t length = sizeof(data_array)
     * @return a checksum value in uint16_t format
     */
    uint16_t calculateCRC16(uint8_t data_array[], uint16_t &length);

public:
    /**calls the function to calculate the checksum and compares it with the provided one from package *** PARAMS uint16_t package_checksum --> package provided checksum,
     * uint8_t* data_array --> the data to calculate the checksum on, uint16_t length = sizeof(data_array)
     * @return true if the checksum is successful
     */
    bool checkPackage(uint16_t &package_checksum, uint8_t data_array[], uint16_t &length);

};

#endif //STRUCTURETEST_CHECKSUMCHECKER_H
