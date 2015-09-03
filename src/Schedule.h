#pragma once

#include "pebble.h"
  
typedef struct{
  time_t start;
  char *visitor;
  char *home;
}GameInfo;

bool IsToday();
GameInfo *FindGameTime();

void SetGameAlarm(struct tm *gameTime, time_t startTime, int32_t nGame);
