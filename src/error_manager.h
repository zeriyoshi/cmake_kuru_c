#ifndef SANDBOX_ERROR_MANAGER_H
#define SANDBOX_ERROR_MANAGER_H

#include <jpeglib.h>

struct sandbox_error_mgr {
    struct jpeg_error_mgr pub;
    char last_error_msg[JMSG_LENGTH_MAX];
};

typedef struct sandbox_error_mgr *sandbox_error_ptr;

void *get_error_mgr(void);

#endif  /* SANDBOX_ERROR_MANAGER_H */
