CMAKE_MINIMUM_REQUIRED(VERSION 3.13.0 FATAL_ERROR)

SET(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(dapolis-pong CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
IF (MSVC)
    IF (NOT CMAKE_VS_PLATFORM_NAME)
        SET(CMAKE_VS_PLATFORM_NAME "x64")
    ENDIF ()
    MESSAGE("${CMAKE_VS_PLATFORM_NAME} architecture in use")

    IF (NOT (("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64") OR ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")))
        MESSAGE(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
    ENDIF ()

    IF ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        SET(PLATFORM_ARCHITECTURE "Win64")
    ENDIF()
    IF ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        SET(PLATFORM_ARCHITECTURE "Win32")
    ENDIF()
ENDIF ()

IF (UNIX)
    SET(PLATFORM_ARCHITECTURE "x86_x64")
ENDIF()

################################################################################
# Global configuration types
################################################################################
SET(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
    )

################################################################################
# Global compiler options
################################################################################
IF (MSVC)
    # remove default flags provided with CMake for MSVC
    SET(CMAKE_CXX_FLAGS "")
    SET(CMAKE_CXX_FLAGS_DEBUG "")
    SET(CMAKE_CXX_FLAGS_RELEASE "")
ENDIF ()

################################################################################
# Global linker options
################################################################################
IF (MSVC)
    # remove default flags provided with CMake for MSVC
    SET(CMAKE_EXE_LINKER_FLAGS "")
    SET(CMAKE_MODULE_LINKER_FLAGS "")
    SET(CMAKE_SHARED_LINKER_FLAGS "")
    SET(CMAKE_STATIC_LINKER_FLAGS "")
    SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
ENDIF ()

################################################################################
# Common utils
################################################################################
INCLUDE(dependencies/Ess3D/cmake/Utils.cmake)

################################################################################
# Use solution folders feature
################################################################################
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################
ADD_SUBDIRECTORY(dependencies/Ess3D/source/Ess3D)
ADD_SUBDIRECTORY(source)

