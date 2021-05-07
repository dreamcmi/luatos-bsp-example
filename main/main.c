#include "bget.h"
#include "luat_base.h"

#define LUAT_HEAP_SIZE (64*1024)
uint8_t luavm_heap[LUAT_HEAP_SIZE] = {0};

void app_main(void)
{
    bpool(luavm_heap, LUAT_HEAP_SIZE);  // lua vm需要一块内存用于内部分配, 给出首地址及大小.
    luat_main();      // luat_main是LuatOS的主入口, 该方法通常不会返回.
}
