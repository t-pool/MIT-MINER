set(SOURCES
    ApiServer.h ApiServer.cpp
	httpServer.cpp httpServer.h
)

hunter_add_package(mongoose)
find_package(mongoose CONFIG REQUIRED)

add_library(apicore ${SOURCES})
target_link_libraries(apicore PRIVATE mitcore devcore mitminer-buildinfo mongoose::mongoose)
target_include_directories(apicore PRIVATE ..)
