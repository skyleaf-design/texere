cmake_minimum_required(VERSION 3.10.2)

# These variables must be set BEFORE the project command!
set(CMAKE_PREFIX_PATH "C:\\Qt-5.11\\5.11.0\\msvc2015")
# set(CMAKE_TOOLCHAIN_FILE "/c/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE "C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
set(CMAKE_AUTOMOC ON)

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

# Windows: copy relavent Qt5 DLL libraries beside the executable.
add_custom_command(
    TARGET texere_ui_x POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE:Qt5::Network>
        $<TARGET_FILE_DIR:texere_ui_x>
)

target_link_libraries(texere_ui_x Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
