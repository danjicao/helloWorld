CMAKE_MINIMUM_REQUIRED (VERSION 3.5.2)


GET_CMAKE_PROPERTY (_variableNames VARIABLES)
FOREACH (_variableName ${_variableNames})
    MESSAGE (STATUS "${_variableName}=${${_variableName}}")
ENDFOREACH()


PROJECT (helloWorld)


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

