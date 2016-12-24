include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/deps/linenoise)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

add_executable(test_sds
  test_sds.c
  )

add_executable(test_adlist
  test_adlist.c
  )

target_link_libraries(test_adlist
  redis
  )

add_executable(test_dict
  test_dict.c
  )

target_link_libraries(test_dict
  redis
  )

add_executable(test_linenoise
  test_linenoise.c
  )

target_link_libraries(test_linenoise
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/liblinenoise.a
  )