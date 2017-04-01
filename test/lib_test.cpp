//
// This source file contains test that checks library dependencies of imported library.
// Created by ken.yu on 16-10-13.
//

#include "ObjTracking.hpp"
#include <cstdio>
#include <cstdlib>

#define BUF_SIZE 10000

int main(int argc, char *argv[]) {

  FILE *file = fopen(argv[1], "r");
  char *conf = (char *) malloc(BUF_SIZE);
  size_t read_cnt = fread(conf, sizeof(char), BUF_SIZE, file);

  printf("Create ObjTracking...\n");
  ObjTracking tracking;

  printf("Init ObjTracking...\n");
  tracking.init(1000, 1000, 3, conf, (int) read_cnt);

  printf("ObjTracking initialized successfully!\n");
  free(conf);

  return 0;
}