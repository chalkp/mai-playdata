#pragma once
#include <stddef.h>
#include <time.h>

/* rating at certain time */
struct rating {
  int rating;
  time_t date;
};

size_t read_rating_from_file(char *file_path, struct rating** ratings);
void append(struct rating new_rating, char *file_path);
