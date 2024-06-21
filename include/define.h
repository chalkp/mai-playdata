#pragma once
#include <openssl/sha.h>

#define RATING_FILE "./ratings"
#define OBJ_DIR "./objects/"

// * object.h related defines

#define SHA_ALGO SHA1
#define OBJ_SHA_LENGTH SHA256_DIGEST_LENGTH
#define SHA_STRING_LEN (OBJ_SHA_LENGTH<<1)+1
#define GZ_BUFFER_SIZE 8192

enum object_type {
  OBJ_NONE = 0,
  OBJ_SNAPSHOT = 1,
  OBJ_SONG = 2,
  OBJ_SCORE = 3,
  OBJ_GENERIC = 4
};


// * song.h related defines

enum genre {
  GENRE_POP_ANI = 0,
  GENRE_NICO_VOCA = 1,
  GENRE_TOUHOU = 2,
  GENRE_GAME_VARA = 3,
  GENRE_MAIMAI = 4,
  GENRE_GEKI_CHU = 5
};

enum version {
  VER_MAIMAI = 0,
  VER_MAIMAI_PLUS = 1,
  VER_GREEN = 2,
  VER_GREEN_PLUS = 3,
  VER_ORANGE = 4,
  VER_ORANGE_PLUS = 5,
  VER_PINK = 6,
  VER_PINK_PLUS = 7,
  VER_MURASAKI = 8,
  VER_MURASAKI_PLUS = 9,
  VER_MILK = 10,
  VER_MILK_PLUS = 11,
  VER_FINALE = 12,
  VER_DX = 13,
  VER_DX_PLUS = 14,
  VER_SPLASH = 15,
  VER_SPLASH_PLUS = 16,
  VER_UNIVERSE = 17,
  VER_UNIVERSE_PLUS = 18,
  VER_FESTIVAL = 19,
  VER_FESTIVAL_PLUS = 20,
  VER_BUDDIES = 21,
  VER_BUDDIES_PLUS = 22  
};

enum chart {
  CHART_STD = 0,
  CHART_DX = 1
};


// * score.h realated defines

enum difficulty {
  DIFF_BASIC = 0,
  DIFF_ADVANCED = 1,
  DIFF_EXPERT = 2,
  DIFF_MASTER = 3,
  DIFF_REMASTER = 4
};

enum level {
  LEVEL_1 = 1,
  LEVEL_2 = 2,
  LEVEL_3 = 3,
  LEVEL_4 = 4,
  LEVEL_5 = 5,
  LEVEL_6 = 6,
  LEVEL_7 = 7,
  LEVEL_7_PLUS = 8,
  LEVEL_8 = 9,
  LEVEL_8_PLUS = 10,
  LEVEL_9 = 11,
  LEVEL_9_PLUS = 12,
  LEVEL_10 = 13,
  LEVEL_10_PLUS = 14,
  LEVEL_11 = 15,
  LEVEL_11_PLUS = 16,
  LEVEL_12 = 17,
  LEVEL_12_PLUS = 18,
  LEVEL_13 = 19,
  LEVEL_13_PLUS = 20,
  LEVEL_14 = 21,
  LEVEL_14_PLUS = 22,
  LEVEL_15 = 23
};

enum rank {
  RANK_D = 0,
  RANK_C = 1,
  RANK_B = 2,
  RANK_BB = 3,
  RANK_BBB = 4,
  RANK_A = 5,
  RANK_AA = 6,
  RANK_AAA = 7,
  RANK_S = 8,
  RANK_S_PLUS = 9,
  RANK_SS = 10,
  RANK_SS_PLUS = 11,
  RANK_SSS = 12,
  RANK_SSS_PLUS = 13
};

enum fcap {
  FCAP_NONE = 0,
  FCAP_FC = 1,
  FCAP_FC_PLUS = 2,
  FCAP_AP = 3,
  FCAP_AP_PLUS = 4
};

enum sync {
  SYNC_NONE = 0,
  SYNC_SYNC = 1,
  SYNC_FS = 2,
  SYNC_FS_PLUS = 3,
  SYNC_FDX = 4,
  SYNC_FDX_PLUS = 5
};


