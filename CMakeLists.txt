CMAKE_MINIMUM_REQUIRED (VERSION 3.5.2)


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


CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)


SET (HELLOWORLD_SRCS
    main.cpp
)


ADD_SUBDIRECTORY (libhello)
ADD_SUBDIRECTORY (libsysinfo)


ADD_EXECUTABLE (helloWorld
    ${HELLOWORLD_SRCS}
)

TARGET_LINK_LIBRARIES (helloWorld
    libhello
    libsysinfo
)


INSTALL (TARGETS helloWorld
        RUNTIME DESTINATION bin
)

