#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rating/types.h"

size_t read(char *file_path, Rating** ratings) {
  FILE *file;
  file = fopen(file_path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return 0;
  }
  fseek(file, 0, SEEK_END);
  size_t fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  *ratings = (Rating*)malloc(fsize);
  fread(*ratings, sizeof(Rating), fsize, file);
  fclose(file);

  return fsize / sizeof(Rating);
}
