cmake_minimum_required(VERSION 3.21)
project(postgres_csv_parser)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(postgres_csv_parser
        main.cpp src/Parser.cpp include/Parser.h include/HelperUtils.h src/Worker.cpp include/Worker.h)
