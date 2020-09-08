project(pong CXX)

################################################################################
# Source groups
################################################################################

set(Header_Files
    "Game.h"
    "GameplayScreen.h"
    "SceneRenderer.h"
    "ScreenIndices.h"
    "Ball.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Bootstrap.cpp"
    "Game.cpp"
    "GameplayScreen.cpp"
    "SceneRenderer.cpp"
    "Ball.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files})

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Test)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG    "${CMAKE_CURRENT_SOURCE_DIR}/../build/$<CONFIG>/"
    OUTPUT_DIRECTORY_DEBUGNCP "${CMAKE_CURRENT_SOURCE_DIR}/../build/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE  "${CMAKE_CURRENT_SOURCE_DIR}/../build/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE  "TRUE"
)
################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "_CONSOLE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DebugNCP>:"
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

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
        >
        $<$<CONFIG:DebugNCP>:
            /Od;
            ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /MD;
            /Gy
        >
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /SUBSYSTEM:CONSOLE;
            /INCREMENTAL;
            /verbose:lib
        >
        $<$<CONFIG:DebugNCP>:
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
endif ()

################################################################################
# Post build events
################################################################################
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/$<CONFIG>/Ess3D/Ess3D.dll ${OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/source/Ess3D/resources/shaders/ ${OUTPUT_DIRECTORY}/Shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources/ ${OUTPUT_DIRECTORY}
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Ess3D
    )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
    "Ess3D"
    ">"
    "$<$<CONFIG:DebugNCP>:"
    "Ess3D"
    ">"
    "$<$<CONFIG:Release>:"
    "Ess3D"
    ">"
    )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:"
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/Debug/Ess3D/;"
    ">"
    "$<$<CONFIG:DebugNCP>:"
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/Debug/Ess3D/;"
    ">"
    "$<$<CONFIG:Release>:"
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/build/Release/Ess3D/;"
    ">"
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Ess3D/source/;"
)