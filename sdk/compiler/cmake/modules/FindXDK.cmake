# - Try to find XDLK
# - Sets XDK_LIBRARIES - list of the libraries found
# - Sets XDK_INCLUDE_DIRS 

include(FindPackageHandleStandardArgs)

# Find the includes

# TODO: Do the version stuff properly!
# TODO: Handle a binary dep version of the XDK
find_path(XDK_PATH include/winrt/Windows.Xbox.UI.h
	PATHS 
	$ENV{XboxOneXDKLatest}/xdk
)

SET(LIB_PATH ${XDK_PATH}/Lib/amd64/)
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

MESSAGE("XDK LIB PATH: ${LIB_PATH}")

find_library(ACPHAL_LIB
	NAMES acphal
	PATHS ${LIB_PATH}
)

find_library(APPMODEL_LIB
	NAMES appmodel
	PATHS ${LIB_PATH}
)

find_library(BCRYPT_LIB
	NAMES bcrypt
	PATHS ${LIB_PATH}
)

find_library(COMBASE_LIB
	NAMES combase
	PATHS ${LIB_PATH}
)

find_library(CONSOLEID_LIB
	NAMES consoleid
	PATHS ${LIB_PATH}
)

find_library(D3D11_X_LIB
	NAMES d3d11_x
	PATHS ${LIB_PATH}
)

find_library(D3D12_X_LIB
	NAMES d3d12_x
	PATHS ${LIB_PATH}
)

find_library(D3DCOMPILER_LIB
	NAMES d3dcompiler
	PATHS ${LIB_PATH}
)

find_library(DXGUID_LIB
	NAMES dxguid
	PATHS ${LIB_PATH}
)

find_library(ETWPLUS_LIB
	NAMES etwplus
	PATHS ${LIB_PATH}
)

find_library(IXMLHTTPREQUEST2_LIB
	NAMES ixmlhttprequest2
	PATHS ${LIB_PATH}
)

find_library(KERNELX_LIB
	NAMES kernelx
	PATHS ${LIB_PATH}
)

find_library(KSTUDIOCLIENT_LIB
	NAMES kstudioclient
	PATHS ${LIB_PATH}
)

find_library(MFPLAT_LIB
	NAMES mfplat
	PATHS ${LIB_PATH}
)

find_library(MFREADWRITE_LIB
	NAMES mfreadwrite
	PATHS ${LIB_PATH}
)

find_library(MFUUID_LIB
	NAMES mfuuid
	PATHS ${LIB_PATH}
)

find_library(MMDEVAPI_LIB
	NAMES mmdevapi
	PATHS ${LIB_PATH}
)

find_library(PIXEVT_LIB
	NAMES PIXEvt
	PATHS ${LIB_PATH}
)

find_library(RPCRT4_LIB
	NAMES rpcrt4
	PATHS ${LIB_PATH}
)

find_library(SMARTGLASSINTEROP_LIB
	NAMES smartglassinterop
	PATHS ${LIB_PATH}
)

find_library(STRMIIDS_LIB
	NAMES strmiids
	PATHS ${LIB_PATH}
)

find_library(TOOLHELPX_LIB
	NAMES toolhelpx
	PATHS ${LIB_PATH}
)

find_library(UUID_LIB
	NAMES uuid
	PATHS ${LIB_PATH}
)

find_library(WINDOWSCODECS_LIB
	NAMES windowscodecs
	PATHS ${LIB_PATH}
)

find_library(WMCODECDSPUUID_LIB
	NAMES wmcodecdspuuid
	PATHS ${LIB_PATH}
)

find_library(WS2_32_LIB
	NAMES ws2_32
	PATHS ${LIB_PATH}
)

find_library(XAPOBASE_LIB
	NAMES xapobase
	PATHS ${LIB_PATH}
)

find_library(XAUDIO2_LIB
	NAMES xaudio2
	PATHS ${LIB_PATH}
)

find_library(XG_X_LIB
	NAMES xg_x
	PATHS ${LIB_PATH}
)

find_library(XI_LIB
	NAMES xi
	PATHS ${LIB_PATH}
)

find_library(XSTUDIOCLIENT_LIB
	NAMES xstudioclient
	PATHS ${LIB_PATH}
)



FIND_PACKAGE_HANDLE_STANDARD_ARGS(XDK
	DEFAULT_MSG
	XDK_PATH

	ACPHAL_LIB
	APPMODEL_LIB
	BCRYPT_LIB
	COMBASE_LIB
	CONSOLEID_LIB
	D3D11_X_LIB
	D3D12_X_LIB
	D3DCOMPILER_LIB
	DXGUID_LIB
	ETWPLUS_LIB
	IXMLHTTPREQUEST2_LIB
	KERNELX_LIB
	KSTUDIOCLIENT_LIB
	MFPLAT_LIB
	MFREADWRITE_LIB
	MFUUID_LIB
	MMDEVAPI_LIB
	PIXEVT_LIB
	RPCRT4_LIB
	SMARTGLASSINTEROP_LIB
	STRMIIDS_LIB
	TOOLHELPX_LIB
	UUID_LIB
	WINDOWSCODECS_LIB
	WMCODECDSPUUID_LIB
	WS2_32_LIB
	XAPOBASE_LIB
	XAUDIO2_LIB
	XG_X_LIB
	XI_LIB
	XSTUDIOCLIENT_LIB
)

if (XDK_FOUND)
	SET(XDK_INCLUDE_DIRS 
		${XDK_PATH}/Include 
		${XDK_PATH}/Include/shared
		${XDK_PATH}/Include/um
		${XDK_PATH}/Include/winrt
	)
	
	SET(XDK_LIBRARIES 
		${ACPHAL_LIB}
		${APPMODEL_LIB}
		${BCRYPT_LIB}
		${COMBASE_LIB}
		${CONSOLEID_LIB}
		${D3D11_X_LIB}
		${D3D12_X_LIB}
		${D3DCOMPILER_LIB}
		${DXGUID_LIB}
		${ETWPLUS_LIB}
		${IXMLHTTPREQUEST2_LIB}
		${KERNELX_LIB}
		${KSTUDIOCLIENT_LIB}
		${MFPLAT_LIB}
		${MFREADWRITE_LIB}
		${MFUUID_LIB}
		${MMDEVAPI_LIB}
		${PIXEVT_LIB}
		${RPCRT4_LIB}
		${SMARTGLASSINTEROP_LIB}
		${STRMIIDS_LIB}
		${TOOLHELPX_LIB}
		${UUID_LIB}
		${WINDOWSCODECS_LIB}
		${WMCODECDSPUUID_LIB}
		${WS2_32_LIB}
		${XAPOBASE_LIB}
		${XAUDIO2_LIB}
		${XG_X_LIB}
		${XI_LIB}
		${XSTUDIOCLIENT_LIB}
	)
endif()
