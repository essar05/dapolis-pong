PROJECT(pong CXX)

################################################################################
# Source groups
################################################################################

SET(Header_Files
    "Game.h"
    "screens/GameplayScreen.h"
    "screens/ScreenIndices.h"
    "models/Ball.h"
    "models/Paddle.h"
    )
SOURCE_GROUP("Header Files" FILES ${Header_Files})

SET(Source_Files
    "Bootstrap.cpp"
    "Game.cpp"
    "screens/GameplayScreen.cpp"
    "models/Ball.cpp"
    "models/Paddle.cpp"
    )
SOURCE_GROUP("Source Files" FILES ${Source_Files})

SET(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
    models/Entity.cpp models/Entity.h
    game/World.cpp game/World.h
    game/Scene.cpp game/Scene.h)

################################################################################
# Target
################################################################################
ADD_EXECUTABLE(${PROJECT_NAME} ${ALL_FILES})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

USE_PROPS(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
SET(ROOT_NAMESPACE Test)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
    )
################################################################################
# Output directory
################################################################################
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../build/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../build/$<CONFIG>/"
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
        "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "UNICODE;"
        "_UNICODE"
        ">"
        "WIN32;"
        "_LIB;"
        "_CRT_SECURE_NO_WARNINGS"
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
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/$<CONFIG>/Ess3D/Ess3D.dll ${OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/$<CONFIG>/Ess3D/Ess3D.pdb>$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/$<CONFIG>/Ess3D/Ess3D.dll>" ${OUTPUT_DIRECTORY}
        )
ENDIF (MSVC)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/source/Ess3D/resources/shaders/ ${OUTPUT_DIRECTORY}/shaders
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/$<CONFIG>/Ess3D/;"
    )

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/source/;"
    )