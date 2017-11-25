add_executable(12.1.1 11multiple.cpp)
add_executable(12.1.2 12graph.cpp)
set_source_files_properties(cpp17.cpp PROPERTIES COMPILE_FLAGS "-std=c++17")
add_executable(cpp17 cpp17.cpp)
