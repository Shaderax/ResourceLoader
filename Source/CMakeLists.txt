cmake_minimum_required(VERSION 3.0)

project(AssetLoader_Source)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})

configure_file(LoaderConfiguration.h.in LoaderConfiguration.h @ONLY)