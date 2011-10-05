#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include "lua.h"
#include "lauxlib.h"

int init_module(void) {
  lua_State *L;
  int status;

	printk(KERN_INFO "Hello world 1.\n");

  L = luaL_newstate();

  status = luaL_loadstring(L, "return 12 + 30");
  if (status) {
    /* If something went wrong, error message is at the top of */
    /* the stack */
    printk("Couldn't load file: %s\n", lua_tostring(L, -1));
    return -1;
  }

	lua_pcall(L, 0, LUA_MULTRET, 0);

	printk(KERN_INFO "Result: %ld\n", lua_tonumber(L, -1));

	return 0;
}

void cleanup_module(void) {
	printk(KERN_INFO "Goodbye world 1.\n");
}
