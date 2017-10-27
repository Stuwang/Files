project(LuaTest)
 
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../test)
 
##########lua静态库############################################
set(LIB_FILES 
	lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c 
	lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c 
	lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c 
	lzio.c lauxlib.c lbaselib.c lbitlib.c lcorolib.c 
	ldblib.c liolib.c lmathlib.c loslib.c lstrlib.c 
	ltablib.c lutf8lib.c loadlib.c linit.c)
 
source_group("\\libFiles" FILES ${LIB_FILES})


add_library (liblua STATIC ${LIB_FILES})
 
############lua解释器###########
add_executable(lua lua.c)
target_link_libraries(lua liblua)
 
 
#ADD_DEFINITIONS(-LUA_LIB -LUA_BUILD_AS_DLL)
######################################define LUA_LIB##################################################
######################################define LUA_BUILD_AS_DLL#########################################

add_executable(CppLua 
	../test/source.cpp
	../test/LuaRuntime.h
	../test/LuaRuntime.cpp
	)
 
target_link_libraries(CppLua liblua)