#ifndef LUARUNTIME_H__
#define LUARUNTIME_H__

#include <iostream>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};

class LuaRuntime {
public:

	LuaRuntime() {
		L = NULL;
	}

	~LuaRuntime() {
		if (L) {
			lua_close(L);
			L = NULL;
		}
	}

	void Init() {
		L = luaL_newstate();
	}

	void OpenLibBase() {
		luaopen_base(L);
	}
	void OpenLibTable() {
		luaopen_table(L);
	}

	void OpenLibPackage() {
		luaopen_package(L);
	}

	void OpenLibIo() {
		luaopen_io(L);

	}

	void OpenLibString() {
		luaopen_string(L);
	}

	void OpenAllLib() {
		luaL_openlibs(L);
	}

	void InitAll() {
		L = luaL_newstate();
		luaopen_base(L);
		luaopen_table(L);
		luaopen_package(L);
		luaopen_io(L);
		luaopen_string(L);

		luaL_openlibs(L);
	}

	int GetInt(const char* name, int def = 0) {
		lua_getglobal(L, name);
		if (!lua_isnumber(L, -1))
		{
			std::cout << "-2 error" << lua_isnumber(L, -1) << lua_isnumber(L, -1) << std::endl;
			return def;
		}
		return lua_tonumber(L, -1);
	}

	void RunString(const char* str) {
		if (luaL_loadstring(L, str)
				|| lua_pcall(L, 0, 0, 0))
		{
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
		}
	};

	void RunFile(const char* file) {
		if (luaL_loadfile(L, file)
				|| lua_pcall(L, 0, 0, 0))
		{
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return;
		}
	}

	void CallFuncFromFile(const char* file, const char* func) {
		if (luaL_loadfile(L, file)) {
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return;
		}

		if (lua_pcall(L, 0, 0, 0)){
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return;
		}

		lua_getglobal(L, func);
		if (!lua_isfunction(L, -1)) {
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return;
		}

		if (lua_pcall(L, 0, 0, 0)) {
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return;
		}
	}

private:
	lua_State *L;

	LuaRuntime(const LuaRuntime&) = delete;
	LuaRuntime&operator=(const LuaRuntime&) = delete;
};

#endif //LUARUNTIME_H__