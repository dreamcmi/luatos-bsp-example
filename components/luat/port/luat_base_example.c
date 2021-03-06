#include "luat_base.h"
#include "luat_malloc.h"
#include "luat_msgbus.h"
#include "luat_log.h"

static const luaL_Reg loadedlibs[] = {
    {"_G", luaopen_base},               // _G
    {LUA_LOADLIBNAME, luaopen_package}, // require
    {LUA_COLIBNAME, luaopen_coroutine}, // coroutine协程库
    {LUA_TABLIBNAME, luaopen_table},    // table库,操作table类型的数据结构
    {LUA_IOLIBNAME, luaopen_io},        // io库,操作文件
    {LUA_OSLIBNAME, luaopen_os},        // os库,已精简
    {LUA_STRLIBNAME, luaopen_string},   // string库,字符串操作
    {LUA_MATHLIBNAME, luaopen_math},    // math 数值计算
                                        //  {LUA_UTF8LIBNAME, luaopen_utf8},
    {LUA_DBLIBNAME, luaopen_debug},     // debug库,已精简
#if defined(LUA_COMPAT_BITLIB)
    {LUA_BITLIBNAME, luaopen_bit32}, // 不太可能启用
#endif
    // 往下是RTT环境下加载的库
    {"rtos", luaopen_rtos},   // rtos底层库, 核心功能是队列和定时器
    {"log", luaopen_log},     // 日志库
    {"timer", luaopen_timer}, // 延时库
    {NULL, NULL}};

// 按不同的rtconfig加载不同的库函数
void luat_openlibs(lua_State *L)
{
  // 初始化队列服务
  luat_msgbus_init();
  //print_list_mem("done>luat_msgbus_init");
  // 加载系统库
  const luaL_Reg *lib;
  /* "require" functions from 'loadedlibs' and set results to global table */
  for (lib = loadedlibs; lib->func; lib++)
  {
    luaL_requiref(L, lib->name, lib->func, 1);
    lua_pop(L, 1); /* remove lib */
                   //extern void print_list_mem(const char* name);
                   //print_list_mem(lib->name);
  }
}

//重启函数
void luat_os_reboot(int code)
{

}

const char *luat_os_bsp(void)
{
  return "example";
}

void luat_os_standy(int timeout)
{
}

void luat_os_entry_cri(void)
{
}

void luat_os_exit_cri(void)
{
}

void luat_meminfo_sys(size_t *total, size_t *used, size_t *max_used)
{
  *used = 0;
  *max_used = 0;
  *total = 0;
}

void luat_nprint(char *s, size_t l)
{
  printf("%s", s);
}
