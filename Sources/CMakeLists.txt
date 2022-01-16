cmake_minimum_required (VERSION 3.10)

file( GLOB_RECURSE SOURCES "*.*")

set(RESOURCE_PATH ${CMAKE_SOURCE_DIR}/)

configure_file(LoaderConfiguration.h.in LoaderConfiguration.h @ONLY)

add_library( "ResourceLoader" STATIC ${SOURCES})
set_property( TARGET "ResourceLoader" PROPERTY FOLDER "" )

set_target_properties("ResourceLoader" PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( "ResourceLoader" PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries( "ResourceLoader" PUBLIC ProjectTemplate)