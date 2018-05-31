#
# Build BlastPerfTests PS4
#

SET(BLASTPERFTESTS_PLATFORM_COMMON_FILES
)

SET(BLASTPERFTESTS_PLATFORM_INCLUDES
)

SET(BLASTPERFTESTS_COMPILE_DEFS
	# Common to all configurations
	${BLASTTESTS_SLN_COMPILE_DEFS}
	
	$<$<CONFIG:debug>:${BLASTTESTS_SLN_DEBUG_COMPILE_DEFS}>
	$<$<CONFIG:checked>:${BLASTTESTS_SLN_CHECKED_COMPILE_DEFS}>
	$<$<CONFIG:profile>:${BLASTTESTS_SLN_PROFILE_COMPILE_DEFS}>
	$<$<CONFIG:release>:${BLASTTESTS_SLN_RELEASE_COMPILE_DEFS}>
)

SET(BLASTPERFTESTS_PLATFORM_LINKED_LIBS
    -lpthread
    -lm
)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	#Required to link against the Google Test binaries in pacman
	SET(BLASTPERFTESTS_PLATFORM_COMPILE_OPTIONS "-D_GLIBCXX_USE_CXX11_ABI=0")
ENDIF()