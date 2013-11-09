project(cat)
cmake_minimum_required(VERSION 2.8)

set(TESTCAT_DIR "${CMAKE_SOURCE_DIR}/test")

include_directories("${CMAKE_SOURCE_DIR}")

set(TESTCAT_SOURCES 

"${TESTCAT_DIR}/testcat.C"

)

set(TESTCAT_TARGET testcat)
add_executable(${TESTCAT_TARGET} ${TESTCAT_SOURCES})

install (TARGETS ${TESTCAT_TARGET} DESTINATION bin)

