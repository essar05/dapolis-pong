PROJECT(pong CXX)

################################################################################
# Source groups
################################################################################

SET(ALL_FILES
    Bootstrap.cpp
    Game.cpp Game.h
    screens/GameplayScreen.cpp screens/GameplayScreen.h
    models/Ball.cpp models/Ball.h
    models/Paddle.cpp models/Paddle.h
    game/World.cpp game/World.h
    game/Scene.cpp game/Scene.h
    )

################################################################################
# Target
################################################################################
ADD_EXECUTABLE(${PROJECT_NAME} ${ALL_FILES})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

USE_PROPS(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
SET(ROOT_NAMESPACE Test)

################################################################################
# Output directory
################################################################################
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
    )
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )

################################################################################
# Compile and link options
################################################################################
IF (MSVC)
    ################################################################################
    # Compile definitions
    ################################################################################

    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "_CONSOLE;"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        ">"
        "WIN32;"
        "_CRT_SECURE_NO_WARNINGS;"
        "UNICODE;"
        "_UNICODE;"
        )

    TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /Od;
        ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
        >
        $<$<CONFIG:Release>:
        /O2;
        /Oi;
        /MD;
        /Gy;
        /utf-8
        >
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
        )

    TARGET_LINK_OPTIONS(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /DEBUG;
        /SUBSYSTEM:CONSOLE;
        /INCREMENTAL;
        /verbose:lib
        >
        $<$<CONFIG:Release>:
        /SUBSYSTEM:WINDOWS;
        /ENTRY:wmainCRTStartup
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
        >
        )

ENDIF ()

################################################################################
# Post build events
################################################################################

IF (MSVC)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/Ess3D.dll ${OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/Ess3D.pdb>$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/Ess3D.dll>" ${OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/dependencies/bin/${PLATFORM_ARCHITECTURE}/$<CONFIG> ${OUTPUT_DIRECTORY}
        )
ENDIF (MSVC)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/source/resources/shaders/ ${OUTPUT_DIRECTORY}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${OUTPUT_DIRECTORY}
    )

################################################################################
# Dependencies
################################################################################
ADD_DEPENDENCIES(${PROJECT_NAME}
    Ess3D
    )

SET(ADDITIONAL_LIBRARY_DEPENDENCIES
    "Ess3D"
    )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

TARGET_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Ess3D/build/Ess3D/${PLATFORM_ARCHITECTURE}/$<CONFIG>/;"
    )