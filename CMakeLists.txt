CMAKE_MINIMUM_REQUIRED (VERSION 3.5.2)


OPTION (enable_shared_libsysinfo "enable shared libsysinfo" ON)
OPTION (enable_shared_libhello "enable shared libhello" ON)


GET_CMAKE_PROPERTY (_variableNames VARIABLES)
FOREACH (_variableName ${_variableNames})
    MESSAGE (STATUS "${_variableName}=${${_variableName}}")
ENDFOREACH()


## location of additional cmake modules
SET (CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)


INCLUDE (git_revision)
INCLUDE (uninstall)



PROJECT (helloWorld
    VERSION "0.1.0.0"
)


INCLUDE (install)


CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)


SET (HELLOWORLD_SRCS
    main.cpp
)


ADD_SUBDIRECTORY (libhello)
ADD_SUBDIRECTORY (libsysinfo)


INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
) 


ADD_EXECUTABLE (helloWorld
    ${HELLOWORLD_SRCS}
)


IF (enable_shared_libhello)
    TARGET_LINK_LIBRARIES (helloWorld
        libhello
    )
ELSE ()
    TARGET_LINK_LIBRARIES (helloWorld
        libhello-static
    )
ENDIF ()


IF (enable_shared_libsysinfo)
    TARGET_LINK_LIBRARIES (helloWorld
        libsysinfo
    )
ELSE ()
    TARGET_LINK_LIBRARIES (helloWorld
        libsysinfo-static
    )
ENDIF ()


INSTALL (TARGETS helloWorld
        RUNTIME DESTINATION bin
)


