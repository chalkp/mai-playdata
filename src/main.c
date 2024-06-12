#include <stdio.h>
#include <string.h>

#include "rating/rating.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    if (!strcmp(argv[1], "read")) {
      Rating* ratings = NULL;
      size_t size = read(argv[2], &ratings);
      int prev_rating = ratings[0].rating;
      for (size_t i=0; i<size; i++) {
        printf("%d/%d/%d : %d (+%d)\n",
          ratings[i].date.year,
          ratings[i].date.month,
          ratings[i].date.day,
          ratings[i].rating,
          ratings[i].rating-prev_rating
        );
        prev_rating = ratings[i].rating;
      }
      free(ratings);
    } else if (!strcmp(argv[1], "write")) {
      Rating rating;
      printf("rating: ");
      scanf("%d", &rating.rating);
      printf("yyyy mm dd: ");
      scanf("%d %d %d", &rating.date.year, &rating.date.month, &rating.date.day);
      append(rating, argv[2]);
    } else {
      printf("usage: %s [read/write] <file>\n", argv[0]);
    }
  } else {
    printf("usage: %s [read/write] <file>\n", argv[0]);
  }
  return 0;
}

