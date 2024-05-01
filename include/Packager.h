//
// Created by paul on 19/03/24.
//
#include <string>
#include <vector>
#include <memory>

#include "MQTTclient.h"
#include "ChecksumChecker.h"

#ifndef STRUCTURETEST_PACKAGER_H
#define STRUCTURETEST_PACKAGER_H

class Packager{
private:
    /** vector representing the network package that has to be checked and packaged into a (json?)*/
    std::vector<uint8_t> serialData;
    /**instance of the checksum calculator*/
   std::shared_ptr<ChecksumChecker> checksumChecker;
    /**instance of the MQTT client to publish we messages*/
    std::shared_ptr<MQTTclient> clientMQTT;


    /**
     * formats the content on the package to a string
     * @return a string
     */
    std::string format_to_String();

    /**
     * invokes ChecksumChecker to check if the checksum is ok
     * @return true is the checksum is ok
     */
    bool checkChecksum();

    /**if the checksum is OK, transmits the package*/
    void publishToCloud();

public:
    /**sends a provided package under the form of a std::vector to the Packager,
     * il will invoke the necessary stack to transmit the package via MQTT if the checksum is ok*/
    void loadData(std::vector<uint8_t> &vector);

    Packager();

};


#endif //STRUCTURETEST_PACKAGER_H
