cmake_minimum_required(VERSION 3.27)
project(p3)

set(CMAKE_CXX_STANDARD 14)

add_executable(p3 p3.cpp
        Patient.h
        PatientPriorityQueue.h)
