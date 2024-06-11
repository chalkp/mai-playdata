#include <stdio.h>
#include <string.h>

typedef struct date {
  int day;
  int month;
  int year;
} Date;

typedef struct rating {
  int rating;
  Date date;
} Rating;

void print(char *file_path);
void add(char *file_path);

int main(int argc, char *argv[]) {
  if (argc>2) {
    if (!strcmp(argv[2], "print")) {
      print(argv[1]);
    } else if (!strcmp(argv[2], "print")) {
      add(argv[1]);
    } else {
      printf("usage: %s <file> [add/print]\n", argv[0]);
    }
  } else {
    printf("usage: %s <file> [add/print]\n", argv[0]);
  }
  return 0;
}

void print(char *file_path) {
  FILE *file;
  file = fopen(file_path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return;
  }

  fseek(file, 0, SEEK_END);
  size_t fsize = ftell(file)/sizeof(Rating);
  fseek(file, 0, SEEK_SET);

  printf("chalkp's maimai rating by date\n");

  Rating ratings[fsize];
  fread(ratings, sizeof(ratings[0]), fsize, file);
  {
    int prev_rating = ratings[0].rating;
    for (int i=0; i<fsize; i++) {
      printf("%d/%d/%d: %d (+%d)\n", ratings[i].date.year, ratings[i].date.month, ratings[i].date.day, ratings[i].rating, ratings[i].rating-prev_rating);
      prev_rating = ratings[i].rating;
    }
  }
  fclose(file);
}

void add(char *file_path) {
  FILE *file;
  file = fopen(file_path, "a");
  if (file == NULL) {
    fprintf(stderr, "Error opening %s\n", file_path);
    return;
  }
  Rating rating;

  printf("rating: ");
  scanf("%d", &rating.rating);
  printf("y m d: ");
  scanf("%d %d %d", &rating.date.year, &rating.date.month, &rating.date.day);


  fwrite(&rating, sizeof(rating), 1, file);
  fclose(file);
}
