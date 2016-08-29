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

unsigned int binomial(int n, int k) {
	if (k > n / 2) k = n - k;
	if (k == 0) return 1;
	unsigned int res = 1;
	for (int i = k + 1; i <= n; i++) {
		res = i * res / (i - k);
	}
	return res;
}

float binompdf(int n, float p, int k) {
	return binomial(n, k) * powf(p, k) * powf(1-p, n-k);
}

//assumes 0<=value<=trials, 0.0<=probability<=1.0
float binomcdf(int trials, float probability, int value) {
	if (value == 0) {
		return 0.0f;
	}
	if (trials == 1 || probability == 0 || probability == 1) {
		return 1 - probability;
	}
	if (trials == 0) {
		return 1.0f;
	}
	int pascal[trials - 1];
	pascal[0] = 2;
	for(int i = 2; i < trials; i++){
		pascal[i - 1] = pascal[i - 2] + 1;
		for(int j = i - 2; j > 0; j--) {
			pascal[j] += pascal[j - 1];
		}
		pascal[0]++;
	}
	float sum = 0.0f, pk = 1.0f, qnk = powf(1 - probability, trials);
	if (value > 0) {
		sum = qnk;
		pk *= probability;
		qnk /= 1 - probability;
	}
	for(int i = 1; i < value; i++) {
		sum += pascal[i - 1] * pk * qnk;
		pk *= probability;
		qnk /= 1 - probability;
	}
	return sum;
}
