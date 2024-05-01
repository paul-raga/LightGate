cmake_minimum_required(VERSION 3.22)
project(Gate)

set(CMAKE_CXX_STANDARD 17)

add_executable(Gate main.cpp
        include/StreamReader.h
        src/StreamReader.cpp
        include/Packager.h
        src/Packager.cpp
        src/ChecksumChecker.cpp
        include/ChecksumChecker.h
        src/MQTTclient.cpp
        include/MQTTclient.h
        src/JsonFormatter.cpp
        src/ByteToString.cpp
        include/mosquitto.h
        src/ConfigReader.cpp
        include/ConfigReader.h
)

set(mosquitto /usr/lib/libmosquitto.so)

target_link_libraries(Gate pthread mosquitto)


