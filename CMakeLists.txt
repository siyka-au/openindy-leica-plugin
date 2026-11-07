cmake_minimum_required(VERSION 3.16)

project(OpenIndyLeicaPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)

# --- Core dependency ---

include(FetchContent)

set(OI_CORE_LOCAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../openindy-core" CACHE PATH
    "Local OpenIndy-Core checkout to build against instead of fetching from git")

if(EXISTS "${OI_CORE_LOCAL_DIR}/CMakeLists.txt")
    FetchContent_Declare(OpenIndyCore SOURCE_DIR "${OI_CORE_LOCAL_DIR}")
else()
    FetchContent_Declare(OpenIndyCore
        GIT_REPOSITORY git@github.com:siyka-au/openindy-core.git
        GIT_TAG        master
    )
endif()
FetchContent_MakeAvailable(OpenIndyCore)

# OpenIndyCore publishes this from include/plugin/pluginabi.h. A core too old
# to define it cannot be checked for ABI compatibility at all, so fail loudly
# here rather than shipping a plugin whose metadata claims nothing.
if(NOT DEFINED OI_PLUGIN_ABI_VERSION OR OI_PLUGIN_ABI_VERSION STREQUAL "")
    message(FATAL_ERROR
        "OpenIndyCore did not publish OI_PLUGIN_ABI_VERSION. "
        "Update openindy-core to a revision that declares it in include/plugin/pluginabi.h.")
endif()

set(OI_APP_LOCAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../openindy" CACHE PATH
    "Local OpenIndy app checkout to auto-deploy this plugin into after each build")

# --- plugin metadata ---
# mirrors the compiler/OS strings OiMetaData::getCompiler()/getOperatingSys()
# (openindy/controller/oimetadata.cpp) report, since PluginCopier::checkPluginMetaData
# compares them literally against this file's contents at import time

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(OI_PLUGIN_COMPILER "clang 64bit")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(OI_PLUGIN_COMPILER "minGW")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(OI_PLUGIN_COMPILER "MVSC 64bit")
else()
    set(OI_PLUGIN_COMPILER "")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OI_PLUGIN_OS "linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OI_PLUGIN_OS "windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OI_PLUGIN_OS "mac os")
else()
    set(OI_PLUGIN_OS "")
endif()

set(COMPILER "${OI_PLUGIN_COMPILER}")
set(OS "${OI_PLUGIN_OS}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/metaInfo.json.in"
    "${CMAKE_CURRENT_BINARY_DIR}/metaInfo.json"
    @ONLY
)

# The metadata is compiled into the library as a string and handed out by the
# oi_plugin_metadata_json() entry point (OI_DECLARE_PLUGIN_WITH_METADATA), so
# the host can read it once the library is loaded.
file(READ "${CMAKE_CURRENT_BINARY_DIR}/metaInfo.json" OI_PLUGIN_METADATA_JSON)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/metaInfo.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/metaInfo.h"
    @ONLY
)

# --- plugin library ---

add_library(OpenIndyLeicaPlugin SHARED
    sensors/tachymeter/LeicaGeoCom/p_leicatachymeter.cpp
    p_factory.cpp

    sensors/tachymeter/LeicaGeoCom/p_leicatachymeter.h
    p_factory.h
)

set_target_properties(OpenIndyLeicaPlugin PROPERTIES
    OUTPUT_NAME p_leicaPlugin
    PREFIX "lib"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(OpenIndyLeicaPlugin PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(OpenIndyLeicaPlugin
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/generated
        ${CMAKE_CURRENT_SOURCE_DIR}
        sensors/tachymeter/LeicaGeoCom
)

target_link_libraries(OpenIndyLeicaPlugin
    PRIVATE
        Qt6::Core
        Qt6::SerialPort
        OpenIndyCore
)

# --- deploy into a sibling openIndy app build, and tests ---
# Both only make sense when this repo is the top-level build - see
# openindy-default-plugin/CMakeLists.txt for why.

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

add_custom_command(TARGET OpenIndyLeicaPlugin POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DPLUGIN_SO=$<TARGET_FILE:OpenIndyLeicaPlugin>
        -DAPP_DIR=${OI_APP_LOCAL_DIR}/build/bin
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DeployToApp.cmake
    VERBATIM
)

# --- tests ---

enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(tst_loadplugin test/loadplugin/tst_loadplugin.cpp)
target_link_libraries(tst_loadplugin PRIVATE Qt6::Test OpenIndyCore)
target_compile_definitions(tst_loadplugin PRIVATE
    PLUGIN_PATH="$<TARGET_FILE:OpenIndyLeicaPlugin>")
add_test(NAME loadplugin COMMAND tst_loadplugin)
add_dependencies(tst_loadplugin OpenIndyLeicaPlugin)

endif()
