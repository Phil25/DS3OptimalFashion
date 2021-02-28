if (WIN32)
	add_executable(DS3OptimalFashion WIN32)
else ()
	add_executable(DS3OptimalFashion)
endif (WIN32)

set(REG_FILE ".*\.(c[pp]?|h[pp]?)")
source_group("Source" REGULAR_EXPRESSION "${REG_FILE}")
source_group("Source\\Frames" REGULAR_EXPRESSION "Frames/${REG_FILE}")
source_group("Source\\Panels" REGULAR_EXPRESSION "Panels/${REG_FILE}")
source_group("Source\\Panels\\Details" REGULAR_EXPRESSION "Details/${REG_FILE}")
source_group("Source\\Utils" REGULAR_EXPRESSION "Utils/${REG_FILE}")

target_link_libraries(DS3OptimalFashion PRIVATE DS3OptimalFashionCore CONAN_PKG::wxwidgets)

add_subdirectory("Source")