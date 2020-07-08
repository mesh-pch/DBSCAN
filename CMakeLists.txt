cmake_minimum_required(VERSION 2.8.3)
project(ANN)

option(BUILD_SAMPLE "option for build sample" OFF)
option(BUILD_TEST "option for build test" OFF)
option(BUILD_ANN2FIG "option for build ann to fig" OFF)
option(BUILD_DBSCAN_SAMPLE "option for build dbsan sample" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -O3 -g")

include_directories(
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    )

file(GLOB SOUREC "src/*.cpp")
add_library(ANN SHARED ${SOUREC} )

if(${BUILD_SAMPLE})
    set(SAMPLE "sample/ann_sample.cpp")
    add_executable(sample ${SAMPLE})
    target_link_libraries(sample ANN)
endif()

if(${BUILD_TEST})
    file(GLOB TEST_SRC "test/*.cpp")
    add_executable(ann_test ${TEST_SRC})
    target_link_libraries(ann_test ANN)
endif()

if(${BUILD_ANN2FIG})
    file(GLOB ANN2FIG_SRC "ann2fig/*.cpp")
    add_executable(ann2fig ${ANN2FIG_SRC})
    target_link_libraries(ann2fig ANN)

endif()

if(${BUILD_DBSCAN_SAMPLE})
    set(DBSCAN_SRC "sample/dbscan_sample.cpp")
    add_executable(dbscan ${DBSCAN_SRC})
    target_link_libraries(dbscan ANN)
endif()



