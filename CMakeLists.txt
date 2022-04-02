cmake_minimum_required(VERSION 3.17)
project(babel_server)
project(babel_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -luuid")

if (UNIX)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
endif ()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/Client/include/")
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/Server/include/")
include(${CMAKE_CURRENT_SOURCE_DIR}/build/conan_paths.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets Gui Core Network)

set(CLIENT 
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/Error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/Package.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/communication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/audio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/AudioPa.cpp
)

set(SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/Error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/Package.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/communication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/network.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/Serialize.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/audio.cpp
)

add_executable(babel_server  ${SERVER})

add_executable(babel_client ${CLIENT})

target_link_libraries(babel_server)

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Core Qt5::Network Qt5::Gui)