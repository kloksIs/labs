#include <stdio.h>
#include <math.h>

float min(float x, float y){
	if (x > y){
		x = y;
	}
	return x;
}

int main(void){
	float x, y;
	float hx = 0.6;
	float hy = 0.7;
	float result;

	for (x = 0; x <= 1; x += hx){
		for (y = 1; y <= 2; y += hy){
			result = min(min(1./tan(x/y),pow(x+y,1./3)),x*x + y*y);
			printf("x = %f\ty = %f\tV = %f\n", x, y, result);
		}
	}
	return 0;
}
