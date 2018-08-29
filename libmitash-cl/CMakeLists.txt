# A custom command and target to turn the OpenCL kernel into a byte array header
# The normal build depends on it properly and if the kernel file is changed, then
# a rebuild of libmitash-cl should be triggered

#TODO: clean up the copy&pasting here
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mitash.h
	COMMAND ${CMAKE_COMMAND} ARGS
	-DBIN2H_SOURCE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/kernels/cl/mitash.cl"
	-DBIN2H_VARIABLE_NAME=mitash_cl
	-DBIN2H_HEADER_FILE="${CMAKE_CURRENT_BINARY_DIR}/mitash.h"
	-P "${CMAKE_CURRENT_SOURCE_DIR}/bin2h.cmake"
	COMMENT "Generating OpenCL Kernel Byte Array"
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cl/mitash.cl
)
add_custom_target(clbin2h_stable DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mitash.h ${CMAKE_CURRENT_SOURCE_DIR}/cl/mitash.cl)

set(SOURCES
	CLMiner.h CLMiner.cpp
	${CMAKE_CURRENT_BINARY_DIR}/mitash.h
)

if(APPLE)
	# On macOS use system OpenCL library.
	find_package(OpenCL REQUIRED)
else()
	hunter_add_package(OpenCL)
	find_package(OpenCL CONFIG REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(..)

add_library(mitash-cl ${SOURCES})
target_link_libraries(mitash-cl PUBLIC mitcore mitash::mitash)
target_link_libraries(mitash-cl PRIVATE OpenCL::OpenCL)
target_link_libraries(mitash-cl PRIVATE Boost::filesystem)
