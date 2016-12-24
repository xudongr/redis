set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

include_directories(${PROJECT_SOURCE_DIR}/deps/hiredis)
include_directories(${PROJECT_SOURCE_DIR}/deps/linenoise)
include_directories(${PROJECT_SOURCE_DIR}/deps/lua/src)

set(SOURCE_FILES
  sds.c
  adlist.c
  zmalloc.c
  dict.c
  ae.c
  ae_epoll.c
# ae_evport.c
# ae_kqueue.c
# ae_select.c
  anet.c
  aof.c
  asciilogo.h
  bio.c
  bitops.c
  db.c
  config.c
  crc64.c
  db.c
  debug.c
  endianconv.c
  intset.c
  lzf_c.c
  lzf_d.c
  memtest.c
  migrate.c
  multi.c
  networking.c
  object.c
  pqsort.c
  pubsub.c
  rand.c
  rdb.c
# redis-benchmark.c
  redis-check-aof.c
  redis-check-dump.c
  release.c
  replication.c
  rio.c
  scripting.c
  sentinel.c
  sha1.c
  slowlog.c
  sort.c
  syncio.c
  t_hash.c
  t_list.c
  t_set.c
  t_string.c
  t_zset.c
  util.c
  ziplist.c
  zipmap.c
  )

add_library(redis
  ${SOURCE_FILES}
  )

target_link_libraries(redis
  pthread
  m
  )

add_executable(redis_server
  redis.c
  )

add_executable(redis_client
  redis-cli.c
  )

target_link_libraries(redis_server
  redis
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/liblinenoise.a
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/libhiredis.a
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/liblua.a
  )

target_link_libraries(redis_client
  redis
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/liblinenoise.a
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/libhiredis.a
  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/liblua.a
  )