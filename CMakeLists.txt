cmake_minimum_required(VERSION 3.13)

project(LSerialTerm LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Gui SerialPort REQUIRED)

set(HEADER_FILES
        LSerialTerm/MainWindow.h
        LSerialTerm/NewConnectionWindow.h)

set(SOURCE_FILES
        LSerialTerm/Main.cpp
        LSerialTerm/MainWindow.cpp
        LSerialTerm/NewConnectionWindow.cpp)

set(UI_FILES
        LSerialTerm/MainWindow.ui
        LSerialTerm/NewConnectionWindow.ui)

set(RESOURCE_FILES LSerialTerm/Resources.qrc)

add_executable(LSerialTerm ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})

target_link_libraries(LSerialTerm PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::SerialPort)
