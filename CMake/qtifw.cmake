function(qtifw)
    cmake_parse_arguments("ARG" "" "TARGET;VENDOR;DESCRIPTION;VERSION;URL;LICENSE;COMPONENT_PACKAGE;INSTALLER_SCRIPT" "" ${ARGN})

    if (CPACK_IFW_ROOT OR DEFINED ENV{QTIFWDIR})
        set(CPACK_PACKAGE_NAME "${ARG_TARGET}")
        set(CPACK_PACKAGE_VENDOR "${ARG_VENDOR}")
        set(CPACK_PACKAGE_FILE_NAME "${ARG_TARGET}_Installer_Windows_x86")
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${ARG_DESCRIPTION}")

        set(CPACK_IFW_VERBOSE ON)
        set(CPACK_IFW_PACKAGE_NAME "${ARG_TARGET}")
        set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY "${ARG_TARGET}")
        set(CPACK_IFW_PRODUCT_URL "${ARG_URL}")
        set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Modern")
        set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDir@/${ARG_TARGET}")
        set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_NAME "Uninstaller")

        if (${CMAKE_CL_64})
            set(CPACK_PACKAGE_FILE_NAME "${ARG_TARGET}_Installer_Windows_x64")
            set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDirX64@/${ARG_TARGET}")
        endif ()

        set(CPACK_GENERATOR IFW)

        include(CPack REQUIRED)
        include(CPackIFW REQUIRED)

        cpack_add_component(
            ${ARG_TARGET}
            DISPLAY_NAME "${ARG_TARGET}"
            DESCRIPTION "${ARG_DESCRIPTION}"
            REQUIRED
        )

        cpack_ifw_configure_component(
            ${ARG_TARGET}
            NAME "${ARG_COMPONENT_PACKAGE}"
            VERSION "${ARG_VERSION}"
            LICENSES "License" "${ARG_LICENSE}"
            SCRIPT "${ARG_INSTALLER_SCRIPT}"
        )
    else ()
        message("If you want to enable target package you can:")
        message("   * Either pass -DCPACK_IFW_ROOT=<path> to cmake")
        message("   * Or set the environment variable QTIFWDIR")
    endif ()
endfunction()
