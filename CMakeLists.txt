cmake_minimum_required(VERSION 3.14)
project(ohcs VERSION 4.0.0 LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_COLOR_DIAGNOSTICS ON)

find_library(gmp gmp)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(include)

add_library(ocss src/interface.cpp src/io.cpp src/OCSS.cpp)
add_executable(ohcs)
target_sources(ohcs PRIVATE src/main.cpp)
target_include_directories(ohcs PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(ohcs PRIVATE ocss PRIVATE gmp PRIVATE Boost::program_options)