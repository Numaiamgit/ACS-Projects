#include<stdio.h>
#define MAX_WINDOW 400
#define MAX_NR_VALORI 20000
unsigned long long CMMDC(unsigned long long a, unsigned long long b)
{
while (a != 0 && b != 0) {
	unsigned long long aux = b;
	b = a % b;
	a = aux;
if (a == 0)
	return b;
if (b == 0)
	return a;
}

return a;

}

unsigned long long CMMMC(unsigned long long a, unsigned long long b)
{

	unsigned long long cmmdc = a / CMMDC(a, b);
	return cmmdc * b;

}

int main(void)
{
int window, counter = 1, j;
unsigned long long t[MAX_NR_VALORI], v[MAX_NR_VALORI];
scanf("%d", &window);
scanf("%llu %llu", &t[0], &v[0]);
	while (t[counter - 1] != 0 && v[counter - 1] != 0) {
		scanf("%llu %llu", &t[counter], &v[counter]);
		counter++;
		}
	for (int i = 0; i < counter - 2; i++) {
		j = i + 1;
		while (t[j] - t[i] <= (unsigned long long)window && j < counter - 1) {
			printf("%llu %llu\n", CMMMC(v[i], v[j]), CMMDC(v[i], v[j]));
			j++;
		}
	}

	return 0;

}
