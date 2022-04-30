cmake_minimum_required(VERSION 3.16)
project(postgres_csv_parser)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-pthread")

include_directories(include)
find_package(spdlog REQUIRED)

add_executable(postgres_csv_parser
        main.cpp src/Parser.cpp include/Parser.h include/HelperUtils.h src/Worker.cpp include/Worker.h include/INIReader.h)

target_link_libraries(postgres_csv_parser PRIVATE spdlog::spdlog)
