cmake_minimum_required (VERSION 3.10)

file( GLOB_RECURSE SOURCES "*.*")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})

#configure_file(LoaderConfiguration.h.in LoaderConfiguration.h @ONLY)

add_library( "AssetLoader" STATIC ${SOURCES})
set_property( TARGET "AssetLoader" PROPERTY FOLDER "" )

target_link_libraries( "AssetLoader" PUBLIC ProjectTemplate)