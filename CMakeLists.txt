CMAKE_MINIMUM_REQUIRED (VERSION 3.5.2)


OPTION (enable_shared_libsysinfo "enable shared libsysinfo" ON)
OPTION (enable_shared_libhello "enable shared libhello" ON)
OPTION (enable_plugins "enable plugins" ON)
OPTION (enable_shared_libplugins "enable shared libplugins" ON)


IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    SET (CMAKE_C_FLAGS   "-Werror" CACHE STRING "" FORCE)
    SET (CMAKE_CXX_FLAGS "-Werror" CACHE STRING "" FORCE) # -Werror: Make all warnings into errors.
    SET (CMAKE_CXX_FLAGS "-Wall" CACHE STRING "" FORCE)
    SET (CMAKE_CXX_FLAGS "-pedantic" CACHE STRING "" FORCE)
    SET (CMAKE_CXX_FLAGS "-Wextra" CACHE STRING "" FORCE)
ENDIF ()


IF (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  MESSAGE (STATUS "No build type selected, default to Debug")
  SET (CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
ENDIF()


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


STRING (TIMESTAMP PROJECT_BUILD_TIME "%Y-%m-%dT%H:%M:%SZ" UTC)


PROJECT (helloWorld
    VERSION "0.1.0.0"
)


INCLUDE (install)


CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)


SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREADED ON)
SET (Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE( Boost 1.63 COMPONENTS program_options REQUIRED )


SET (HELLOWORLD_SRCS
    main.cpp
)


ADD_SUBDIRECTORY (libhello)
ADD_SUBDIRECTORY (libsysinfo)
#ADD_SUBDIRECTORY (thirdparty/json)


INCLUDE_DIRECTORIES(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
) 


ADD_EXECUTABLE (${PROJECT_NAME}
    ${HELLOWORLD_SRCS}
)


SET_TARGET_PROPERTIES (${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD                11
)


TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME}
    PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/json/src"
    PUBLIC  "${Boost_INCLUDE_DIR}"
)


TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${Boost_LIBRARIES} )


IF (enable_shared_libhello)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME}
        libhello
    )
ELSE ()
    TARGET_LINK_LIBRARIES (${PROJECT_NAME}
        libhello-static
    )
ENDIF ()


IF (enable_shared_libsysinfo)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME}
        libsysinfo
    )
ELSE ()
    TARGET_LINK_LIBRARIES (${PROJECT_NAME}
        libsysinfo-static
    )
ENDIF ()


IF (enable_plugins)
    ADD_DEFINITIONS(
        -DENABLE_PLUGINS
    )

    ADD_SUBDIRECTORY (libplugins)
    ADD_SUBDIRECTORY (libpluginhelper)
    ADD_SUBDIRECTORY (plugins/libexample)

    IF (enable_shared_libplugins)
        TARGET_LINK_LIBRARIES (${PROJECT_NAME} libplugins)
    ELSE ()
        TARGET_LINK_LIBRARIES (${PROJECT_NAME} libplugins-static)
    ENDIF ()
ENDIF ()


INSTALL (TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)


