#pragma once
#include <stdio.h>
#include <zlib.h>
#include "define.h"

struct object {
  unsigned char hash[OBJ_SHA_LENGTH];
  enum object_type type : OBJ_GENERIC;
};

int read_file_content(FILE *file, unsigned char **file_content, size_t *file_size);
int create_object_path(const char *hash_string, char *obj_path, size_t path_size);
int write_compressed_object_file(gzFile obj_file, unsigned char *file_content, size_t file_size);
struct object objectify(FILE *file);
