cmake_minimum_required(VERSION 3.21)
project(projeto2)

set(CMAKE_CXX_STANDARD 14)

add_executable(projeto2 main.cpp BaseDados.cpp BaseDados.h graph.cpp graph.h minHeap.h)
