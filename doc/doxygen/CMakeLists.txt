project(cat_doc)
cmake_minimum_required(VERSION 2.8)

set(DOC_DIR "${CMAKE_SOURCE_DIR}/doc")
set(CAT_DIR "${CMAKE_SOURCE_DIR}/cat")


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxy.in ${CMAKE_CURRENT_BINARY_DIR}/doxy @ONLY)
add_custom_target(doxy ALL
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxy
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION doc/doxygen)
endif(DOXYGEN_FOUND)

