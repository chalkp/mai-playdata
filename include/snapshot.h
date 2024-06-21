#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "object.h"

struct snapshot {
  struct object snapshot_object;
  struct object *objects;
  time_t snapshot_time;

  unsigned int index;
};
