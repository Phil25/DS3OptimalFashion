target_sources(DS3OptimalFashion
	PRIVATE
		"AppMain.cpp"
		"AppMain.h"
		"ArmorFinder.cpp"
		"ArmorFinder.h"
		"ArmorPieceCard.cpp"
		"ArmorPieceCard.h"
		"ArmorSetPreviewPanel.cpp"
		"ArmorSetPreviewPanel.h"
		"CurrentParameters.cpp"
		"CurrentParameters.h"
		"FrameMain.cpp"
		"FrameMain.h"
		"GroupPanel.cpp"
		"GroupPanel.h"
		"ParameterChoiceList.cpp"
		"ParameterChoiceList.h"
		"ParameterField.cpp"
		"ParameterField.h"
		"TitlePanel.cpp"
		"TitlePanel.h"
)

target_include_directories(DS3OptimalFashion PRIVATE ${CMAKE_CURRENT_LIST_DIR})