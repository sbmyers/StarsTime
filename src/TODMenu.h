#pragma once
#include "pebble.h"
  
typedef struct{
  uint32_t key;
  short startTime;
  char label[10];
} Entry;
  
void ShowTODMenu(char *label, short *times, int nEntries,int first);