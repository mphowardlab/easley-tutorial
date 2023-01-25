cmake_minimum_required(VERSION 3.19)
project(
    parallelism
    VERSION 0.1.0
    LANGUAGES CXX
    )

# set default build type https://blog.kitware.com/cmake-and-the-default-build-type/
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option(PARALLELISM_MPI "Use MPI." ON)
option(PARALLELISM_OPENMP "Use OpenMP threading." ON)

if(PARALLELISM_MPI)
    find_package(MPI REQUIRED)
endif()
if(PARALLELISM_OPENMP)
    find_package(OpenMP REQUIRED)
endif()

add_subdirectory(src)
