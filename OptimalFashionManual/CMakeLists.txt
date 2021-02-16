add_executable(OptimalFashionManual)

target_link_libraries(OptimalFashionManual PRIVATE OptimalFashionCore)

target_sources(OptimalFashionManual PRIVATE "main.cpp")