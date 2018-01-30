# CMake settings
cmake_minimum_required(VERSION 2.6.3)


#Custom commands
add_custom_target(clean-all
    COMMAND rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake compile_commands.json hackatomb
    )

# Compiler settings
project(hackatomb)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED YES)
set(CXX_EXTENSIONS NO)
set(CMAKE_CXX_FLAGS "-Wall -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-deprecated-declarations -O2")

# System specific flags
if (APPLE)
    add_definitions(-DMAC)
endif (APPLE)

# Source files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs/libpmg/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs/libpmg/bin" "${CMAKE_CURRENT_SOURCE_DIR}/libs")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp")

# Executables
add_executable(hackatomb ${SOURCES})
target_link_libraries(hackatomb pmg)

