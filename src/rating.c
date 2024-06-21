#include "rating.h"
#include <stdio.h>
#include <stdlib.h>

size_t read_rating_from_file(char *file_path, struct rating** ratings) {
  FILE *file;
  size_t fsize;
  file = fopen(file_path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return 0;
  }
  fsize = fread(NULL, 1, 0, file);
  fseek(file, 0, SEEK_SET);
  *ratings = (struct rating*)malloc(fsize);
  fread(*ratings, sizeof(struct rating), fsize, file);
  fclose(file);
  return fsize / sizeof(struct rating);
}

void append(struct rating new_rating, char *file_path) {
  FILE *file;
  file = fopen(file_path, "ab");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return;
  }
  fwrite(&new_rating, sizeof(struct rating), 1, file);
  fclose(file);
}
