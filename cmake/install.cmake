## Set installation prefix automatically to custom path if not explicitly specified on the command line
## http://stackoverflow.com/questions/16074598/set-installation-prefix-automatically-to-custom-path-if-not-explicitly-specified
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
