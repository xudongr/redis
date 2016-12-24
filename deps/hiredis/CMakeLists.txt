#set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
add_library(hiredis
  hiredis.c
  net.c
  dict.c
  net.c
  sds.c
  async.c
  )