#include <linux/module.h>
#include <linux/kernel.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Richard Musiol <mail@richard-musiol.de>");
MODULE_DESCRIPTION("Lua scripting in kernel space");

extern char _binary_test_lua_start[];

static int __init lua_module_init(void) {
  lua_State *L;
  int status;

	printk(KERN_INFO "Hello world 1.\n");

  L = luaL_newstate();
  luaL_openlibs(L);

  status = luaL_loadstring(L, _binary_test_lua_start);
  if (status) {
    printk(KERN_ERR "lua: could not load file (%s)\n", lua_tostring(L, -1));
    return -1;
  }

	status = lua_pcall(L, 0, LUA_MULTRET, 0);
  if (status) {
    printk(KERN_ERR "lua: could not run script (%s)\n", lua_tostring(L, -1));
    return -1;
  }

	printk(KERN_INFO "Result: %ld\n", lua_tonumber(L, -1));

	return 0;
}

static void __exit lua_module_exit(void) {
	printk(KERN_INFO "Goodbye world 1.\n");
}

module_init(lua_module_init);
module_exit(lua_module_exit);
