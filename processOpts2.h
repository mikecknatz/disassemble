#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#ifndef PROCESSOPTS2_H_
#define PROCESSOPTS2_H_

int processOpts2(int argc, char *argv[], int *rFormatFlag, int *jFormatFlag, int *iFormatFlag);
int readMipsFile(int argc, char *argv[], int rFormatFlag, int jFormatFlag, int iFormatFlag);

#endif