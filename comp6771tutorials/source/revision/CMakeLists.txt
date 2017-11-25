find_package(Threads)

add_executable(rev_vector vector.cpp)
add_executable(rev_oo oo.cpp)
add_executable(rev_threads threads.cpp) 
target_link_libraries(rev_threads ${CMAKE_THREAD_LIBS_INIT})
