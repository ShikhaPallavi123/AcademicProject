cmake_minimum_required(VERSION 3.27)
project(p3x)

set(CMAKE_CXX_STANDARD 14)

add_executable(p3x p3x.cpp
        Patient.h
        PatientPriorityQueuex.h)
