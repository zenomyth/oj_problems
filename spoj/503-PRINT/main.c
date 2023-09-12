#include <stdio.h>
#include <string.h>

int main(void)
{
	int t;
	unsigned int L;
	unsigned int U;
	unsigned char is_not_prime[1000001];
	unsigned int sieve[5000];
	unsigned int sieve_index_max;
	unsigned int i;
	unsigned int j;

	memset(is_not_prime, 0, sizeof(is_not_prime));
	for (i = 2; i * i * i * i <= 2147483647; ++i) {
		if (is_not_prime[i])
			continue;
		for (j = i * i; j * j <= 2147483647; j += i)
			is_not_prime[j] = 1;
	}
	for (i = 2, sieve_index_max = 0; i * i < 2147483647; ++i) {
		if (is_not_prime[i] == 0)
			sieve[sieve_index_max++] = i;
	}

	scanf("%d", &t);
	do {
		scanf("%u %u", &L, &U);
		memset(is_not_prime, 0, U - L + 1);
		for(i = 0; i < sieve_index_max && sieve[i] * sieve[i] <= U; ++i) {
			j = L / sieve[i] * sieve[i];
			while (j <= sieve[i] || j < L)
				j += sieve[i];
			while (j <= U) {
				is_not_prime[j - L] = 1;
				j += sieve[i];
			}
		}
		for (i = L; i <= U; ++i) {
			if (is_not_prime[i - L] == 0)
				printf("%d\n", i);
		}
	} while (--t > 0);
    return 0;
}
