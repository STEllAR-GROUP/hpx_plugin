# Copyright (c) 2016 Hartmut Kaiser
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Find and include HPX settings
if(NOT HPX_DIR)
  message(FATAL_ERROR "HPX_DIR not set, unable to find HPX!")
endif()

# Require a recent version of cmake
cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

# This project is C++ based.
project(HPXPluginExample)

# This adds the HPX cmake configuration directory to the search path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  ${HPX_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)

# Instruct cmake to find the HPX settings
find_package(HPX)

hpx_include(SetOutputPaths)

include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

# Adjust auxiliary build settings for HPX to work properly
if(NOT MSVC)
  set(HPX_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${HPX_RPATH})
else()
  # enable solution folders for MSVC
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

include_directories(src)

# add executable
add_hpx_executable(load_plugin
    SOURCES src/load_plugin.cpp
    HEADERS src/example_plugin_factory_base.hpp
            src/example_plugin_base.hpp)

# add plugin
set(CMAKE_DEBUG_POSTFIX ${HPX_DEBUG_POSTFIX})
add_hpx_library(loaded_plugin
    PLUGIN
    SOURCES src/plugin/loaded_plugin.cpp
    HEADERS src/plugin/example_plugin_factory.hpp
            src/plugin/example_plugin1.hpp
            src/plugin/example_plugin2.hpp)
