//
// Created by paul on 19/03/24.
//
#include <cstring>
#include "../include/Packager.h"
#include "../include/ByteToString.h"
#include "../include/JsonFormatter.h"

void Packager::loadData(std::vector<uint8_t> &vector) {
    this->serialData=vector;

    this->publishToCloud();
}



bool Packager::checkChecksum() {

    uint8_t data_array[this->serialData.size()-4]; //creates a dataArray excluding SOP and Checksum fields
    for(int i=0; i<this->serialData.size()-4; i++){ //populates the dataArray with Header and Payload
        data_array[i] = serialData[i+2]; // from first byte of Header (package[2]) to last byte of Payload (package[package_size - 2])
    }

    data_array[7] = 0x00; //TODO THIS IS THE ERROR IN THE NODE TRANSMISSION, ALTHOUGH IT IS TRANSMITTED CORRECTLY THE CHECKSUM IS CALCULATED UPON AN RSSI VALUE OF 0x00

    uint16_t old_checksum = this->serialData[this->serialData.size()-1] * 256 + this->serialData[this->serialData.size()-2]; //the package provided checksum is in the last two bytes of the vector

    //std::cout<<old_checksum<<std::endl;

    uint16_t length = sizeof (data_array); //the length of the data array

    if(this->checksumChecker->checkPackage(old_checksum,data_array,length)){
        return true;
    }else{
        return false;}
}


void Packager::publishToCloud() {
    std::string  message = this->format_to_String();

    char* message_cstr = new char[message.length() + 1];
    std::strcpy(message_cstr, message.c_str());


    if(this->checkChecksum()){
        this->clientMQTT->sendMessage(message_cstr);
    }

    delete[] message_cstr;

}



std::string Packager::format_to_String() {
 std::string outstring;

 outstring.append("***PACKAGE ");
 outstring.append("{ {");

    for (int i=0; i<=12; i++)

    {
        outstring.append(JsonFormatter::getString(i));

        outstring.append(ByteToString::getValue(this->serialData[i]));
    }
    outstring.append("}");
    outstring += '\n';

    outstring.append("{");
    outstring.append(" Payload : ");

    for (int i = 0; i < this->serialData[12] ; i++) {
        outstring.append(ByteToString::getValue(this->serialData[i +13]));
    }

    outstring.append("}");
    outstring += '\n';

    outstring.append("{");
    outstring.append(" CKsum : ");
    outstring.append( ByteToString::getValue(this->serialData[this->serialData.size()-1]));
    outstring.append( ByteToString::getValue(this->serialData[this->serialData.size()-2]));

    outstring.append("} }");

    outstring.append(" END***");

    //std::cout<<outstring<<std::endl;


    return outstring;

}

Packager::Packager() {
    this->checksumChecker=std::make_shared<ChecksumChecker>();
    this->clientMQTT=std::make_shared<MQTTclient>();

}



