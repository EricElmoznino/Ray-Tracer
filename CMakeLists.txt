cmake_minimum_required(VERSION 3.7)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Ofast -fopenmp")

set(SOURCE_FILES Ray\ Tracer/main.cpp)
file(GLOB SOURCES
        Ray\ Tracer/*.h
        Ray\ Tracer/*.cpp
        Ray\ Tracer/GeometricTypes/*.h
        Ray\ Tracer/GeometricTypes/*.cpp
        Ray\ Tracer/ObjectTypes/*.h
        Ray\ Tracer/ObjectTypes/*.cpp
        Ray\ Tracer/ObjectTypes/ObjectSubclasses/*.h
        Ray\ Tracer/ObjectTypes/ObjectSubclasses/*.cpp
        Ray\ Tracer/Lights/*.h
        Ray\ Tracer/Lights/*.cpp
        Ray\ Tracer/Utilities/*.h
        Ray\ Tracer/Utilities/*.cpp
    )
add_executable(Ray_Tracer ${SOURCE_FILES} ${SOURCES})