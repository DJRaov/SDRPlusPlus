cmake_minimum_required(VERSION 3.13)
project(hackrf_source)

if (MSVC)
    set(CMAKE_CXX_FLAGS "-O2 /std:c++17 /EHsc")
else()
    set(CMAKE_CXX_FLAGS "-O3 -std=c++17 -fpermissive")
endif (MSVC)

include_directories("src/")

file(GLOB SRC "src/*.cpp")

add_library(hackrf_source SHARED ${SRC})
target_link_libraries(hackrf_source PRIVATE sdrpp_core)
set_target_properties(hackrf_source PROPERTIES PREFIX "")

if (MSVC)
    # Lib path
    target_link_directories(sdrpp_core PUBLIC "C:/Program Files/PothosSDR/bin/")

    target_link_libraries(hackrf_source PUBLIC hackrf)
else (MSVC)
    find_package(PkgConfig)

    pkg_check_modules(LIBHACKRF REQUIRED libhackrf)

    target_include_directories(hackrf_source PUBLIC ${LIBHACKRF_INCLUDE_DIRS})
    target_link_directories(hackrf_source PUBLIC ${LIBHACKRF_LIBRARY_DIRS})
    target_link_libraries(hackrf_source PUBLIC ${LIBHACKRF_LIBRARIES})
endif (MSVC)