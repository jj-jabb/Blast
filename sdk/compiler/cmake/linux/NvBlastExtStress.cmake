#
# Build NvBlast Linux
#

SET(BLASTTK_LIBTYPE SHARED)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	SET(BLASTEXTSTRESS_PLATFORM_COMPILE_OPTIONS "-Wno-return-type-c-linkage" "-pedantic")
ELSE()
	SET(BLASTEXTSTRESS_PLATFORM_COMPILE_OPTIONS "-pedantic")
ENDIF()
