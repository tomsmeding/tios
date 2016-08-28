#include "math.h"

unsigned int fact(unsigned int num) {
	if (num == 0 || num == 1) {
		return 1;
	} else {
		int res = num;
		int n = num;
		while (n-->1) {
			res *= n;
		}
		return res;
	}
}

unsigned int binomial(int a, int b) {
	return fact(a) / (fact(b) * fact(a - b));
}

float binompdf(int n, float p, int k) {
	return binomial(n, k) * powf(p, k) * powf(1-p, n-k);
}

float binomcdf(int trials, float probability, int value) {
	float sum = 0.0f;
	int i;
	for (i = 0; i < value; i++) {
		sum += binompdf(trials, probability, i);
	}
	return sum;
}
