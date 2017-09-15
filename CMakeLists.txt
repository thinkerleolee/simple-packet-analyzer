cmake_minimum_required(VERSION 3.8)
project(pcap_task)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DataReceiver.cpp DataReceiver.h FilterDataReceiver.cpp FilterDataReceiver.h)
set(CMAKE_EXE_LINKER_FLAGS "-lpcap")
add_executable(pcap_task ${SOURCE_FILES})
