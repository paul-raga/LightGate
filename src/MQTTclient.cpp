//
// Created by paul on 21/03/24.
//

#include "../include/MQTTclient.h"
#include <iostream>
#include <cstring>

#include "../include/ConfigReader.h"


#define MQTT_PORT 1883 //default Mosquitto port

std::string topic = ConfigReader::getValue("TOPIC");
std::string ip = ConfigReader::getValue("IP");


MQTTclient::MQTTclient() {
    this->clientInit();
}


void MQTTclient::clientInit() {
    //clean mosq struct
    this->mosq=NULL;

    // Initialize Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto client instance
    this->mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
    }

    // Connect to the MQTT broker
    if (mosquitto_connect(mosq, this->string_to_charPointer(ip), MQTT_PORT, 0) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to the MQTT broker.\n");
        mosquitto_destroy(mosq);
    }else{std::cout<<"connection enstablished"<<std::endl;}

}

MQTTclient::~MQTTclient() {
// Disconnect from the MQTT broker
    mosquitto_disconnect(mosq);

    // Destroy the Mosquitto client instance
    //also calls delete on local mosq
    mosquitto_destroy(mosq);

    // Clean up Mosquitto library
    mosquitto_lib_cleanup();

}

void MQTTclient::sendMessage(char * payload) {

    int length = strlen(payload);
    // Publish a message
    int ret = mosquitto_publish(mosq, nullptr, this->string_to_charPointer(topic), length, payload, 0, false);

    if (ret != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Error publishing message: %s\n", mosquitto_strerror(ret));
        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
    }

}


char* MQTTclient::string_to_charPointer(std::string string_)
{
    char* message_cstr = new char[string_.length() + 1];
    std::strcpy(message_cstr, string_.c_str());

    return message_cstr;
}


