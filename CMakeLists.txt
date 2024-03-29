cmake_minimum_required (VERSION 3.11...3.19)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(ResourceLoader
		VERSION 0.0.1
		LANGUAGES CXX)

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

message( STATUS "Compiler Id: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER_VERSION})")
message( STATUS "Target system: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})" )
message( STATUS "Host system: ${CMAKE_HOST_SYSTEM_NAME} (${CMAKE_HOST_SYSTEM_VERSION})" )

set( AL_TP_USE_STABLE_VERSIONS ON CACHE BOOL "use last stable version instead of master branch" )

set( AL_ENABLE_TESTS ON CACHE BOOL "Enable tests" )
set( AL_ENABLE_STB ON CACHE BOOL "Use stb lib (optional, required for tests" )

include("CMake/CompilersOptions.cmake")

add_subdirectory(Sources)
target_include_directories( "ResourceLoader" INTERFACE "Sources" )
#add_subdirectory(ThirdParty)

if (${AL_ENABLE_TESTS})
	message("Test Enabled")
	enable_testing()

	add_subdirectory( "Tests/Dummy" )
	add_subdirectory( "Tests/RefactoTest" )
endif ()


message("CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")
message("CMAKE_SOURCE_DIR : " ${CMAKE_SOURCE_DIR})
message("CMAKE_CURRENT_BINARY_DIR : ${CMAKE_CURRENT_BINARY_DIR}")
