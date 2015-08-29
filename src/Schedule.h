#pragma once

#include "pebble.h"
  
enum{Sunday5, Sunday1st=Sunday5, Sunday7, SundayLast=Sunday7,
     WeekDay730, 
     Saturday2, Saturday1st=Saturday2, Saturday3, Saturday6, Saturday7, Saturday8, SaturdayLast=Saturday8,};

typedef struct{
  time_t start;
  char *visitor;
  char *home;
}GameInfo;

bool IsToday();
GameInfo *FindGameTime();