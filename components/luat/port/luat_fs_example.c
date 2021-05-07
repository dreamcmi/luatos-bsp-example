#include "luat_base.h"
#include "luat_malloc.h"
#include "luat_fs.h"
#include "luat_msgbus.h"


int luat_fs_init(void);

int luat_fs_info(const char *path, luat_fs_info_t *conf);

