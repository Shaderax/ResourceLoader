if (TARGET "ResourceLoader")
	file( GLOB_RECURSE SOURCES "*.*" )
	add_executable( "Tests.Dummy" ${SOURCES} )
	source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
	set_property( TARGET "Tests.Dummy" PROPERTY FOLDER "Tests" )
	target_link_libraries( "Tests.Dummy" "ResourceLoader" )
	
	add_test( NAME "Tests.Dummy" COMMAND "Tests.Dummy" )
endif ()