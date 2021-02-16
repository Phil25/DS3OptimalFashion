target_sources(OptimalFashionCore
	PRIVATE
		"Parser.cpp"
		"ArmorFinder.hpp"
		"ArmorFinder.cpp"
		"ArmorPiece.hpp"
		"ArmorSet.hpp"
		"Parser.hpp"
		"Utils.hpp"
)

target_include_directories(OptimalFashionCore PUBLIC ${CMAKE_CURRENT_LIST_DIR})