if (WIN32)
	add_executable(DS3OptimalFashion WIN32)
else ()
	add_executable(DS3OptimalFashion)
endif (WIN32)

target_link_libraries(DS3OptimalFashion PRIVATE DS3OptimalFashionCore CONAN_PKG::wxwidgets)

add_subdirectory("Source")