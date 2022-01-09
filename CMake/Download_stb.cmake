# find or download STB

if (${BSC_ENABLE_STB})
	set( BSC_TP_STB_PATH "" CACHE PATH "path to stb source" )
	mark_as_advanced( BSC_TP_STB_PATH )
	
	# reset to default
	if (NOT EXISTS "${BSC_TP_STB_PATH}/stb_image.h" )
		message( STATUS "stb is not found in \"${BSC_TP_STB_PATH}\"" )
		set( BSC_TP_STB_PATH "${BSC_TP_PATH}/stb" CACHE PATH "" FORCE )
	else ()
		message( STATUS "stb found in \"${BSC_TP_STB_PATH}\"" )
	endif ()
	
	# download
	if (NOT EXISTS "${BSC_TP_STB_PATH}/stb_image.h")
		FetchContent_Declare( TP_STB
			GIT_REPOSITORY		"https://github.com/nothings/stb.git"
			GIT_TAG				master
			SOURCE_DIR			"${BSC_TP_STB_PATH}"
		)
		
		FetchContent_GetProperties( TP_STB )
		if (NOT TP_STB_POPULATED)
			message( STATUS "downloading stb..." )
			FetchContent_Populate( TP_STB )
		endif ()
	endif ()

	add_library( "STB-lib" INTERFACE )
	target_include_directories( "STB-lib" INTERFACE "${BSC_TP_STB_PATH}" )
	target_compile_definitions( "STB-lib" INTERFACE "BSC_ENABLE_STB" )
endif ()