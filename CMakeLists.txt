cmake_minimum_required(VERSION 3.10.2)

project(Texere)


find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem thread locale)
add_executable(texere_server src/server_x/http_wrapper.cpp)
target_link_libraries(texere_server Boost::system Boost::filesystem Boost::thread Boost::locale)
target_compile_features(texere_server PUBLIC cxx_std_11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
add_executable(texere_ui_x src/ui_x/main.cpp)
target_link_libraries(texere_ui_x Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
