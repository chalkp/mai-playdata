#pragma once
typedef struct date {
  int day;
  int month;
  int year;
} Date;

typedef struct rating {
  int rating;
  Date date;
} Rating;
