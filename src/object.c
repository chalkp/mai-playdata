#include "object.h"
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>

int read_file_content(FILE *file,
    unsigned char **file_content,
    size_t *file_size) {
  fseek(file, 0, SEEK_END);
  *file_size = ftell(file);
  rewind(file);

  *file_content = (unsigned char *)malloc(*file_size);
  if (*file_content == NULL) {
    fprintf(stderr, "object.c/read_file_content: malloc error\n");
    return -1;
  }

  if (fread(*file_content, sizeof(unsigned char), *file_size, file) != *file_size) {
    fprintf(stderr, "object.c/read_file_content: fread failed\n");
    return -1;
  }

  return 0;
}

int write_compressed_object_file(gzFile obj_file, unsigned char *file_content, size_t file_size) {
  int flush, chunk_size;
  flush = Z_NO_FLUSH;

  while (file_size > 0) {
    chunk_size = (file_size < GZ_BUFFER_SIZE) ? file_size : GZ_BUFFER_SIZE;
    if (gzwrite(obj_file, file_content, chunk_size) != chunk_size) {
      fprintf(stderr, "object.c/write_compressed_object_file: gzwrite error\n");
      return -1;
    }
    file_content += chunk_size;
    file_size -= chunk_size;
    if (file_size == 0) flush = Z_FINISH;
  }
  
  if (gzflush(obj_file, flush) != Z_OK) {
    fprintf(stderr, "object.c/write_compressed_object_file: gzflush error\n");
    return -1;
  }

  return 0;
}

int create_object_path(const char *hash_string,
    char *obj_path,
    size_t path_size) {
  if (snprintf(obj_path, path_size, "%s%s", OBJ_DIR, hash_string) >= (int)path_size) {
    fprintf(stderr, "object.c/create_object_path: path overflow\n");
    return -1;
  }
  return 0;
}

struct object objectify(FILE *file) {
  struct object obj;
  size_t file_size;
  unsigned char *file_content;

  if (read_file_content(file, &file_content, &file_size) != 0) {
    return obj;
  }

  SHA_ALGO(file_content, file_size, obj.hash);

  char hash_string_hex[SHA_STRING_LEN];
  for (int i=0; i<OBJ_SHA_LENGTH; i++) {
    snprintf(&hash_string_hex[i*2], sizeof(hash_string_hex)-(i*2), "%02x", obj.hash[i]);
  }

  char obj_path[256]; // overkill af
  if (create_object_path(hash_string_hex, obj_path, sizeof(obj_path)) != 0) {
    free(file_content);
    return obj;
  }

  gzFile obj_file = gzopen(obj_path, "wb+");
  if (obj_file == NULL) {
    fprintf(stderr, "object.c/objectify: gzopen error\n");
    free(file_content);
    return obj;
  }

  if (write_compressed_object_file(obj_file, file_content, file_size) != 0) {
    free(file_content);
    gzclose(obj_file);
    return obj;
  }

  free(file_content);
  gzclose(obj_file);

  return obj;
}
