
#include <stdio.h>
#include "lua.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "assert.h"

lua_State* L;

void lua_initialize(int* argc, char*** argv) {
  L = (lua_State*)lua_open();
  luaopen_base(L);
  luaopen_table(L);
  luaopen_string(L);
  luaopen_math(L);
  lua_pushcfunction(L, luaopen_io);
  lua_call(L, 0, 0);
}

void lua_print(int n) {
  assert(luaL_dofile(L, "lua.lua") == 0);
  lua_getglobal(L, "lua_print");
  lua_pushnumber(L, n);
  lua_pcall(L, 1, 0, 0);
}

void lua_release() {
  lua_close(L);
}
