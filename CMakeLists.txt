cmake_minimum_required(VERSION 3.10.2)

project(Texere)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem thread locale)

add_executable(texere src/http_wrapper.cpp)

target_link_libraries(texere Boost::system Boost::filesystem Boost::thread Boost::locale)