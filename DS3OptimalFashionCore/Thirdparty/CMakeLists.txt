target_sources(DS3OptimalFashionCore
	PRIVATE
		"csv.h"
)

target_include_directories(DS3OptimalFashionCore PRIVATE ${CMAKE_CURRENT_LIST_DIR})

if (UNIX)
	find_package(Threads REQUIRED)
	target_link_libraries(DS3OptimalFashionCore PRIVATE Threads::Threads)
endif (UNIX)
