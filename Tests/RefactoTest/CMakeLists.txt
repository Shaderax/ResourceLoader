if (TARGET "AssetLoader")
	file( GLOB_RECURSE SOURCES "*.*" )
	add_executable( "Tests.Refacto" ${SOURCES} )
	source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
	set_property( TARGET "Tests.Refacto" PROPERTY FOLDER "Tests" )
	target_link_libraries( "Tests.Refacto" ProjectTemplate)
	
	add_test( NAME "Tests.Refacto" COMMAND "Tests.Refacto" )
endif ()