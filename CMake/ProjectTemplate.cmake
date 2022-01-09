add_library( "ProjectTemplate" INTERFACE )

# Debug
if (PRJ_TEMPLATE_CXX_FLAGS_DEBUG)
	target_compile_options( "ProjectTemplate" INTERFACE $<$<CONFIG:Debug>: ${PRJ_TEMPLATE_CXX_FLAGS_DEBUG}> )
endif ()
if (PRJ_TEMPLATE_LINKER_FLAGS_DEBUG)
	set_target_properties( "ProjectTemplate" PROPERTIES INTERFACE_LINK_OPTIONS_DEBUG ${PRJ_TEMPLATE_LINKER_FLAGS_DEBUG} )
endif ()

# Release
if (PRJ_TEMPLATE_CXX_FLAGS_RELEASE)
	target_compile_options( "ProjectTemplate" INTERFACE $<$<CONFIG:Release>: ${PRJ_TEMPLATE_CXX_FLAGS_RELEASE}> )
endif ()
if (PRJ_TEMPLATE_LINKER_FLAGS_RELEASE)
	set_target_properties( "ProjectTemplate" PROPERTIES INTERFACE_LINK_OPTIONS_RELEASE ${PRJ_TEMPLATE_LINKER_FLAGS_RELEASE} )
endif ()

target_compile_features( "ProjectTemplate" INTERFACE cxx_std_20 )