set(TESTCAT_TARGET testcat)

enable_testing()

set(TESTCAT_DIR "${CMAKE_SOURCE_DIR}/test")

include_directories("${CMAKE_SOURCE_DIR}")

set(TESTCAT_SOURCES 

"${TESTCAT_DIR}/testcat.C"

)

set(TESTCAT_TARGET testcat)
add_executable(${TESTCAT_TARGET} ${TESTCAT_SOURCES})
target_link_libraries(${TESTCAT_TARGET} ${LIBS})
add_dependencies(${TESTCAT_TARGET} cat)

add_test(${TESTCAT_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TESTCAT_TARGET})

