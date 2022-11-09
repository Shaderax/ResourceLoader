cmake_minimum_required (VERSION 3.10)

file( GLOB_RECURSE SOURCES "*.cpp")
file( GLOB_RECURSE INCLUDES "*.hpp")

set(RESOURCE_PATH ${CMAKE_SOURCE_DIR}/ CACHE STRING "Resources path")

configure_file(LoaderConfiguration.h.in LoaderConfiguration.h @ONLY)

#add_library( "ResourceLoader" STATIC ${SOURCES} ${INCLUDES})

source_group("Source Files" ${SOURCES})
source_group("Header Files" ${INCLUDES})

set_target_properties("ResourceLoader" PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( "ResourceLoader" INTERFACE ${CMAKE_CURRENT_BINARY_DIR})