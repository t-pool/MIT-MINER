set(SOURCES
	BlockHeader.h BlockHeader.cpp
	MitashAux.h MitashAux.cpp
	Exceptions.h
	Farm.h
	Miner.h Miner.cpp
)

include_directories(BEFORE ..)

add_library(mitcore ${SOURCES})
target_link_libraries(mitcore PUBLIC devcore mitash::mitash PRIVATE hwmon)

if(MITASHCL)
	target_link_libraries(mitcore PRIVATE mitash-cl)
endif()
if(MITASHCUDA)
	target_link_libraries(mitcore PUBLIC mitash-cuda)
endif()
