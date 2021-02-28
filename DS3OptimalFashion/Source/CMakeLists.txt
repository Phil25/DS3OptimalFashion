target_sources(DS3OptimalFashion
	PRIVATE
		"AppMain.cpp"
		"AppMain.h"
)

target_include_directories(DS3OptimalFashion PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory("Frames")
add_subdirectory("Panels")
add_subdirectory("Utils")