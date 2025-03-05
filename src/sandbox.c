#include <stdio.h>
#include <jpeglib.h>

#include "sandbox.h"

#include "error_manager.h"

size_t sandbox_get_jpeg_width(FILE *fp) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    size_t size;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);

    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        return 0;
    }

    size = cinfo.image_width;

    jpeg_destroy_decompress(&cinfo);

    return size;
}

size_t sandbox_get_jpeg_height(FILE *fp) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    size_t size;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);

    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        return 0;
    }

    size = cinfo.image_height;

    jpeg_destroy_decompress(&cinfo);

    return size;
}
