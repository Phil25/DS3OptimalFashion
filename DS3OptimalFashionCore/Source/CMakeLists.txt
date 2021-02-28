target_sources(DS3OptimalFashionCore
	PRIVATE
		"ArmorFinder.h"
		"ArmorFinder.cpp"
		"ArmorPiece.hpp"
		"ArmorSet.hpp"
		"Database.cpp"
		"Database.h"
		"Utils.hpp"
)

target_include_directories(DS3OptimalFashionCore PUBLIC ${CMAKE_CURRENT_LIST_DIR})