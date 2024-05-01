#include <iostream>
#include <memory>
#include <thread>

#include "include/StreamReader.h"



//TODO REMEMBER TO CHANGE BAUD RATE IN STREAMREADER.cpp WHEN SWITCHING FROM TERMINAL TO LORA

int main() {

    std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>();

    std::thread service = reader->readerService();

    std::cin.get();


}

//TODO improve memory efficiency
//TODO safely deallocate objects in memory on program shutdown

