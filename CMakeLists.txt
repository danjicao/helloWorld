CMAKE_MINIMUM_REQUIRED (VERSION 3.5.2)


GET_CMAKE_PROPERTY (_variableNames VARIABLES)
FOREACH (_variableName ${_variableNames})
    MESSAGE (STATUS "${_variableName}=${${_variableName}}")
ENDFOREACH()


PROJECT (helloWorld)


SET (HELLOWORLD_SRCS
    main.cpp
)


ADD_EXECUTABLE (helloWorld
    ${HELLOWORLD_SRCS}
)

