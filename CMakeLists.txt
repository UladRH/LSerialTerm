cmake_minimum_required(VERSION 3.16)

project(LSerialTerm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Gui SerialPort REQUIRED)
set(QTDIR ${Qt5_DIR}/../../..)

set(HEADER_FILES
    LSerialTerm/MainWindow.h
    LSerialTerm/NewConnectionWindow.h
    LSerialTerm/Widgets/HexConsole.h
    LSerialTerm/Widgets/TerminalManager.hpp)

set(SOURCE_FILES
    LSerialTerm/Main.cpp
    LSerialTerm/MainWindow.cpp
    LSerialTerm/NewConnectionWindow.cpp
    LSerialTerm/Widgets/HexConsole.cpp
    LSerialTerm/Widgets/TerminalManager.cpp)

set(UI_FILES
    LSerialTerm/MainWindow.ui
    LSerialTerm/NewConnectionWindow.ui)

set(RESOURCE_FILES LSerialTerm/Resources.qrc)

add_executable(LSerialTerm WIN32 ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})

target_link_libraries(LSerialTerm PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::SerialPort)

install(
    TARGETS LSerialTerm
    RUNTIME DESTINATION LSerialTerm
    COMPONENT LSerialTerm
    BUNDLE DESTINATION LSerialTerm
    COMPONENT LSerialTerm
)

include(CMake/windeployqt.cmake)
include(CMake/qtifw.cmake)

windeployqt(TARGET LSerialTerm INSTALL)

qtifw(
    TARGET LSerialTerm
    VENDOR "Uladzislau Hlebovich"
    DESCRIPTION LSerialTerm
    VERSION ${PROJECT_VERSION}
    URL https://github.com/LightSunrider/LSerialTerm
    LICENSE ${LSerialTerm_SOURCE_DIR}/LICENSE
    INSTALLER_SCRIPT "${LSerialTerm_SOURCE_DIR}/Installer/component.js"
)
