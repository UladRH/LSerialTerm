function(windeployqt)
    cmake_parse_arguments("ARG" "INSTALL" "TARGET" "" ${ARGN})

    get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if (GENERATOR_IS_MULTI_CONFIG)
        set(_BUILD_TYPE "$<IF:$<CONFIG:Debug>,debug,release>")
        set(_BIN_DIR $<TARGET_FILE_DIR:${ARG_TARGET}>)

    else ()
        set(_BIN_DIR ${CMAKE_BINARY_DIR})

        if (CMAKE_BUILD_TYPE MATCHES Release)
            set(_BUILD_TYPE "release")
        else ()
            set(_BUILD_TYPE "debug")
        endif ()
    endif ()

    add_custom_command(
        TARGET LSerialTerm POST_BUILD

        COMMAND
        ${QTDIR}/bin/windeployqt.exe
        --${_BUILD_TYPE}
        --compiler-runtime
        --no-system-d3d-compiler
        --no-opengl-sw
        --no-angle
        --no-webkit2
        --no-quick-import
        --no-translations
        --dir ${_BIN_DIR}/windeployqt_stuff
        $<TARGET_FILE:LSerialTerm>

        COMMAND ${CMAKE_COMMAND} -E copy_directory ${_BIN_DIR}/windeployqt_stuff/ $<TARGET_FILE_DIR:LSerialTerm>
    )

    if (${ARG_INSTALL})
        install(
            DIRECTORY ${_BIN_DIR}/windeployqt_stuff/
            DESTINATION ${ARG_TARGET}
            COMPONENT ${ARG_TARGET}
        )
    endif ()
endfunction()
