//
// Created by paul on 19/03/24.
//
#include <vector>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <memory>

#include "Packager.h"

#ifndef STRUCTURETEST_STREAMREADER_H
#define STRUCTURETEST_STREAMREADER_H

# pragma once

class StreamReader{

private:
    /**value that stores the return value of open() when opening a serial port*/
    int serialPort;

    /**value that stores the payload length from of the package currently being transmitted*/
    int payloadLength;

    /**dynamic array that stores the package byte by byte (ex: at location [12] there will be byte of the payload length)*/
    std::vector<uint8_t> networkPackage;

    /**opens the serial communication to port ttyUSB0 and sets the necessary (default) values*/
    void initializeCommunication();

    /**sends the dynamic array containing the bytes of the package to the Packager*/
    void notityPackeger();

    /**
     * once per cycle, checks if the last byte of the package is received
     * @return true if the current package if fully received
     */
    bool package_is_Received();

    /**loop where the bytes in input from the serial transmission are written to the dynamic array*/
    void populateVector();

    /**clears the content of the dynamic array*/
    void freeMemory();

    //instance of a Packager class for debugging purposes, TODO to be substituted by a Packager singleton
   std::shared_ptr <Packager> myPackager;

public:
    /**
     * CONSTRUCTOR *** CALLS: initializeCommunication()
     */
    StreamReader();
    /**
     * DESTRUCTOR *** CALLS: posix::close() with the stored serial port integer
     */
    ~StreamReader();

    /**
     * starts a USB serial serial reading service on ttyUSB0
     * @return the reference to the thread where the reading takes place
     */
    std::thread readerService();
};


#endif //STRUCTURETEST_STREAMREADER_H
