#ifndef __MATH__
#define __MATH__
#include <math.h>

unsigned int fact(unsigned int num);
unsigned int binomial(int a, int b);

float binompdf(int n, float p, int k);
float binomcdf(int trials, float probability, int value);

#endif
