#pragma once
#include <stdio.h>

#include "rating/types.h"

void append(Rating rating, char *file_path) {
  FILE *file;
  file = fopen(file_path, "a");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return;
  }
  fwrite(&rating, sizeof(rating), 1, file);
  fclose(file);
}
