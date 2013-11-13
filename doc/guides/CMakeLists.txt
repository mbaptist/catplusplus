project(cat_doc)
cmake_minimum_required(VERSION 2.8)

set(DOC_DIR "${CMAKE_SOURCE_DIR}/doc")
set(GUIDES_DIR "${DOC_DIR}/guides")

#Function for pdf generation

# Generate Guides
find_package(Lyx)
#if (LYX_FOUND)

set(LYX_EXECUTABLE "/usr/bin/lyx")  

function(add_lyx2pdf_target DIR_REL MAIN_FILE EXTRA_SOURCES)
	set(SRC_DIR "${CMAKE_SOURCE_DIR}/${DIR_REL}")  
	set(WORK_DIR "${CMAKE_BINARY_DIR}/${DIR_REL}")
	set(LYX_INPUT "${MAIN_FILE}.lyx")
	set(PDF_OUTPUT "${MAIN_FILE}.pdf")
	foreach(SRC_FILE ${EXTRA_SOURCES})
		configure_file(${SRC_DIR}/${SRC_FILE} ${WORK_DIR}/${SRC_FILE} @ONLY)
	endforeach(SRC_FILE)
	configure_file(${SRC_DIR}/${LYX_INPUT} ${WORK_DIR}/${LYX_INPUT} @ONLY)
	add_custom_target("build_${MAIN_FILE}" ALL
		COMMAND ${LYX_EXECUTABLE} -e pdf2 "${WORK_DIR}/${LYX_INPUT}"
		WORKING_DIRECTORY ${WORK_DIR}
	COMMENT "Generating Guide ${MAIN_FILE}.pdf" VERBATIM
	)
	install(FILES ${WORK_DIR}/${PDF_OUTPUT} DESTINATION ${DIR_REL})
endfunction(add_pdf_target)

add_lyx2pdf_target("doc/guides" "cat_quickref" "") 
add_lyx2pdf_target("doc/guides" "cat_user_guide" "")


#endif(LYX_FOUND)


