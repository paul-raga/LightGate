//
// Created by paul on 21/03/24.
//
#include <string>
#include <cstring>
#include "../include/mosquitto.h"

#ifndef STRUCTURETEST_MQTTCLIENT_H
#define STRUCTURETEST_MQTTCLIENT_H


class MQTTclient{

private:
    /** stores the struct objet when creating a mosquitto client instance*/
    struct mosquitto *mosq;

    /**initialized the MQTT client*/
    void clientInit();

    char * string_to_charPointer(std::string string_);


public:
    /**CONSTRUCTOR calls for clientInit() */
    MQTTclient();
    /**DESTRUCTOR calls for client disconnection and destruction*/
    ~MQTTclient();

    /**sends a message to the MQTT broker with default topic and provided message*/
    void sendMessage(char * message);
};


#endif //STRUCTURETEST_MQTTCLIENT_H
