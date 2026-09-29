#include <stdio.h>
#include <string.h>

void ziduri_numar(char joculet[][99], char nr1, int i, int j, int n, int m)
{
	int nr_beculete, nr;

	if (joculet[i][j] == nr1) {
		nr_beculete = 0;
		if (j <= 2 * m - 2 && joculet[i][j + 2] == 'L')
			nr_beculete++;
		if (j >= 2 && joculet[i][j - 2] == 'L')
			nr_beculete++;
		if (i <= n - 2 && joculet[i + 1][j] == 'L')
			nr_beculete++;
		if (i >= 1 && joculet[i - 1][j] == 'L')
			nr_beculete++;
		if (nr1 == '0')
			nr = 0;
		if (nr1 == '1')
			nr = 1;
		if (nr1 == '2')
			nr = 2;
		if (nr1 == '3')
			nr = 3;
		if (nr_beculete == nr) {
			if (j <= 2 * m - 2 && joculet[i][j + 2] == '-')
				joculet[i][j + 2] = 'x';
			if (j >= 2 && joculet[i][j - 2] == '-')
				joculet[i][j - 2] = 'x';
			if (i <= n - 2 && joculet[i + 1][j] == '-')
				joculet[i + 1][j] = 'x';
			if (i >= 1 && joculet[i - 1][j] == '-')
				joculet[i - 1][j] = 'x';
		}
	}
}

void inlocuire_x(char joculet[][99], int i, int j, int n, int m)
{
	int x, y;
	x = i + 1; y = j;
	while	(x >= 0 && x <= n - 1 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' && joculet[x][y] != 'L' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		joculet[x][y] = 'x';
		x++;
	}
	x = i - 1; y = j;
	while	(x >= 0 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' && joculet[x][y] != 'L' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		joculet[x][y] = 'x';
		x--;
	}
	x = i; y = j + 2;
	while	(y <= 2 * m - 2 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' && joculet[x][y] != 'L' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		joculet[x][y] = 'x';
		y += 2;
	}
	x = i; y = j - 2;
	while	(y >= 0 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' && joculet[x][y] != 'L' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		joculet[x][y] = 'x';
		y -= 2;
	}
}

int verifica_linii_coloane(char joculet[][99], int i, int j, int n, int m)
{
	int x, y, checker_becuri = 0;
	x = i + 1; y = j;
	while	(x >= 0 && x <= n - 1 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' && joculet[x][y] != '1' &&
			 joculet[x][y] != '2' && joculet[x][y] != '3' &&
			 joculet[x][y] != '4') {
		if (joculet[x][y] == 'L')
			checker_becuri++;
		x++;
	}

	x = i - 1; y = j;
	while	(x >= 0 && joculet[x][y] != '#' && joculet[x][y] != '0' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		if (joculet[x][y] == 'L')
			checker_becuri++;
		x--;
	}

	x = i; y = j + 2;
	while	(y <= 2 * m - 2 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		if (joculet[x][y] == 'L')
			checker_becuri++;
		y += 2;
	}

	x = i; y = j - 2;
	while	(y >= 0 && joculet[x][y] != '#' &&
			 joculet[x][y] != '0' &&
			 joculet[x][y] != '1' && joculet[x][y] != '2' &&
			 joculet[x][y] != '3' && joculet[x][y] != '4') {
		if (joculet[x][y] == 'L')
			checker_becuri++;
		y -= 2;
	}

	return checker_becuri;
}

int checker(char joculet[][99], char nr1, int i, int j, int n, int m)
{
	int checker_becuri = 0, nr_beculete, nr_libere = 0, nr, vecine = 4;
	if (i == 0 || i == n - 1)
		vecine--;
	if (j == 0 || j == 2 * m - 1)
		vecine--;
	if (joculet[i][j] == nr1) {
		nr_beculete = 0;
		if (j <= 2 * m - 2 && joculet[i][j + 2] == 'L')
			nr_beculete++;
		if (j >= 2 && joculet[i][j - 2] == 'L')
			nr_beculete++;
		if (i <= n - 2 && joculet[i + 1][j] == 'L')
			nr_beculete++;
		if (i >= 1 && joculet[i - 1][j] == 'L')
			nr_beculete++;
		if (j <= 2 * m - 2 && joculet[i][j + 2] == '-')
			nr_libere++;
		if (j >= 2 && joculet[i][j - 2] == '-')
			nr_libere++;
		if (i <= n - 2 && joculet[i + 1][j] == '-')
			nr_libere++;
		if (i >= 1 && joculet[i - 1][j] == '-')
			nr_libere++;
		if (nr1 == '0')
			nr = 0;
		if (nr1 == '1')
			nr = 1;
		if (nr1 == '2')
			nr = 2;
		if (nr1 == '3')
			nr = 3;
		if (nr1 == '4')
			nr = 4;
		if (nr_beculete > nr) {
			checker_becuri++;
			joculet[i][j] = 'N';
		} else if (nr_libere + nr_beculete < nr && nr_beculete < nr) {
			checker_becuri++;
			joculet[i][j] = 'N';
		}
	}

	return checker_becuri;
}

int main(void)
{
	int o, n, m, checker_becuri;
	char joculet[50][99];
	scanf("%d", &o);
	scanf("%d %d", &n, &m);
	getchar();
	for (int i = 0; i < n - 1; i++) {
		fgets(joculet[i], 2 * m + 1, stdin);
		joculet[i][strlen(joculet[i]) - 1] = '\0';
	}
	fgets(joculet[n - 1], 2 * m + 1, stdin);

	if (o == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] == 'L') {
					inlocuire_x(joculet, i, j, n, m);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] != '-' && joculet[i][j] != 'L' &&
					joculet[i][j] != '#' && joculet[i][j] != 'x') {
					ziduri_numar(joculet, joculet[i][j], i, j, n, m);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			printf("%s\n", joculet[i]);
		}
	}
	checker_becuri = 0;
	if (o == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] == 'L') {
					inlocuire_x(joculet, i, j, n, m);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] != '-' && joculet[i][j] != 'L' &&
					joculet[i][j] != '#' && joculet[i][j] != 'x') {
					ziduri_numar(joculet, joculet[i][j], i, j, n, m);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] == 'L') {
					checker_becuri +=
						verifica_linii_coloane(joculet, i, j, n, m);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * m; j += 2) {
				if (joculet[i][j] != '-' &&
					joculet[i][j] != 'L' &&
					joculet[i][j] != '#' && joculet[i][j] != 'x') {
					checker_becuri +=
						checker(joculet, joculet[i][j], i, j, n, m);
				}
			}
		}
		if (checker_becuri > 0) {
			printf("zero\n");
		} else {
			printf("ichi\n");
		}
	}

	return 0;
}
