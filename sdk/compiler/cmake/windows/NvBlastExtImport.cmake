#
# Build NvBlastExt Windows
#

SET(BLASTEXT_PLATFORM_COMMON_FILES
	${COMMON_SOURCE_DIR}/NvBlastIncludeWindows.h
)

SET(BLASTEXT_PLATFORM_INCLUDES
)

SET(BLASTEXT_COMPILE_DEFS
	# Common to all configurations
	${BLAST_SLN_COMPILE_DEFS};_CONSOLE;
	
	$<$<CONFIG:debug>:${BLAST_SLN_DEBUG_COMPILE_DEFS}>
	$<$<CONFIG:checked>:${BLAST_SLN_CHECKED_COMPILE_DEFS}>
	$<$<CONFIG:profile>:${BLAST_SLN_PROFILE_COMPILE_DEFS}>
	$<$<CONFIG:release>:${BLAST_SLN_RELEASE_COMPILE_DEFS}>
)

SET(BLAST_EXT_SHARED_LIB_TYPE SHARED)

SET(BLASTEXT_PLATFORM_COMPILE_OPTIONS "/wd4100;/wd4239;/wd4244;/wd4245;/wd4267;/EHsc")
