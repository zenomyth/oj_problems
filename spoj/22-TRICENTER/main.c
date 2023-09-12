#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int case_count;
	double a, ga, gb, gc;
	double b, c, s, A, R, GHGH, GH;
	scanf("%d", &case_count);
	while (case_count--) {
		scanf("%lf %lf %lf %lf", &a, &ga, &gb, &gc);
		b = a * ga / gb;
		c = a * ga / gc;
		s = (a + b + c) / 2;
		A = sqrt(s * (s - a) * (s - b) * (s - c));
		R = a * b * c / (4 * A);
		GHGH = 4 * R * R - 4 * (a * a + b * b + c * c) / 9;
		if (GHGH >= 0)
			GH = sqrt(GHGH);
		else
			GH = 0;
		printf("%.3f %.3f\n", A, GH);
	}
	exit(0);
}