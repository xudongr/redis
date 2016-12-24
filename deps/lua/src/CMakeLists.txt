
set(LUA_SOURCES
  lapi.c
  ldo.c
  llex.c
  loslib.c
  ltablib.c
  lua_struct.c
  lauxlib.c
  ldump.c
  lmathlib.c
  lparser.c
  ltm.c
  lundump.c
  lbaselib.c
  lfunc.c
  lmem.c
  lstate.c
# lua.c
  lvm.c
  lcode.c
  lgc.c
  loadlib.c
  lstring.c
# luac.c
  lzio.c
  ldblib.c
  linit.c
  lobject.c
  lstrlib.c
  lua_cjson.c
  print.c
  ldebug.c
  liolib.c
  lopcodes.c
  ltable.c
  lua_cmsgpack.c
  strbuf.c
  )

add_library(lua
  ${LUA_SOURCES}
  )
