#ifndef SANDBOX_H
#define SANDBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool sandbox_test(void);
size_t sandbox_get_jpeg_width(FILE *fp);
size_t sandbox_get_jpeg_height(FILE *fp);

#endif  /* SANDBOX_H */
