//
// Created by paul on 19/03/24.
//
#include "../include/StreamReader.h"
#include "../include/ByteToString.h"

#include <iostream>
#include <fcntl.h> //controllo file -> open()
#include <unistd.h> //write() read() close()
#include <termios.h> //terminal control interface
#include "../include/ByteToString.h"




void StreamReader::initializeCommunication(){
    int serial_port = open("/dev/ttyUSB0",
                           O_RDONLY); //apre la porta seriale associata a /dev/ttyUSB0 e ritorna l'identificatore
    if (serial_port == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        return ;
    }
    this->serialPort=serial_port;

    struct termios tty; //configurazione della connessione seriale
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Error getting serial port attributes." << std::endl;
        return ;
    }

    /**
     * 9600 to read terminal
     * 115200 to read LoRa
     */
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // Set other serial port options
    tty.c_cflag &= ~PARENB;  // Disable parity
    tty.c_cflag &= ~CSTOPB;  // One stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;      // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS; // Disable hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    // Set raw mode
    cfmakeraw(&tty);

    // Apply settings
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting serial port attributes." << std::endl;
        return;
    }
};


StreamReader::StreamReader() {
    this->myPackager=std::make_shared<Packager>();
    this->initializeCommunication();
}


StreamReader::~StreamReader() {
    close(this->serialPort);
}

void StreamReader::populateVector() {
    while (this->serialPort){
        // Read data from serial port
        uint8_t buffer[1]; //buffer da modificare in base alla mole di dati in arrivo

        long bytes_read = read(this->serialPort, buffer,sizeof (buffer));

        if (bytes_read < 0) {
            std::cerr << "Error reading from serial port." << std::endl;
            return ;
        }

        //ensures that termination character are not loaded into the dynamic array TODO delete this for LoRa implementation
        if((buffer[0]) >=0 && buffer[0] <= 255) {
            this->networkPackage.push_back(buffer[0]); //adds the current byte in the buffer to the dynamic array
        }

        if(this->networkPackage.size()==13){   //if inside the dynamic array there are least 13 elements it means that the data byte is available
            this->payloadLength = networkPackage[12]; //when the data length byte is available, store it in the variable
        }

        if(this->package_is_Received())
        {
            this->notityPackeger();
        }
    }
};


bool StreamReader::package_is_Received() {
    if(this->networkPackage.size() == this->payloadLength + 15){
        return true;
    }else
    {return false;}
}

//
void StreamReader::notityPackeger() {
    this->myPackager->loadData(this->networkPackage);
    this->freeMemory();
}


std::thread StreamReader::readerService() {
    return std::thread(&StreamReader::populateVector, this);
}


void StreamReader::freeMemory() {
    this->networkPackage = std::vector<uint8_t>();
}
