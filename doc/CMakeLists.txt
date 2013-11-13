project(cat_doc)
cmake_minimum_required(VERSION 2.8)

add_subdirectory("guides")
add_subdirectory("doxygen")

add_custom_target(doc)
add_dependencies(doc guides doxygen)

