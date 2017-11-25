find_package(Threads)

add_executable(10.1.1 11producerconsumer.cpp)
target_link_libraries(10.1.1 ${CMAKE_THREAD_LIBS_INIT})
add_executable(10.1.2 12futuressketch.cpp)
target_link_libraries(10.1.2 ${CMAKE_THREAD_LIBS_INIT})
add_executable(10.1.3 13futuresexception.cpp)
target_link_libraries(10.1.3 ${CMAKE_THREAD_LIBS_INIT})

set_source_files_properties(21inheritance.cpp PROPERTIES COMPILE_FLAGS "-Wno-unused-variable -Wno-unused-parameter")
add_executable(10.2.1 21inheritance.cpp)
add_executable(10.2.2 22shapes.cpp)
