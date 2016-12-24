set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(hiredis)
#add_subdirectory(jemalloc)
add_subdirectory(linenoise)
add_subdirectory(lua)