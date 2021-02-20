add_executable(DS3OptimalFashionManual)

target_link_libraries(DS3OptimalFashionManual PRIVATE DS3OptimalFashionCore)

target_sources(DS3OptimalFashionManual PRIVATE "main.cpp")