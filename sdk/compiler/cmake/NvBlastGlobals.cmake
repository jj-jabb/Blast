#
# Build NvBlastGlobals common
#

SET(GLOBALS_DIR ${PROJECT_SOURCE_DIR}/globals)
SET(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/common)

# Include here after the directories are defined so that the platform specific file can use the variables.
include(${PROJECT_CMAKE_FILES_DIR}/${TARGET_BUILD_PLATFORM}/NvBlastGlobals.cmake OPTIONAL)

SET(COMMON_FILES
	${COMMON_SOURCE_DIR}/NvBlastAssert.cpp
	${COMMON_SOURCE_DIR}/NvBlastAssert.h
)

SET(SOURCE_FILES
	${GLOBALS_DIR}/source/NvBlastGlobals.cpp
	${GLOBALS_DIR}/source/NvBlastProfiler.cpp
	${GLOBALS_DIR}/source/NvBlastProfilerInternal.h
)

SET(PUBLIC_FILES
	${GLOBALS_DIR}/include/NvBlastGlobals.h
	${GLOBALS_DIR}/include/NvBlastAllocator.h
	${GLOBALS_DIR}/include/NvBlastProfiler.h
	${GLOBALS_DIR}/include/NvBlastDebugRender.h
)

ADD_LIBRARY(NvBlastGlobals SHARED 
	${COMMON_FILES}
	${SOURCE_FILES}
	${PUBLIC_FILES}
)

SOURCE_GROUP("common" FILES ${COMMON_FILES})
SOURCE_GROUP("source" FILES ${SOURCE_FILES})
SOURCE_GROUP("public" FILES ${PUBLIC_FILES})

# Target specific compile options

TARGET_INCLUDE_DIRECTORIES(NvBlastGlobals 
	PUBLIC ${GLOBALS_DIR}/include
	PUBLIC ${GLOBALS_DIR}/source
    PRIVATE ${COMMON_SOURCE_DIR}
)

TARGET_COMPILE_DEFINITIONS(NvBlastGlobals 
	PRIVATE ${BLASTGLOBALS_COMPILE_DEFS}
)

TARGET_COMPILE_OPTIONS(NvBlastGlobals
	PRIVATE ${BLASTGLOBALS_PLATFORM_COMPILE_OPTIONS}
)

SET_TARGET_PROPERTIES(NvBlastGlobals PROPERTIES 
	PDB_NAME_DEBUG "NvBlastGlobals${CMAKE_DEBUG_POSTFIX}"
	PDB_NAME_CHECKED "NvBlastGlobals${CMAKE_CHECKED_POSTFIX}"
	PDB_NAME_PROFILE "NvBlastGlobals${CMAKE_PROFILE_POSTFIX}"
	PDB_NAME_RELEASE "NvBlastGlobals${CMAKE_RELEASE_POSTFIX}"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BL_LIB_OUTPUT_DIR}/debug"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BL_DLL_OUTPUT_DIR}/debug"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BL_EXE_OUTPUT_DIR}/debug"
    ARCHIVE_OUTPUT_DIRECTORY_CHECKED "${BL_LIB_OUTPUT_DIR}/checked"
    LIBRARY_OUTPUT_DIRECTORY_CHECKED "${BL_DLL_OUTPUT_DIR}/checked"
    RUNTIME_OUTPUT_DIRECTORY_CHECKED "${BL_EXE_OUTPUT_DIR}/checked"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${BL_LIB_OUTPUT_DIR}/profile"
    LIBRARY_OUTPUT_DIRECTORY_PROFILE "${BL_DLL_OUTPUT_DIR}/profile"
    RUNTIME_OUTPUT_DIRECTORY_PROFILE "${BL_EXE_OUTPUT_DIR}/profile"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BL_LIB_OUTPUT_DIR}/release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BL_DLL_OUTPUT_DIR}/release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BL_EXE_OUTPUT_DIR}/release"
)

# Do final direct sets after the target has been defined
TARGET_LINK_LIBRARIES(NvBlastGlobals 
	PRIVATE NvBlast 

	PUBLIC ${BLASTGLOBALS_PLATFORM_LINKED_LIBS}
)

