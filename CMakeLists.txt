# One project structure to rule them all
#
# Copyright Christopher Di Bella 2017 -- Present
#
#  Use, modification and distribution is subject to the
#  Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
# Project home: https://github.com/appliedmoderncpp/cppcon-stdlib.git
#
# "Adapted" from cmcstl2's top-level CMakeLists.txt
#

set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.9")

project(tutorials CXX)

enable_testing()
include(CTest)
include(FindUnixCommands)


set( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")


# if ("${SANITIZE}" STREQUAL "")
#    set(SANITIZE "-fsanitize=undefined")
# endif()
#
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ftemplate-backtrace-limit=0 -fmax-errors=10")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Werror -march=native")
#
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-inline -g3 -fstack-protector-all")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${SANITIZE}")
#
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g0 -DNDEBUG")
# set(CMAKE_CXX_FLAGS_MIN_SIZEREL "${CMAKE_CXX_FLAGS_MIN_SIZEREL} -Os -g0 -DNDEBUG")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "{CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g3 -DNDEBUG ${SANITIZE}")

# include_directories(include)

# add_subdirectory(lecture)
add_subdirectory(asst1)
add_subdirectory(asst3)
# add_subdirectory(test)
