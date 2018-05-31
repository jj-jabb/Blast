#
# Build NvBlastExtAssetUtils Common
#

SET(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/common)

SET(ASSETUTILS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extensions/assetutils/include)
SET(ASSETUTILS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extensions/assetutils/source)

SET(EXT_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extensions/common/source)
SET(EXT_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extensions/common/include)

# Include here after the directories are defined so that the platform specific file can use the variables.
include(${PROJECT_CMAKE_FILES_DIR}/${TARGET_BUILD_PLATFORM}/NvBlastExtAssetUtils.cmake)


SET(COMMON_FILES
	${BLASTEXTASSETUTILS_PLATFORM_COMMON_FILES}
	
	${COMMON_SOURCE_DIR}/NvBlastAssert.cpp
	${COMMON_SOURCE_DIR}/NvBlastAssert.h
	${COMMON_SOURCE_DIR}/NvBlastAtomic.cpp
	${COMMON_SOURCE_DIR}/NvBlastAtomic.h
	${COMMON_SOURCE_DIR}/NvBlastDLink.h
	${COMMON_SOURCE_DIR}/NvBlastFixedArray.h
	${COMMON_SOURCE_DIR}/NvBlastFixedBitmap.h
	${COMMON_SOURCE_DIR}/NvBlastFixedBoolArray.h
	${COMMON_SOURCE_DIR}/NvBlastFixedPriorityQueue.h
	${COMMON_SOURCE_DIR}/NvBlastGeometry.h
	${COMMON_SOURCE_DIR}/NvBlastIndexFns.h
	${COMMON_SOURCE_DIR}/NvBlastIteratorBase.h
	${COMMON_SOURCE_DIR}/NvBlastMath.h
	${COMMON_SOURCE_DIR}/NvBlastMemory.h
	${COMMON_SOURCE_DIR}/NvBlastPreprocessorInternal.h
	${COMMON_SOURCE_DIR}/NvBlastTime.cpp
	${COMMON_SOURCE_DIR}/NvBlastTime.h
	${COMMON_SOURCE_DIR}/NvBlastTimers.cpp
)

SET(ASSETUTILS_SOURCE_FILES
	${ASSETUTILS_SOURCE_DIR}/NvBlastExtAssetUtils.cpp
)

SET(ASSETUTILS_PUBLIC_FILES
	${ASSETUTILS_INCLUDE_DIR}/NvBlastExtAssetUtils.h
)

ADD_LIBRARY(NvBlastExtAssetUtils ${BLASTEXTASSETUTILS_LIB_TYPE} 
	${COMMON_FILES}
	${ASSETUTILS_SOURCE_FILES}
	${ASSETUTILS_PUBLIC_FILES}
)

SOURCE_GROUP("common" FILES ${COMMON_FILES})
SOURCE_GROUP("public" FILES ${ASSETUTILS_PUBLIC_FILES}) 
SOURCE_GROUP("src" FILES ${ASSETUTILS_SOURCE_FILES})

# Target specific compile options

TARGET_INCLUDE_DIRECTORIES(NvBlastExtAssetUtils 
	PUBLIC ${ASSETUTILS_INCLUDE_DIR}

	PRIVATE ${BLASTEXTASSETUTILS_PLATFORM_INCLUDES}

	PRIVATE ${PROJECT_SOURCE_DIR}/common
	PRIVATE ${PROJECT_SOURCE_DIR}/lowlevel/include
	PRIVATE ${PROJECT_SOURCE_DIR}/lowlevel/source

	PRIVATE ${COMMON_SOURCE_DIR}
)

TARGET_COMPILE_DEFINITIONS(NvBlastExtAssetUtils
	PUBLIC CAPNP_LITE=1
	PRIVATE ${BLASTEXTASSETUTILS_COMPILE_DEFS}
)

# Warning disables for Capn Proto
TARGET_COMPILE_OPTIONS(NvBlastExtAssetUtils
	PRIVATE ${BLASTEXTASSETUTILS_COMPILE_OPTIONS}
)

SET_TARGET_PROPERTIES(NvBlastExtAssetUtils PROPERTIES 
	PDB_NAME_DEBUG "NvBlastExtAssetUtils${CMAKE_DEBUG_POSTFIX}"
	PDB_NAME_CHECKED "NvBlastExtAssetUtils${CMAKE_CHECKED_POSTFIX}"
	PDB_NAME_PROFILE "NvBlastExtAssetUtils${CMAKE_PROFILE_POSTFIX}"
	PDB_NAME_RELEASE "NvBlastExtAssetUtils${CMAKE_RELEASE_POSTFIX}"
)

# Do final direct sets after the target has been defined
TARGET_LINK_LIBRARIES(NvBlastExtAssetUtils 
	PRIVATE NvBlast
	PUBLIC NvBlastGlobals
)
