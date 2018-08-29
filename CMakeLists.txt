cmake_minimum_required(VERSION 3.5)

include(cmake/cable/bootstrap.cmake)

include(CableBuildInfo)
include(CableBuildType)
include(CableToolchains)
include(HunterGate)

include(defaults/HunterCacheServers)

cable_configure_toolchain(DEFAULT cxx11)

set(HUNTER_CONFIGURATION_TYPES Release CACHE STRING "Build type of Hunter packages")
set(HUNTER_JOBS_NUMBER 6 CACHE STRING "Number of parallel builds used by Hunter")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.6.tar.gz"
    SHA1 "951e8daf57a51708b0e6a00cab342a042db57a2f"
    LOCAL
)

project(mitminer)
set(PROJECT_VERSION 0.16.0.dev2)

cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Release RelWithDebInfo)

option(MITASHCL "Build with OpenCL mining" ON)
option(MITASHCUDA "Build with CUDA mining" ON)
option(MITDBUS "Build with D-Bus support" OFF)
option(APICORE "Build with API Server support" ON)
option(BINKERN "Install AMD binary kernels" ON)

# propagates CMake configuration options to the compiler
function(configureProject)
	if (MITASHCL)
		add_definitions(-DMIT_MITASHCL)
	endif()
	if (MITASHCUDA)
		add_definitions(-DMIT_MITASHCUDA)
	endif()
	if (MITDBUS)
		add_definitions(-DMIT_DBUS)
	endif()
	if (APICORE)
		add_definitions(-DAPI_CORE)
	endif()
	if (BINKERN)
		add_definitions(-DBIN_KERN)
	endif()
endfunction()

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

hunter_add_package(libjson-rpc-cpp)
find_package(libjson-rpc-cpp CONFIG REQUIRED)

hunter_add_package(CppNetlibUri)
find_package(CppNetlibUri CONFIG REQUIRED)

hunter_add_package(ethash)
find_package(ethash CONFIG REQUIRED)

configureProject()

message("------------------------------------------------------------------------")
message("-- CMake ${CMAKE_VERSION}")
message("-- Build ${CMAKE_BUILD_TYPE} / ${CMAKE_SYSTEM_NAME}")
message("------------------------------------------------------------- components")
message("-- MITASHCL         Build OpenCL components                  ${MITASHCL}")
message("-- MITASHCUDA       Build CUDA components                    ${MITASHCUDA}")
message("-- MITDBUS          Build D-Bus components                   ${MITDBUS}")
message("-- APICORE          Build API Server components              ${APICORE}")
message("-- BINKERN          Install AMD binary kernels               ${BINKERN}")
message("------------------------------------------------------------------------")
message("")

include(MitCompilerSettings)
if(UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()


cable_add_buildinfo_library(PROJECT_NAME ${PROJECT_NAME})

add_subdirectory(libdevcore)
add_subdirectory(libmitcore)
add_subdirectory(libhwmon)
add_subdirectory(libpoolprotocols)

if (MITASHCL)
	add_subdirectory(libmitash-cl)
	if (BINKERN)
		add_subdirectory(libmitash-cl/kernels)
	endif()
endif ()
if (MITASHCUDA)
	add_subdirectory(libmitash-cuda)
endif ()
if (APICORE)
	add_subdirectory(libapicore)
endif()

add_subdirectory(mitminer)


if(WIN32)
	set(CPACK_GENERATOR ZIP)
else()
	set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)
