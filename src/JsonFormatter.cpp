//
// Created by paul on 26/03/24.
//

#include "../include/JsonFormatter.h"

std::string JsonFormatter::getString(int value) {
    switch(value){
        case 0: return " 'SOP' : ";
        case 2: return "| 'MAC src' : ";
        case 3: return "| 'MAC trg' : ";
        case 4: return "| 'App src' : ";
        case 5: return "| 'App trg' : ";
        case 6: return "| 'PAN ID' : ";
        case 8: return "| 'Opt' : ";
        case 9: return "| 'RSSI' : ";
        case 10: return "| 'Seq Num' : ";
        case 11: return "| 'Type' : ";
        case 12: return "| 'Payload length' : ";

        default: return "";
    }
}
