#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int elicopter_valid(int a, int b, int c, int d)
{
	if (abs(a - c) == abs(b - d) && a != c && b != d) {
		if (abs(a - c) > 0) {
			return abs(a - c) + 1;
		} else {
			return 0;
		}

	} else {
		return 0;
	}
}

int elicopter_suma(char harta[][2000], int a, int b, int c,
				   int d, int x1, int y1, int lung, int n, int m)
{
	int s_mat = 0, aux;
	if (c > a) {
		aux = c;
		c = a;
		a = aux;
	}
	if (d > b) {
		aux = d;
		d = b;
		b = aux;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * m; j += 2) {
			if (i >= c && i <= a && j >= d && j <= b) {
				if (abs(i - x1) + (abs(j - y1) / 2) <= lung) {
					s_mat += harta[i][j] - '0';
				}
			}
		}
	}
return s_mat;
}

int elicopter_pozitionat(char harta[][2000], int a, int b,
						 int c, int d, int s, int n, int m)
{
	int S = 0, s_mat = 0, lung = elicopter_valid(a, b, c, d) - 1, x1, y1;
	int lungime = lung + 1;
	if (elicopter_valid(a, b, c, d)) {
		for (int i = 0; i <= lungime; i++) {
			S = S + (lungime - i);
		}
	}
	b *= 2;
	d *= 2;
	if (a > c && b > d && s == 1) {
		x1 = a - lung;
		y1 = b;
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a > c && b > d && s == -1) {
		x1 = a;
		y1 = b - (lung * 2);
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a > c && b < d && s == 1) {
		x1 = a - lung;
		y1 = b;
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a > c && b < d && s == -1) {
		x1 = a;
		y1 = b + (lung * 2);
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a < c && b > d && s == 1) {
		x1 = a;
		y1 = b - (lung * 2);
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a < c && b > d && s == -1) {
		x1 = a + lung;
		y1 = b;
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a < c && b < d && s == 1) {
		x1 = a;
		y1 = b + (lung * 2);
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (a < c && b < d && s == -1) {
		x1 = a + lung;
		y1 = b;
		s_mat += elicopter_suma(harta, a, b, c, d, x1, y1, lung, n, m);
	}
	if (s_mat == S) {
		return 1;
	}
	if (s_mat * 2 < S) {
		return -1;
	}

return 0;

}

int main(void)
{
	char harta[2000][2000];
	int n, m, nr_heli, r1[800], r2[800], c1[800], c2[800], s[800];
	int ord, perfect = 0, gresit = 0, v_sol[800], pozitie;
	scanf("%d %d", &n, &m);
	fgets(harta[0], 2 * m + 2, stdin);

for (int i = 0; i < n; i++) {
	fgets(harta[i], 2 * m + 2, stdin);
	if (strlen(harta[i]) > 0 && harta[i][strlen(harta[i]) - 1] == '\n') {
		harta[i][strlen(harta[i]) - 1] = '\0';
	}
}

	scanf("%d", &nr_heli);
	for (int i = 0; i < nr_heli; i++) {
		scanf("%d %d %d %d %d", &r1[i], &c1[i], &r2[i], &c2[i], &s[i]);
		r1[i]--;
		c1[i]--;
		r2[i]--;
		c2[i]--;

	}
	for (int i = 0; i < nr_heli; i++) {
		ord = i + 1;
		pozitie = elicopter_pozitionat(harta, r1[i], c1[i],
									   r2[i], c2[i], s[i], n, m);
		if (elicopter_valid(r1[i], c1[i], r2[i], c2[i]) == 0) {
			printf("Elicopterul %d este pozitionat necorespunzator!\n", ord);
		} else if (pozitie == 1) {
			perfect++;
		} else if (pozitie == -1) {
			gresit++;
			v_sol[gresit] = ord;

		}
	}
	printf("%d\n", perfect);
	printf("%d\n", gresit);
	for (int i = 1; i <= gresit; i++) {
		printf("%d ", v_sol[i]);
	}

return 0;

}
