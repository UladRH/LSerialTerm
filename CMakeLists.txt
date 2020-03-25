cmake_minimum_required(VERSION 3.13)

project(LSerialTerm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Gui SerialPort REQUIRED)

set(HEADER_FILES
    LSerialTerm/MainWindow.h
    LSerialTerm/NewConnectionWindow.h
    LSerialTerm/HexConsole.h)

set(SOURCE_FILES
    LSerialTerm/Main.cpp
    LSerialTerm/MainWindow.cpp
    LSerialTerm/NewConnectionWindow.cpp
    LSerialTerm/HexConsole.cpp)

set(UI_FILES
    LSerialTerm/MainWindow.ui
    LSerialTerm/NewConnectionWindow.ui)

set(RESOURCE_FILES LSerialTerm/Resources.qrc)

add_executable(LSerialTerm WIN32 ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})

target_link_libraries(LSerialTerm PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::SerialPort)

# https://github.com/skypjack/gh-greets-qt

install(TARGETS LSerialTerm
    RUNTIME DESTINATION LSerialTerm
    COMPONENT LSerialTerm
    BUNDLE DESTINATION LSerialTerm
    COMPONENT LSerialTerm)

if (CPACK_IFW_ROOT OR DEFINED ENV{QTIFWDIR})
    if (DEFINED ENV{QTDIR})
        set(CPACK_PACKAGE_NAME LSerialTerm)
        set(CPACK_PACKAGE_VENDOR "Uladzislau Hlebovich")
        set(CPACK_PACKAGE_FILE_NAME LSerialTerm_Installer_x86)
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LSerialTerm")

        set(CPACK_IFW_VERBOSE ON)
        set(CPACK_IFW_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY LSerialTerm)
        set(CPACK_IFW_PRODUCT_URL https://github.com/LightSunrider/LSerialTerm)
        set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Modern")
        set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDir@/LSerialTerm")
        set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_NAME "Uninstaller")

        if (${CMAKE_CL_64})
            set(CPACK_PACKAGE_FILE_NAME LSerialTerm_Installer_x64)
            set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDirX64@/LSerialTerm")
        endif ()


        set(CPACK_GENERATOR IFW)

        include(CPack REQUIRED)
        include(CPackIFW REQUIRED)

        if (EXISTS $ENV{QTDIR}/bin/windeployqt.exe)
            if (CMAKE_BUILD_TYPE MATCHES Release)
                set(BINARIES_TYPE --release)
            else ()
                set(BINARIES_TYPE --debug)
            endif ()

            add_custom_command(
                TARGET LSerialTerm POST_BUILD
                #  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/windeployqt_stuff
                COMMAND $ENV{QTDIR}/bin/windeployqt.exe ${BINARIES_TYPE} --compiler-runtime --no-system-d3d-compiler --no-angle --no-webkit2 --no-quick-import --no-translations --dir ${CMAKE_BINARY_DIR}/windeployqt_stuff $<TARGET_FILE:LSerialTerm>
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/windeployqt_stuff/ $<TARGET_FILE_DIR:LSerialTerm>
            )

            install(
                DIRECTORY ${CMAKE_BINARY_DIR}/windeployqt_stuff/
                DESTINATION LSerialTerm
                COMPONENT LSerialTerm
            )

            cpack_add_component(
                LSerialTerm
                DISPLAY_NAME LSerialTerm
                DESCRIPTION "LSerialTerm"
                REQUIRED
            )

            cpack_ifw_configure_component(
                LSerialTerm
                NAME me.sviet.${PROJECT_NAME}
                VERSION ${PROJECT_VERSION}
                LICENSES "License" ${LSerialTerm_SOURCE_DIR}/LICENSE
                SCRIPT "${LSerialTerm_SOURCE_DIR}/Installer/component.js"
            )
        else ()
            message("Unable to find executable QTDIR/bin/windeployqt.")
        endif ()
    else ()
        message("Set properly environment variable QTDIR to be able to create a package.")
    endif ()
else ()
    message("If you want to enable target package you can:")
    message("\t* Either pass -DCPACK_IFW_ROOT=<path> to cmake")
    message("\t* Or set the environment variable QTIFWDIR")
    message("To specify the location of the QtIFW tool suite.")
    message("The specified path should not contain bin at the end (for example: D:\\DevTools\\QtIFW2.0.5).")
endif ()
