set(LIB_TARGET cat)

set(CAT_DIR "${CMAKE_SOURCE_DIR}/cat")

include_directories("${CAT_DIR}")
include_directories("${CAT_DIR}/random")
include_directories("${CAT_DIR}/array")
include_directories("${CAT_DIR}/traits")
include_directories("${CAT_DIR}/tiny") 

set(CAT_SOURCES 

"${CAT_DIR}/random/random.C"

)

set(CAT_HEADERS

"${CAT_DIR}/cat.h"
"${CAT_DIR}/funcstructs.h"
"${CAT_DIR}/globals.h"
"${CAT_DIR}/opstructs.h"

)

set(RANDOM_HEADERS

"${CAT_DIR}/random/random.h"

)

set(ARRAY_HEADERS

"${CAT_DIR}/array/arrayclass.h"
"${CAT_DIR}/array/array_expression.h"
"${CAT_DIR}/array/array_funcs.h"
"${CAT_DIR}/array/array.h"
"${CAT_DIR}/array/array_iterator.h"
"${CAT_DIR}/array/array_macros.h"
"${CAT_DIR}/array/array_ops.h"
"${CAT_DIR}/array/memory_block.h"
"${CAT_DIR}/array/memory_reference.h"
"${CAT_DIR}/array/range.h"
"${CAT_DIR}/array/storage.h"

)

set(TINY_HEADERS

"${CAT_DIR}/tiny/tiny.h"
"${CAT_DIR}/tiny/tvector_expression.h"
"${CAT_DIR}/tiny/tvector_funcs.h"
"${CAT_DIR}/tiny/tvector.h"
"${CAT_DIR}/tiny/tvector_ops.h"

)

set(TRAITS_HEADERS

"${CAT_DIR}/traits/multi.h"
"${CAT_DIR}/traits/numeric.h"
"${CAT_DIR}/traits/promote.h"
"${CAT_DIR}/traits/traits.h"

)

set(ARRAY_TEMPLATE_IMPLEMENTATIONS

"${CAT_DIR}/array/arrayclass.C"
"${CAT_DIR}/array/array_funcs.C"
"${CAT_DIR}/array/array_iterator.C"
"${CAT_DIR}/array/memory_block.C"
"${CAT_DIR}/array/memory_reference.C"
"${CAT_DIR}/array/storage.C"

)

set(TINY_TEMPLATE_IMPLEMENTATIONS

"${CAT_DIR}/tiny/tvector_funcs.C"
"${CAT_DIR}/tiny/tvector.C"

)

add_library(${LIB_TARGET} SHARED ${CAT_SOURCES})
target_include_directories(${LIB_TARGET}
  PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CAT_DIR}>"
    # Headers used from installed location:
    "$<INSTALL_INTERFACE:include/cat>"     
)

install (TARGETS ${LIB_TARGET} DESTINATION lib)
install (FILES ${CAT_HEADERS} DESTINATION include/${LIB_TARGET})
install (FILES ${RANDOM_HEADERS} DESTINATION include/${LIB_TARGET}/random)
install (FILES ${ARRAY_HEADERS} DESTINATION include/${LIB_TARGET}/array)
install (FILES ${TINY_HEADERS} DESTINATION include/${LIB_TARGET}/tiny)
install (FILES ${TRAITS_HEADERS} DESTINATION include/${LIB_TARGET}/traits)
install (FILES ${ARRAY_TEMPLATE_IMPLEMENTATIONS} DESTINATION include/${LIB_TARGET}/array)
install (FILES ${TINY_TEMPLATE_IMPLEMENTATIONS} DESTINATION include/${LIB_TARGET}/tiny)

