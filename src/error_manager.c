#include <stdio.h>
#include <setjmp.h>
#include <stdbool.h>

#include <jpeglib.h>

#include "sandbox.h"

#include "error_manager.h"

static struct sandbox_error_mgr error_mgr;
static bool error_mgr_initialized = false;

METHODDEF(void)
sandbox_output_message(j_common_ptr cinfo)
{
    sandbox_error_ptr err = (sandbox_error_ptr)cinfo->err;
    (*(cinfo->err->format_message))(cinfo, err->last_error_msg);
}

void *get_error_mgr(void)
{
    if (!error_mgr_initialized) {
        jpeg_std_error(&error_mgr.pub);
        error_mgr.pub.output_message = sandbox_output_message;
        error_mgr_initialized = true;
    }

    return &error_mgr.pub;
}
