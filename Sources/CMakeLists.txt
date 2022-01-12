cmake_minimum_required (VERSION 3.10)

file( GLOB_RECURSE SOURCES "*.*")

set(RESOURCE_PATH ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})

configure_file(LoaderConfiguration.h.in LoaderConfiguration.h @ONLY)

add_library( "AssetLoader" STATIC ${SOURCES})
set_property( TARGET "AssetLoader" PROPERTY FOLDER "" )

target_link_libraries( "AssetLoader" PUBLIC ProjectTemplate)