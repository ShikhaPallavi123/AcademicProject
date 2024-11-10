cmake_minimum_required(VERSION 3.27)
project(p1x)

set(CMAKE_CXX_STANDARD 14)

add_executable(p1x p1x.cpp
        BookList.h
        BookList.cpp
        MemberList.h
        MemberList.cpp
        RatingList.h
        RatingList.cpp)
