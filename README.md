# LightGate v0.2

Beta **UNTESTED** version of a LoRa custom packet transportation software. 

This software is meant to run on a Linux machine, and is DEPENDENT ON THE FOLLOWING SOFTWARES and LIBRARIES: 

 _ Cmake version 3.22 or older 
 
 _ Make version 4.3 
 
 _ GNU GCC (g++ version 11.4.0)
 
 _ pthread from POSIX (libpthread)
 
 _ Eclipse Mosquitto (MQTT broker) --> https://mosquitto.org
 
 _ libmosquitto-dev, development header from the mosquitto library

You can install all of them via your package manager; on debian-based systems (Ubuntu, Debian, Mint ecc..) the commands will be: 

$sudo apt install build-essential
$sudo apt install cmake
$sudo apt install make (should already be installed by default on the system)
$sudo apt install g++ (should be contained in build-essentials)
$sudo apt install mosquitto (debian mirror)  or   $sudo snap install mosquitto (eclipse mirror)
optional -> $sudo apt install libmosquitto-dev (to use the latest version of the Mosquitto development headers. CMakeList.txt has to be modified accordingly)

GNU GCC is already pre-installed on most linux distributions, pthread is part of the Glibc library.

HOW IT WORKS:

The application reads asynchronously serial data in input from a USB device, pseudo-parses the data red, performs a crc16 checksum calculation after each virtual packet is fully received and compares it with the checksum provided in the packet itself to check for data integrity. After all that, the app creates a Json-like string with the packet bytes and transmits it to a local / remote server via MQTT protocol.

DEFAULT PACKET STRUCTURE:

 **********************************
 | SOP | HEADER | DATA | Checksum |
 **********************************

 Sop: 2 B 
 
 Header: MAC Source Address 1 B, MAC Target Address 1 B, APP Source Address 1 B, APP Target Address 1 B, PAN ID 2 B, Options 1 B, RSSI LastHop 1 B, Sequence Number 1 B, Type 1 B, Length 1 B

 Data: 0-255 B

 Checksum: 2 B (calculated on header + data bytes excluding sop and checksum)



BUILD AND RUN: 

_ clone the repository 
$git clone -b Gate_v0.2 https://github.com/paulRagazziniUnicam/Gateway_0.0.1

_ traverse to the cloned repository, create a build folder and traverse to it 
$cd Gateway_0.0.1 
$mkdir build
$cd build 

_ generate the build files from the CMakeList.txt in the parent directory
$cmake ..

_ build the project 
$make

You have now created an executable named 'Gate'

_ can run it with 
$./Gate 

_ press Enter to stop execution

If you get the error "Unable to open serial port" and you are not root you might need to change the ownership of the connected usb serial device:

_ from the root of the file system: $cd dev

_ $sudo chown -user- ttyUSB0 (or the whatever number of the serial device you are using)


HOW TO USE:

By default the app uses port 1883 for the network transmission. 
You can specify your target server ipv4 and messaging topic modifyng the variable values in the "config.txt" file. IP Options are:

"localhost" to transmit to address 127.0.0.1 if you have a broker running on the same machine where the app is running

"192.168...." ipv4 address to transmit to a broker on your LAN 

"http://example-url.com" to transmit to a broker on a different network

By default, the message's topic is "test", you can modify it to whatever string you want as long as it matcher the topic your server is subscribed to.


 If you need safe transportation, use port 8883 insted of 1883. You might also want to add client certificates to secure the communication: this can be done with the function:
 mosquitto_tls_set(your_mosq_struct, "/path/to/ca_certificate.crt", NULL, "/path/to/client_certificate.crt", "/path/to/client_key.key", NULL);
 before the mosquitto_connect(params...) function. See https://mosquitto.org/api/files/mosquitto-h.html for the documentation 


 OPTIONAL -> SETUP OF A MOSQUITTO MQTT BROKER AS THE SERVER 

 If you want to use Mosquitto broker on your listening server, steps are:

 _ install mosquitto (on Debian $sudo apt install mosquitto)
 
 _ install mosquitto client package ($sudo apt install mosquitto-clients)

 _ if you want to listen on the machine ipv4 ip address without permission requirements (very unsafe, should be used for debugging purposes only), append to the the mosquitto.conf file (/etc/mosquitto/mosquitto.conf) the following two lines:  "listener 1883 0.0.0.0" and "allow_anonymous true"

 _run the command: $mosquitto_sub -h -your_ipvf4- -t "-your_topic-"             (topic=test if you run the default configuration)

 Enjoy

 

 





