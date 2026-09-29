// 311CB Gheorghe Alexandru-Nicolae
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_sqrt(int n)
{
	if (n < 0) return 0;
	int r = 0;
	while ((r + 1) * (r + 1) <= n) r++;
	return r;
}

int int_pow(int baza, int expo) {
	int rez = 1;
	for (int i = 0; i < expo; i++) rez *= baza;
	return rez;
}

int check_limite(char **amplasare, int **amplasare_poz, int j, int n, int m)
{
	if (amplasare[j][0] == 'S') {
		if (amplasare[j][1] == 'H') {
			if (amplasare_poz[j][0] > n || amplasare_poz[j][0] < 1) {
				return 0;
			}
			if (m - amplasare_poz[j][1] < 4 || amplasare_poz[j][1] < 1) {
				return 0;
			}
		} else if (amplasare[j][1] == 'V') {
			if (amplasare_poz[j][0] - 1 < 4 || amplasare_poz[j][0] > n) {
				return 0;
			}
			if (amplasare_poz[j][1] < 1 || amplasare_poz[j][1] > m) {
				return 0;
			}
		}
	}
	if (amplasare[j][0] == 'Y') {
		if (amplasare[j][1] == 'H') {
			if (amplasare_poz[j][0] > n || amplasare_poz[j][0] < 1) {
				return 0;
			}
			if (m - amplasare_poz[j][1] < 3 || amplasare_poz[j][1] < 1) {
				return 0;
			}
		} else if (amplasare[j][1] == 'V') {
			if (amplasare_poz[j][0] - 1 < 3 || amplasare_poz[j][0] > n) {
				return 0;
			}
			if (amplasare_poz[j][1] < 1 || amplasare_poz[j][1] > m) {
				return 0;
			}
		}
	}
	if (amplasare[j][0] == 'B') {
		if (amplasare[j][1] == 'H') {
			if (amplasare_poz[j][0] > n || amplasare_poz[j][0] < 1) {
				return 0;
			}
			if (m - amplasare_poz[j][1] < 2 || amplasare_poz[j][1] < 1) {
				return 0;
			}
		} else if (amplasare[j][1] == 'V') {
			if (amplasare_poz[j][0] - 1 < 2 || amplasare_poz[j][0] > n) {
				return 0;
			}
			if (amplasare_poz[j][1] < 1 || amplasare_poz[j][1] > m) {
				return 0;
			}
		}
	}
	if (amplasare[j][0] == 'L') {
		if (amplasare[j][1] == 'H') {
			if (amplasare_poz[j][0] > n || amplasare_poz[j][0] < 1) {
				return 0;
			}
			if (m - amplasare_poz[j][1] < 1 || amplasare_poz[j][1] < 1) {
				return 0;
			}
		} else if (amplasare[j][1] == 'V') {
			if (amplasare_poz[j][0] - 1 < 1 || amplasare_poz[j][0] > n) {
				return 0;
			}
			if (amplasare_poz[j][1] < 1 || amplasare_poz[j][1] > m) {
				return 0;
			}
		}
	}
	if (amplasare[j][0] == 'A') {
		if (amplasare_poz[j][0] > n || amplasare_poz[j][0] < 1) {
			return 0;
		}
		if (amplasare_poz[j][1] > m || amplasare_poz[j][1] < 1) {
			return 0;
		}
	}

	return 1;
}

int check_suprapuneri(char **amplasare, int **amplasare_poz,
					  char **battleships_1, char **battleships_2, int j)
{
	int k;
	if (j % 2 == 0) {
		if (amplasare[j][0] == 'S') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 3; i++) {
					if (battleships_1[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 5; i--) {
					if (battleships_1[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'Y') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 2; i++) {
					if (battleships_1[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 4; i--) {
					if (battleships_1[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'B') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 1; i++) {
					if (battleships_1[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 3; i--) {
					if (battleships_1[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'L') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1];
					 i++) {
					if (battleships_1[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 2; i--) {
					if (battleships_1[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'A') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] - 1; i++) {
					if (battleships_1[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 1; i--) {
					if (battleships_1[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
	}
	if (j % 2 != 0) {
		if (amplasare[j][0] == 'S') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 3; i++) {
					if (battleships_2[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 5; i--) {
					if (battleships_2[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'Y') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 2; i++) {
					if (battleships_2[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 4; i--) {
					if (battleships_2[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'B') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 1; i++) {
					if (battleships_2[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 3; i--) {
					if (battleships_2[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'L') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1];
					 i++) {
					if (battleships_2[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 2; i--) {
					if (battleships_2[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
		if (amplasare[j][0] == 'A') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] - 1; i++) {
					if (battleships_2[k - 1][i] != '0') {
						return 0;
					}
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 1; i--) {
					if (battleships_2[i][k - 1] != '0') {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

void construire_matrici(char **amplasare, int **amplasare_poz,
						char **battleships_1, char **battleships_2, int j) 
{
	int k;
	if (j % 2 == 0) {
		if (amplasare[j][0] == 'S') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 3; i++) {
					battleships_1[k - 1][i] = '5';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 5; i--) {
					battleships_1[i][k - 1] = '5';
				}
			}
		}
		if (amplasare[j][0] == 'Y') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 2; i++) {
					battleships_1[k - 1][i] = '4';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 4; i--) {
					battleships_1[i][k - 1] = '4';
				}
			}
		}
		if (amplasare[j][0] == 'B') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 1; i++) {
					battleships_1[k - 1][i] = '3';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 3; i--) {
					battleships_1[i][k - 1] = '3';
				}
			}
		}
		if (amplasare[j][0] == 'L') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1];
					 i++) {
					battleships_1[k - 1][i] = '2';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 2; i--) {
					battleships_1[i][k - 1] = '2';
				}
			}
		}
		if (amplasare[j][0] == 'A') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] - 1; i++) {
					battleships_1[k - 1][i] = '1';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 1; i--) {
					battleships_1[i][k - 1] = '1';
				}
			}
		}
	}
	if (j % 2 != 0) {
		if (amplasare[j][0] == 'S') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 3; i++) {
					battleships_2[k - 1][i] = '5';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 5; i--) {
					battleships_2[i][k - 1] = '5';
				}
			}
		}
		if (amplasare[j][0] == 'Y') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 2; i++) {
					battleships_2[k - 1][i] = '4';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 4; i--) {
					battleships_2[i][k - 1] = '4';
				}
			}
		}
		if (amplasare[j][0] == 'B') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] + 1; i++) {
					battleships_2[k - 1][i] = '3';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 3; i--) {
					battleships_2[i][k - 1] = '3';
				}
			}
		}
		if (amplasare[j][0] == 'L') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1];
					 i++) {
					battleships_2[k - 1][i] = '2';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 2; i--) {
					battleships_2[i][k - 1] = '2';
				}
			}
		}
		if (amplasare[j][0] == 'A') {
			if (amplasare[j][1] == 'H') {
				k = amplasare_poz[j][0];
				for (int i = amplasare_poz[j][1] - 1;
					 i <= amplasare_poz[j][1] - 1; i++) {
					battleships_2[k - 1][i] = '1';
				}
			} else if (amplasare[j][1] == 'V') {
				k = amplasare_poz[j][1];
				for (int i = amplasare_poz[j][0] - 1;
					 i >= amplasare_poz[j][0] - 1; i--) {
					battleships_2[i][k - 1] = '1';
				}
			}
		}
	}
}

void afisare_barca_distrusa(char **amplasare, int **amplasare_poz,
							char **battleships_1, char **battleships_2, int j,
							int rand) 
{
	int k, l;
	if (amplasare[j][0] == 'S') {
		if (amplasare[j][1] == 'H') {
			k = amplasare_poz[j][0];
			l = amplasare_poz[j][1] + 4;

			for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1] + 3;
				 i++) {
				if (rand == 1 && battleships_2[k - 1][i] != 'P') {
					battleships_2[k - 1][i] = 'x';
				} else if (rand == 2 && battleships_1[k - 1][i] != 'P') {
					battleships_1[k - 1][i] = 'x';
				}
			}
			printf("Jucatorul %d a distrus o nava Shinano plasata intre coordonatele (%d, %d) si (%d, %d).\n",
				   rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		} else if (amplasare[j][1] == 'V') {
			k = amplasare_poz[j][0] - 4;
			l = amplasare_poz[j][1];
			for (int i = amplasare_poz[j][0] - 1; i >= amplasare_poz[j][0] - 5;
				 i--) {
				if (rand == 1 && battleships_2[i][l - 1] != 'P') {
					battleships_2[i][l - 1] = 'x';
				} else if (rand == 2 && battleships_1[i][l - 1] != 'P') {
					battleships_1[i][l - 1] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Shinano plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		}
	}

	if (amplasare[j][0] == 'Y') {
		if (amplasare[j][1] == 'H') {
			k = amplasare_poz[j][0];
			l = amplasare_poz[j][1] + 3;
			for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1] + 2;
				 i++) {
				if (rand == 1 && battleships_2[k - 1][i] != 'P') {
					battleships_2[k - 1][i] = 'x';
				} else if (rand == 2 && battleships_1[k - 1][i] != 'P') {
					battleships_1[k - 1][i] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Yamato plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		} else if (amplasare[j][1] == 'V') {
			k = amplasare_poz[j][0] - 3;
			l = amplasare_poz[j][1];
			for (int i = amplasare_poz[j][0] - 1; i >= amplasare_poz[j][0] - 4;
				 i--) {
				if (rand == 1 && battleships_2[i][l - 1] != 'P') {
					battleships_2[i][l - 1] = 'x';
				} else if (rand == 2 && battleships_1[i][l - 1] != 'P') {
					battleships_1[i][l - 1] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Yamato plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		}
	}
	if (amplasare[j][0] == 'B') {
		if (amplasare[j][1] == 'H') {
			k = amplasare_poz[j][0];
			l = amplasare_poz[j][1] + 2;
			for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1] + 1;
				 i++) {
				if (rand == 1 && battleships_2[k - 1][i] != 'P') {
					battleships_2[k - 1][i] = 'x';
				} else if (rand == 2 && battleships_1[k - 1][i] != 'P') {
					battleships_1[k - 1][i] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Belfast plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		} else if (amplasare[j][1] == 'V') {
			k = amplasare_poz[j][0] - 2;
			l = amplasare_poz[j][1];
			for (int i = amplasare_poz[j][0] - 1; i >= amplasare_poz[j][0] - 3;
				 i--) {
				if (rand == 1 && battleships_2[i][l - 1] != 'P') {
					battleships_2[i][l - 1] = 'x';
				} else if (rand == 2 && battleships_1[i][l - 1] != 'P') {
					battleships_1[i][l - 1] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Belfast plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		}
	}
	if (amplasare[j][0] == 'L') {
		if (amplasare[j][1] == 'H') {
			k = amplasare_poz[j][0];
			l = amplasare_poz[j][1] + 1;
			for (int i = amplasare_poz[j][1] - 1; i <= amplasare_poz[j][1];
				 i++) {
				if (rand == 1 && battleships_2[k - 1][i] != 'P') {
					battleships_2[k - 1][i] = 'x';
				} else if (rand == 2 && battleships_1[k - 1][i] != 'P') {
					battleships_1[k - 1][i] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Laffey plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		} else if (amplasare[j][1] == 'V') {
			k = amplasare_poz[j][0] - 1;
			l = amplasare_poz[j][1];
			for (int i = amplasare_poz[j][0] - 1; i >= amplasare_poz[j][0] - 2;
				 i--) {
				if (rand == 1 && battleships_2[i][l - 1] != 'P') {
					battleships_2[i][l - 1] = 'x';
				} else if (rand == 2 && battleships_1[i][l - 1] != 'P') {
					battleships_1[i][l - 1] = 'x';
				}
			}
			printf(
				"Jucatorul %d a distrus o nava Laffey plasata intre "
				"coordonatele (%d, %d) si (%d, %d).\n",
				rand, amplasare_poz[j][0], amplasare_poz[j][1], k, l);
		}
	}

	if (amplasare[j][0] == 'A') {
		if (rand == 1 &&
			battleships_2[amplasare_poz[j][0] - 1][amplasare_poz[j][1] - 1] !=
				'P') {
			battleships_2[amplasare_poz[j][0] - 1][amplasare_poz[j][1] - 1] =
				'x';
		} else if (rand == 2 && battleships_1[amplasare_poz[j][0] - 1]
											 [amplasare_poz[j][1] - 1] != 'P') {
			battleships_1[amplasare_poz[j][0] - 1][amplasare_poz[j][1] - 1] =
				'x';
		}
		printf(
			"Jucatorul %d a distrus o nava Albacore plasata intre coordonatele "
			"(%d, %d) si (%d, %d).\n",
			rand, amplasare_poz[j][0], amplasare_poz[j][1], amplasare_poz[j][0],
			amplasare_poz[j][1]);
	}
}

int check_barca_lovita(int x, int y, char **battleships_1, char **battleships_2,
					   int rand) 
{
	if (rand == 1) {
		if (battleships_2[x - 1][y - 1] != 'P') {
			if (battleships_2[x - 1][y - 1] == '1') {
				battleships_2[x - 1][y - 1] = 'x';
				return 1;
			} else if (battleships_2[x - 1][y - 1] == '2') {
				battleships_2[x - 1][y - 1] = 'x';
				return 2;
			} else if (battleships_2[x - 1][y - 1] == '3') {
				battleships_2[x - 1][y - 1] = 'x';
				return 3;
			} else if (battleships_2[x - 1][y - 1] == '4') {
				battleships_2[x - 1][y - 1] = 'x';
				return 4;
			} else if (battleships_2[x - 1][y - 1] == '5') {
				battleships_2[x - 1][y - 1] = 'x';
				return 5;
			}
		}
	} else if (rand == 2) {
		if (battleships_1[x - 1][y - 1] != 'P') {
			if (battleships_1[x - 1][y - 1] == '1') {
				battleships_1[x - 1][y - 1] = 'x';
				return 1;
			} else if (battleships_1[x - 1][y - 1] == '2') {
				battleships_1[x - 1][y - 1] = 'x';
				return 2;
			} else if (battleships_1[x - 1][y - 1] == '3') {
				battleships_1[x - 1][y - 1] = 'x';
				return 3;
			} else if (battleships_1[x - 1][y - 1] == '4') {
				battleships_1[x - 1][y - 1] = 'x';
				return 4;
			} else if (battleships_1[x - 1][y - 1] == '5') {
				battleships_1[x - 1][y - 1] = 'x';
				return 5;
			}
		}
	}
	return 0;
}
int incadrare_caz(char cerinta[])
{
	if (cerinta[1] == 'U' && cerinta[11] == 'M' && cerinta[12] == 'I' &&
		cerinta[13] == 'N') {
		return 2;
	}
	if (cerinta[1] == 'U' && cerinta[11] == 'M' && cerinta[12] == 'A' &&
		cerinta[13] == 'X') {
		return 4;
	}
	if (cerinta[1] == 'T' && cerinta[11] == 'M' && cerinta[12] == 'I' &&
		cerinta[13] == 'N') {
		return 1;
	}
	if (cerinta[1] == 'T' && cerinta[11] == 'M' && cerinta[12] == 'A' &&
		cerinta[13] == 'X') {
		return 3;
	}
	return 0;
}

float calc_total(float auxiliar[], int j, float total_barci[])
{
	float acuratete_totala_1 = 0;
	float numarator_acuratete_1 = 0;
	float numitor_acuratete_1 = 0;
	for (int g = 0; g < j; g++) {
		numarator_acuratete_1 += auxiliar[g] * total_barci[g];
		numitor_acuratete_1 += total_barci[g];
	}
	acuratete_totala_1 = numarator_acuratete_1 / numitor_acuratete_1;
	return acuratete_totala_1;
}

int caz1(char cerinta[], float acuratete[], int j, float total_barci[])
{
	float tinta;
	sscanf(cerinta + 5, "%f", &tinta); 

	float castig[j];
	for (int i = 0; i < j; i++) {
		castig[i] = (1.0f - acuratete[i]) * total_barci[i];
	}

	int contor = 0;

	float total_puncte = 0;
	for (int i = 0; i < j; i++) total_puncte += acuratete[i] * total_barci[i];
	float total_barci_sum = 0;
	for (int i = 0; i < j; i++) total_barci_sum += total_barci[i];

	while ((total_puncte / total_barci_sum) * 100.0f < tinta) {
		int indice_max = -1;
		for (int i = 0; i < j; i++) {
			if (castig[i] > 0) {
				if (indice_max == -1 || castig[i] > castig[indice_max]) {
					indice_max = i;
				}
			}
		}

		if (indice_max == -1) break; 

		total_puncte += castig[indice_max];
		castig[indice_max] = 0;
		contor++;
	}

	return contor;
}
int caz2(char cerinta[], float nr_lovite[], float nr_totale[], int *meci)
{
	*meci =
		100 * (cerinta[2] - '0') + 10 * (cerinta[3] - '0') + (cerinta[4] - '0');
	float aux_nr_lovite = nr_lovite[*meci - 1];
	float aux_nr_totale = nr_totale[*meci - 1];
	float total = aux_nr_lovite / aux_nr_totale * 100;
	int count = 0;

	char aflare_numar[50];
	strcpy(aflare_numar, cerinta + 5);
	aflare_numar[6] = '\0';
	float goal = strtof(aflare_numar, NULL);

	while (total < goal && aux_nr_lovite < aux_nr_totale) {
		aux_nr_lovite++;
		float new_total = (aux_nr_lovite / aux_nr_totale) * 100;
		count++;
		if (new_total >= goal) 
			break;
		total = new_total;
	}

	return count;
}

int caz3(char cerinta[], float acuratete[], int j, float total_barci[])
{
	float tinta;
	sscanf(cerinta + 5, "%f", &tinta);

	double total_punct = 0.0;
	double total_barc = 0.0;
	for (int i = 0; i < j; i++) {
		total_punct += acuratete[i] * total_barci[i];
		total_barc += total_barci[i];
	}
	double puncte_tinta = tinta / 100.0 * total_barc;

	int contor = 0;
	int modificat[j];
	for (int i = 0; i < j; i++) 
	modificat[i] = 0;

	while (1) {
		int indice = -1;
		for (int i = 0; i < j; i++) {
			if (!modificat[i] && acuratete[i] > 0.0f) {
				if (indice == -1 || acuratete[i] * total_barci[i] <
										acuratete[indice] * total_barci[indice])
					indice = i;
			}
		}
		if (indice == -1) 
		break;  

		double punct_nou =
			total_punct - acuratete[indice] * total_barci[indice];
		if (punct_nou < puncte_tinta) 
		break;

		total_punct = punct_nou;
		modificat[indice] = 1;
		contor++;
	}

	return contor;
}

int caz4(char cerinta[], float nr_lovite[], float nr_totale[], int *meci)
{
	*meci =
		100 * (cerinta[2] - '0') + 10 * (cerinta[3] - '0') + (cerinta[4] - '0');
	float aux_nr_lovite = nr_lovite[*meci - 1];
	float aux_nr_totale = nr_totale[*meci - 1];
	float total = aux_nr_lovite / aux_nr_totale * 100;
	int count = 0;

	char aflare_numar[50];
	strcpy(aflare_numar, cerinta + 5);
	aflare_numar[6] = '\0';
	float goal = strtof(aflare_numar, NULL);

	while (total >= goal && aux_nr_lovite > 0) {
		aux_nr_lovite--; 
		float new_total =
			(aux_nr_lovite / aux_nr_totale) * 100;  
		if (new_total < goal) break;               
		count++;
		total = new_total;
	}

	return count;
}
int **minor(int **m, int **matrice, int linie, int coloana, int dim)
{
	int r = 0;
	for (int i = 0; i < dim + 1; i++) {
		if (i == linie) continue;
		int c = 0;
		for (int j = 0; j < dim + 1; j++) {
			if (j == coloana) continue;
			m[r][c++] = matrice[i][j];
		}
		r++;
	}
	return m;
}

int calcul_determinant(int **matrice, int dimensiune)
{
	int determinant = 0;
	if (dimensiune == 1) {
		return matrice[0][0];
	}
	if (dimensiune == 2) {
		return matrice[0][0] * matrice[1][1] - matrice[0][1] * matrice[1][0];
	}

	int newDim = dimensiune - 1;
	int **m = malloc(newDim * sizeof(int *));
	for (int i = 0; i < newDim; i++) m[i] = malloc(newDim * sizeof(int));

	for (int i = 0; i < dimensiune; i++) {
		determinant +=
			matrice[0][i] *
			calcul_determinant(minor(m, matrice, 0, i, dimensiune - 1),
							   dimensiune - 1) *
			int_pow(-1, i);
	}

	for (int i = 0; i < newDim; i++) free(m[i]);
	free(m);

	return determinant;
}

void citire_cheie(char *cheie)
{
	int dimensiune = 50; 
	int len = 0;
	int c;

	while ((c = getchar()) != EOF && c != '\n') {
		cheie[len++] = (char)c;
		if (len + 1 >= dimensiune) {
			dimensiune *= 2;
			char *tmp = realloc(cheie, dimensiune * sizeof(char));
			if (!tmp) {
				free(cheie);
			}
			//free(cheie);
			cheie = tmp;
		}
	}

	cheie[len] = '\0';
}
void citire_cerinta(char *cerinta)
{
	int dimensiune = 50; 
	int len = 0;
	while (1) {
		int c = getchar();
		if (c == EOF || c == '\n') break;

		cerinta[len++] = c;

		if (len + 1 >= dimensiune) { 
			dimensiune *= 2;
			char *tmp = realloc(cerinta, dimensiune);
			if (!tmp) {
				free(cerinta);
			}
			//free(cerinta);
			cerinta = tmp;
			free(tmp);
		}
	}

	cerinta[len] = '\0';
}
void transformare_cheie(char cheie[], int **cheie_mat)
{
	int j = 0;
	int c = 0;
	int numar_litera;
	for (long unsigned int i = 0; i < strlen(cheie); i++) {
		if (i % (int)int_sqrt(strlen(cheie)) == 0 && i != 0) {
			j++;
			c = 0;
		}
		if (cheie[i] >= 'A' && cheie[i] <= 'Z') {
			numar_litera = cheie[i] - 'A' + 10;
		} else if (cheie[i] >= '0' && cheie[i] <= '9') {
			numar_litera = cheie[i] - '0';
		} else if (cheie[i] == '.') {
			numar_litera = 36;
		}
		
		cheie_mat[j][c] = numar_litera;
		c++;
		
	}
}

void transformare_cerinta(char cerinta_aux[], int cerinta_vect[])
{
	int numar_litera;
	for (long unsigned int i = 0; i < strlen(cerinta_aux); i++) {
		if (cerinta_aux[i] >= 'A' && cerinta_aux[i] <= 'Z') {
			numar_litera = cerinta_aux[i] - 'A' + 10;
		} else if (cerinta_aux[i] >= '0' && cerinta_aux[i] <= '9') {
			numar_litera = cerinta_aux[i] - '0';
		} else if (cerinta_aux[i] == '.') {
			numar_litera = 36;
		}
		cerinta_vect[i] = numar_litera;
	}
}

int modulo(int a, int b)
{
	int rezultat = a % b;
	if (rezultat < 0) {
		rezultat += b;
	}
	return rezultat;
}

int invers_multiplicativ(int a, int b)
{
	for (int i = 1; i < 37; i++) {
		if ((a * i) % b == 1) {
			return i;
		}
	}
	return 0;
}
int **calcul_adjuncta(int **matrice_adjuncta, int **matrice, int dimensiune)
{


	int newDim = dimensiune - 1;
	int **m = malloc(newDim * sizeof(int *));
	for (int i = 0; i < newDim; i++) m[i] = malloc(newDim * sizeof(int));

	for (int i = 0; i < dimensiune; i++) {
		for (int j = 0; j < dimensiune; j++) {
			matrice_adjuncta[i][j] = modulo(
				(calcul_determinant(minor(m, matrice, i, j, dimensiune - 1),
									dimensiune - 1) *
				 int_pow(-1, i + j)),
				37);
		}
	}

	for (int i = 0; i < newDim; i++) free(m[i]);
	free(m);
	return matrice_adjuncta;
}

int **calcul_inversa(int **matrice_adjuncta, int **matrice_inversa,
					 int **matrice, int dimensiune)
{
	int determinant = calcul_determinant(matrice, dimensiune);
	int invers_determinant = invers_multiplicativ(modulo(determinant, 37), 37);

	matrice_adjuncta = calcul_adjuncta(matrice_adjuncta, matrice, dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		for (int j = 0; j < dimensiune; j++) {
			matrice_inversa[i][j] =
				modulo((matrice_adjuncta[j][i] * invers_determinant), 37);
		}
	}
	return matrice_inversa;
}

int inmultire_matrice(int **matrice_inversa, int cerinta_vect[], int dimensiune,
					  int rezultat_cerinta_numeric[])
{
	int index = 0;
	for (int j = 0; j < dimensiune; j++) {
		int suma = 0;
		for (int k = 0; k < dimensiune; k++) {
			suma += matrice_inversa[j][k] * cerinta_vect[k];
		}
		rezultat_cerinta_numeric[index++] = modulo(suma, 37);
	}
	return 0;
}

void decriptare_bucata(int **matrice_adjuncta, int **matrice_inversa,
					   char rezultat_cheie[], char rezultat_cerinta[],
					   int **cheie_mat, int cerinta_vect[], char *cheie,
					   char cerinta[], int *index) 
{
	int L = strlen(cerinta);
	int dim = (int)int_sqrt(strlen(cheie));

	transformare_cerinta(cerinta, cerinta_vect);
	transformare_cheie(cheie, cheie_mat);
	calcul_inversa(matrice_adjuncta, matrice_inversa, cheie_mat, dim);
	int rezultat_cerinta_numeric[L];
	inmultire_matrice(matrice_inversa, cerinta_vect, dim,
					  rezultat_cerinta_numeric);
	for (int i = 0; i < L; i++) {
		if (rezultat_cerinta_numeric[i] >= 10 &&
			rezultat_cerinta_numeric[i] <= 35)
			rezultat_cerinta[(*index)++] =
				'A' + (rezultat_cerinta_numeric[i] - 10);
		else if (rezultat_cerinta_numeric[i] >= 0 &&
				 rezultat_cerinta_numeric[i] <= 9)
			rezultat_cerinta[(*index)++] = '0' + rezultat_cerinta_numeric[i];
		else if (rezultat_cerinta_numeric[i] == 36)
			rezultat_cerinta[(*index)++] = '.';
	}
	rezultat_cerinta[*index] = '\0';
	strcpy(rezultat_cheie, "-");
}

void criptare_bucata(char rezultat_criptare[], int **cheie_mat,
					 int lacriptare_vect[], char cheie[], char lacriptare[],
					 int *index, int dimensiune) 
{
	int L = strlen(lacriptare);

	transformare_cerinta(lacriptare, lacriptare_vect);
	transformare_cheie(cheie, cheie_mat);

	int rezultat_criptare_numeric[L];

	for (int j = 0; j < dimensiune; j++) {
		int suma = 0;
		for (int k = 0; k < dimensiune; k++) {
			suma += cheie_mat[j][k] * lacriptare_vect[k];
		}
		rezultat_criptare_numeric[j] = modulo(suma, 37);
	}

	for (int i = 0; i < dimensiune; i++) {
		int x = rezultat_criptare_numeric[i];

		if (x >= 10 && x <= 35)
			rezultat_criptare[(*index)++] = 'A' + (x - 10);
		else if (x >= 0 && x <= 9)
			rezultat_criptare[(*index)++] = '0' + x;
		else if (x == 36)
			rezultat_criptare[(*index)++] = '.';
	}
}

int main(void) 
{
	int n, m, i, j, count_distruse_1 = 0, count_distruse_2 = 0, rand = 1,
					CONT = 0, hit, nr_barci, x, y, count_atacat = 0;
	char cuv1[15], cuv2[15];
	scanf("%d", &j);
	float nr_lovite_1[j], nr_lovite_2[j], total_barci[j], nr_ratate_1[j],
		nr_ratate_2[j];
	float nr_totale_1[j], nr_totale_2[j];
	float acuratete_1[j], acuratete_2[j];
	for (int w = 0; w < j; w++) {
		nr_lovite_1[w] = 0;
		nr_lovite_2[w] = 0;
		nr_ratate_1[w] = 0;
		nr_ratate_2[w] = 0;
		nr_totale_1[w] = 0;
		nr_totale_2[w] = 0;
		acuratete_1[w] = 0;
		acuratete_2[w] = 0;
	}
	for (int g = 0; g < j; g++) {
		count_distruse_1 = 0;
		count_distruse_2 = 0;
		rand = 1;
		scanf("%d %d", &n, &m);
		int nr_S = n * m / 70;
		int nr_Y = n * m / 55;
		int nr_B = n * m / 40;
		int nr_L = n * m / 30;
		int nr_A = n * m / 20;
		total_barci[g] = (nr_S + nr_Y + nr_B + nr_L + nr_A) * 2;
		char **battleships_1 = malloc(n * sizeof(char *));
		if (!battleships_1) {
			printf("Eroare\n");
			free(battleships_1);
			battleships_1 = NULL;
			return 0;
		}
		for (i = 0; i < n; i++) {
			battleships_1[i] = malloc(m * sizeof(char));
			if (!battleships_1[i]) {
				printf("Eroare\n");
				for (int c = 0; c < i; c++) {
					free(battleships_1[c]);
					battleships_1[c] = NULL;
				}
				free(battleships_1);
				battleships_1 = NULL;
				return 0;
			}
		}
		char **battleships_2 = malloc(n * sizeof(char *));
		if (!battleships_2) {
			printf("Eroare\n");
			free(battleships_2);
			battleships_2 = NULL;
			return 0;
		}
		for (i = 0; i < n; i++) {
			battleships_2[i] = malloc(m * sizeof(char));
			if (!battleships_2[i]) {
				printf("Eroare\n");
				for (int c = 0; c < i; c++) {
					free(battleships_2[c]);
					battleships_2[c] = NULL;
				}
				free(battleships_2);
				battleships_2 = NULL;
				return 0;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int c = 0; c < m; c++) {
				battleships_1[i][c] = '0';
			}
		}
		for (int i = 0; i < n; i++) {
			for (int c = 0; c < m; c++) {
				battleships_2[i][c] = '0';
			}
		}
		char **amplasare = malloc(total_barci[g] * sizeof(char *));
		if (!amplasare) {
			printf("Eroare\n");
			free(amplasare);
			amplasare = NULL;
			return 0;
		}
		for (i = 0; i < total_barci[g]; i++) {
			amplasare[i] = malloc(2 * sizeof(char));
			if (!amplasare[i]) {
				printf("Eroare\n");
				for (int c = 0; c < i; c++) {
					free(amplasare[c]);
					amplasare[c] = NULL;
				}
				free(amplasare);
				amplasare = NULL;
				return 0;
			}
		}
		int **amplasare_poz = malloc(total_barci[g] * sizeof(int *));
		if (!amplasare_poz) {
			printf("Eroare\n");
			free(amplasare_poz);
			amplasare_poz = NULL;
			return 0;
		}
		for (i = 0; i < total_barci[g]; i++) {
			amplasare_poz[i] = malloc(2 * sizeof(int));
			if (!amplasare_poz[i]) {
				printf("Eroare\n");
				for (int c = 0; c < i; c++) {
					free(amplasare_poz[c]);
					amplasare_poz[c] = NULL;
				}
				free(amplasare_poz);
				amplasare_poz = NULL;
				return 0;
			}
		}

		if (amplasare != NULL && amplasare_poz != NULL) {
			for (int c = 0; c < total_barci[g]; c++) {
				for (int k = 0; k < 2; k++) {
					scanf(" %c", &amplasare[c][k]);
				}
				for (int k = 0; k < 2; k++) {
					scanf(" %d", &amplasare_poz[c][k]);
				}

				if (amplasare[c][0] == 'S') {
					strcpy(cuv1, "Shinano");
				} else if (amplasare[c][0] == 'Y') {
					strcpy(cuv1, "Yamato");
				} else if (amplasare[c][0] == 'B') {
					strcpy(cuv1, "Belfast");
				} else if (amplasare[c][0] == 'L') {
					strcpy(cuv1, "Laffey");
				} else if (amplasare[c][0] == 'A') {
					strcpy(cuv1, "Albacore");
				}
				if (amplasare[c][1] == 'V') {
					strcpy(cuv2, "vertical");
				} else if (amplasare[c][1] == 'H') {
					strcpy(cuv2, "orizontal");
				}
				if (check_limite(amplasare, amplasare_poz, c, n, m) == 0) {
					printf(
						"Nava %s nu poate fi amplasata %s la coordonatele (%d, "
						"%d).\n",
						cuv1, cuv2, amplasare_poz[c][0], amplasare_poz[c][1]);
					c--;
				} else if (check_limite(amplasare, amplasare_poz, c, n, m) ==
						   1) {
					if (check_suprapuneri(amplasare, amplasare_poz,
										  battleships_1, battleships_2,
										  c) == 0) {
						printf(
							"Nava %s nu poate fi amplasata %s la coordonatele "
							"(%d, %d).\n",
							cuv1, cuv2, amplasare_poz[c][0],
							amplasare_poz[c][1]);
						c--;
					} else if (check_suprapuneri(amplasare, amplasare_poz,
												 battleships_1, battleships_2,
												 c) == 1) {
						construire_matrici(amplasare, amplasare_poz,
										   battleships_1, battleships_2, c);
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int c = 0; c < m; c++) {
				printf("%c ", battleships_1[i][c]);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < n; i++) {
			for (int c = 0; c < m; c++) {
				printf("%c ", battleships_2[i][c]);
			}
			printf("\n");
		}
		nr_barci = total_barci[g] / 2;
		for (int i = 0;
			 count_distruse_1 < nr_barci && count_distruse_2 < nr_barci; i++) {
			CONT = 0;
			count_atacat = 0;
			if (count_distruse_1 == nr_barci) {
				printf("Jucatorul 1 a castigat.\n");
				break;
			} else if (count_distruse_2 == nr_barci) {
				printf("Jucatorul 2 a castigat.\n");
				break;
			}

			scanf("%d %d", &x, &y);
			if (x <= 0 || x > n || y <= 0 || y > m) {
				if (rand == 1) {
					rand = 2;
				} else {
					rand = 1;
				}
				continue;
			}

			if (rand == 1) {
				if (battleships_2[x - 1][y - 1] == 'P') {
					printf(
						"Coordonatele (%d, %d) au fost deja atacate de "
						"jucatorul %d. \n",
						x, y, rand);
					nr_ratate_1[g]++;
					count_atacat = 1;
				}
				for (int l = 1; l < total_barci[g]; l += 2) {
					if (x == amplasare_poz[l][0] && y == amplasare_poz[l][1]) {
						if (count_atacat == 0) {
							afisare_barca_distrusa(amplasare, amplasare_poz,
												   battleships_1, battleships_2,
												   l, rand);
							nr_lovite_1[g]++;
							count_distruse_1++;
						}
						rand = 2;

						CONT++;
						battleships_2[x - 1][y - 1] = 'P';
					}
				}
				if (CONT == 1) {
					continue;
				}
				hit = check_barca_lovita(x, y, battleships_1, battleships_2,
										 rand);

				if (hit == 1) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Albacore la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 2) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Laffey la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 3) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Belfast la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 4) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Yamato la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 5) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Shinano la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 0) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a ratat o lovitura la coordonatele "
							"(%d, %d).\n",
							rand, x, y);
						nr_ratate_1[g]++;
					}
					rand = 2;
					battleships_2[x - 1][y - 1] = 'P';
					continue;
				}
			}

			if (rand == 2) {
				if (battleships_1[x - 1][y - 1] == 'P') {
					printf(
						"Coordonatele (%d, %d) au fost deja atacate de "
						"jucatorul %d.\n",
						x, y, rand);
					nr_ratate_2[g]++;
					count_atacat = 1;
				}
				for (int l = 0; l < total_barci[g]; l += 2) {
					if (x == amplasare_poz[l][0] && y == amplasare_poz[l][1]) {
						if (count_atacat == 0) {
							afisare_barca_distrusa(amplasare, amplasare_poz,
												   battleships_1, battleships_2,
												   l, rand);
							nr_lovite_2[g]++;
							count_distruse_2++;
						}
						rand = 1;
						CONT++;
						battleships_1[x - 1][y - 1] = 'P';
					}
				}
				if (CONT == 1) {
					continue;
				}
				hit = check_barca_lovita(x, y, battleships_1, battleships_2,
										 rand);
				if (hit == 1) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Albacore la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 2) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Laffey la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 3) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Belfast la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 4) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Yamato la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 5) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a lovit o nava Shinano la "
							"coordonatele (%d, %d).\n",
							rand, x, y);
						nr_lovite_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				} else if (hit == 0) {
					if (count_atacat == 0) {
						printf(
							"Jucatorul %d a ratat o lovitura la coordonatele "
							"(%d, %d).\n",
							rand, x, y);
						nr_ratate_2[g]++;
					}
					rand = 1;
					battleships_1[x - 1][y - 1] = 'P';
					continue;
				}
			}
		}

		if (count_distruse_1 == nr_barci) {
			printf("Jucatorul 1 a castigat.\n");
		} else if (count_distruse_2 == nr_barci) {
			printf("Jucatorul 2 a castigat.\n");
		}

		for (int i = 0; i < n; i++) {
			free(battleships_1[i]);

			free(battleships_2[i]);
		}
		free(battleships_1);

		free(battleships_2);

		for (int i = 0; i < total_barci[g]; i++) {
			free(amplasare[i]);

			free(amplasare_poz[i]);
		}
		free(amplasare);

		free(amplasare_poz);

	
		nr_totale_1[g] = nr_lovite_1[g] + nr_ratate_1[g];
		nr_totale_2[g] = nr_lovite_2[g] + nr_ratate_2[g];
		acuratete_1[g] = nr_lovite_1[g] / nr_totale_1[g];
		acuratete_2[g] = nr_lovite_2[g] / nr_totale_2[g];
	}
	int lungime_cheie = 50;
	int ch;
	while ((ch = getchar()) == '\n');
	if (ch != EOF) ungetc(ch, stdin);
	char *cheie = (char *)malloc(lungime_cheie * sizeof(char));
	citire_cheie(cheie);
	int dim = (int)int_sqrt(strlen(cheie));
	char rezultat_cheie[lungime_cheie];
	rezultat_cheie[0] = '\0';
	char rezultat_cerinta[100];
	rezultat_cerinta[0] = '\0';
	int meci;
	int index = 0;
	int facem_decriptarea = 0;
	float acuratete_totala_1 = 0, acuratete_totala_2 = 0;
	float numarator_acuratete_1 = 0, numarator_acuratete_2 = 0;
	float numitor_acuratete_1 = 0, numitor_acuratete_2 = 0;
	for (int g = 0; g < j; g++) {
		numarator_acuratete_1 += acuratete_1[g] * total_barci[g];
		numitor_acuratete_1 += total_barci[g];
		numarator_acuratete_2 += acuratete_2[g] * total_barci[g];
		numitor_acuratete_2 += total_barci[g];
	}
	acuratete_totala_1 = numarator_acuratete_1 / numitor_acuratete_1;
	acuratete_totala_2 = numarator_acuratete_2 / numitor_acuratete_2;
	if (strcmp(cheie, "-") != 0) {
		facem_decriptarea = 1;
	}
	char lacriptare[100];
	int counter_parcurgere_cerinta = 0;
	int **cheie_mat;
	while (strcmp(cheie, "Q") != 0) {
		index = 0;
		char *cerinta = malloc(50 * sizeof(char));
		citire_cerinta(cerinta);

		int **matrice_adjuncta = (int **)malloc(dim * sizeof(int *));
		int **matrice_inversa = (int **)malloc(dim * sizeof(int *));
		for (int i = 0; i < dim; i++) {
			matrice_adjuncta[i] = (int *)malloc(dim * sizeof(int));
			matrice_inversa[i] = (int *)malloc(dim * sizeof(int));
		}

		int cerinta_vect[strlen(cerinta)];
		char *cerinta_aux = (char *)malloc((dim + 1) * sizeof(cerinta));
		memset(cerinta_aux, 0, (dim + 1) * sizeof(int));
		if (strcmp(cerinta, "Q") == 0) {
		
			for (int t = 0; t < dim; t++) {
				free(matrice_adjuncta[t]);
				free(matrice_inversa[t]);
			}
			free(matrice_adjuncta);
			free(matrice_inversa);
			free(cerinta_aux);
			free(cerinta);
			break;
		}
		cheie_mat = malloc(dim * sizeof(int *));
		for (int i = 0; i < dim; i++) {
			cheie_mat[i] = malloc(dim * sizeof(int));
		}
		if (!cheie_mat) {
			printf("Eroare\n");
			free(cheie_mat);
			cheie_mat = NULL;
			return 0;
		}
		for (i = 0; i < int_sqrt(strlen(cheie)); i++) {
			if (!cheie_mat[i]) {
				printf("Eroare\n");
				for (int c = 0; c < i; c++) {
					free(cheie_mat[c]);
					cheie_mat[c] = NULL;
				}
			}
		}
		if (strcmp(cheie, "-") != 0) {
			for (long unsigned int i = 0; i < strlen(cerinta); i++) {
				cerinta_aux[counter_parcurgere_cerinta] = cerinta[i];

				if (counter_parcurgere_cerinta ==
					(int)int_sqrt(strlen(cheie)) - 1) {
					decriptare_bucata(matrice_adjuncta, matrice_inversa,
									  rezultat_cheie, rezultat_cerinta,
									  cheie_mat, cerinta_vect, cheie,
									  cerinta_aux, &index);

					counter_parcurgere_cerinta = 0;
					cerinta_aux[0] = '\0';

				} else {
					counter_parcurgere_cerinta++;
				}
			}
			cerinta_aux[counter_parcurgere_cerinta] = '\0';
			counter_parcurgere_cerinta = 0;
			if (cerinta_aux[0] != '\0') {
				int d = strlen(cerinta_aux);
				char cheie_aux[int_pow(d, 2)];
				memcpy(cheie_aux, cheie, int_pow(d, 2));
				cheie_aux[int_pow(d, 2)] = '\0';
				decriptare_bucata(matrice_adjuncta, matrice_inversa,
								  rezultat_cheie, rezultat_cerinta, cheie_mat,
								  cerinta_vect, cheie_aux, cerinta_aux, &index);

			}
		}
		if (strcmp(cheie, "-") == 0 && cerinta[0] == 'O' &&
			facem_decriptarea == 0) {
			int caz = incadrare_caz(cerinta);
			if (caz == 1) {
				int rezultat = caz1(cerinta, acuratete_1, j, total_barci);
				printf(
					"%06.2f.%d\n",
					(double)((int)((acuratete_totala_1 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 2) {
				int rezultat = caz2(cerinta, nr_lovite_1, nr_totale_1, &meci);
				printf("%06.2f.%d\n",
					   (double)((int)((acuratete_1[meci - 1] * 100) * 100) /
								100.0),
					   rezultat);
			} else if (caz == 3) {
				int rezultat = caz3(cerinta, acuratete_1, j, total_barci);
				printf(
					"%06.2f.%d\n",
					(double)((int)((acuratete_totala_1 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 4) {
				int rezultat = caz4(cerinta, nr_lovite_1, nr_totale_1, &meci);
				printf("%06.2f.%d\n",
					   (double)((int)((acuratete_1[meci - 1] * 100) * 100) /
								100.0),
					   rezultat);
			}
		} else if (strcmp(cheie, "-") == 0 && cerinta[0] == 'T' &&
				   facem_decriptarea == 0) {
			int caz = incadrare_caz(cerinta);
			if (caz == 1) {
				int rezultat = caz1(cerinta, acuratete_2, j, total_barci);
				printf(
					"%06.2f.%d\n",
					(double)((int)((acuratete_totala_2 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 2) {
				int rezultat = caz2(cerinta, nr_lovite_2, nr_totale_2, &meci);
				printf("%06.2f.%d\n",
					   (double)((int)((acuratete_2[meci - 1] * 100) * 100) /
								100.0),
					   rezultat);
			} else if (caz == 3) {
				int rezultat = caz3(cerinta, acuratete_2, j, total_barci);
				printf(
					"%06.2f.%d\n",
					(double)((int)((acuratete_totala_2 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 4) {
				int rezultat = caz4(cerinta, nr_lovite_2, nr_totale_2, &meci);
				printf("%06.2f.%d\n",
					   (double)((int)((acuratete_2[meci - 1] * 100) * 100) /
								100.0),
					   rezultat);
			}
		}
		if (strcmp(rezultat_cheie, "-") == 0 && rezultat_cerinta[0] == 'O' &&
			facem_decriptarea == 1) {
			int caz = incadrare_caz(rezultat_cerinta);
			if (caz == 1) {
				int rezultat =
					caz1(rezultat_cerinta, acuratete_1, j, total_barci);
				sprintf(
					lacriptare, "%06.2f.%d\n",
					(double)((int)((acuratete_totala_1 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 2) {
				int rezultat =
					caz2(rezultat_cerinta, nr_lovite_1, nr_totale_1, &meci);
				sprintf(lacriptare, "%06.2f.%d\n",
						(double)((int)((acuratete_1[meci - 1] * 100) * 100) /
								 100.0),
						rezultat);
			} else if (caz == 3) {
				int rezultat =
					caz3(rezultat_cerinta, acuratete_1, j, total_barci);
				sprintf(
					lacriptare, "%06.2f.%d\n",
					(double)((int)((acuratete_totala_1 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 4) {
				int rezultat =
					caz4(rezultat_cerinta, nr_lovite_1, nr_totale_1, &meci);
				sprintf(lacriptare, "%06.2f.%d\n",
						(double)((int)((acuratete_1[meci - 1] * 100) * 100) /
								 100.0),
						rezultat);
			}
		} else if (strcmp(rezultat_cheie, "-") == 0 &&
				   rezultat_cerinta[0] == 'T' && facem_decriptarea == 1) {
			int caz = incadrare_caz(rezultat_cerinta);

			if (caz == 1) {
				int rezultat =
					caz1(rezultat_cerinta, acuratete_2, j, total_barci);
				sprintf(
					lacriptare, "%06.2f.%d\n",
					(double)((int)((acuratete_totala_2 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 2) {
				int rezultat =
					caz2(rezultat_cerinta, nr_lovite_2, nr_totale_2, &meci);
				sprintf(lacriptare, "%06.2f.%d\n",
						(double)((int)((acuratete_2[meci - 1] * 100) * 100) /
								 100.0),
						rezultat);
			} else if (caz == 3) {
				int rezultat =
					caz3(rezultat_cerinta, acuratete_2, j, total_barci);
				sprintf(
					lacriptare, "%06.2f.%d\n",
					(double)((int)((acuratete_totala_2 * 100) * 100) / 100.0),
					rezultat);
			} else if (caz == 4) {
				int rezultat =
					caz4(rezultat_cerinta, nr_lovite_2, nr_totale_2, &meci);
				sprintf(lacriptare, "%06.2f.%d\n",
						(double)((int)((acuratete_2[meci - 1] * 100) * 100) /
								 100.0),
						rezultat);
			}
		}
		if (facem_decriptarea == 1) {
			index = 0;
			counter_parcurgere_cerinta = 0;
			char rezultat_criptare[200];
			int lacriptare_vect[200];
			char lacriptare_aux[strlen(lacriptare)];
			lacriptare[strlen(lacriptare) - 1] = '\0';
			for (long unsigned int i = 0; i < strlen(lacriptare); i++) {
				lacriptare_aux[counter_parcurgere_cerinta] = lacriptare[i];
				if (counter_parcurgere_cerinta ==
					(int)int_sqrt(strlen(cheie)) - 1) {
					lacriptare_aux[counter_parcurgere_cerinta + 1] = '\0';
					criptare_bucata(rezultat_criptare, cheie_mat,
									lacriptare_vect, cheie, lacriptare_aux,
									&index, dim);
					counter_parcurgere_cerinta = 0;
					lacriptare_aux[0] = '\0';
					memset(lacriptare_aux, 0, sizeof(lacriptare_aux));
				} else {
					counter_parcurgere_cerinta++;
				}
			}

			lacriptare_aux[strlen(lacriptare_aux)] = '\0';
			if (lacriptare_aux[0] != '\0') {
				if (lacriptare_aux[strlen(lacriptare_aux) - 1] == '\n')
					lacriptare_aux[strlen(lacriptare_aux) - 1] = '\0';

				lacriptare_aux[strlen(lacriptare_aux)] = '\0';
				int dl = strlen(lacriptare_aux);
				char cheie_aux2[int_pow(dl, 2)];
				memcpy(cheie_aux2, cheie, int_pow(dl, 2));
				cheie_aux2[int_pow(dl, 2)] = '\0';
				criptare_bucata(rezultat_criptare, cheie_mat, lacriptare_vect,
								cheie_aux2, lacriptare_aux, &index, dl);
				counter_parcurgere_cerinta = 0;
				lacriptare_aux[0] = '\0';
			}

			rezultat_criptare[index] = '\0';
			printf("%s\n", rezultat_criptare);

			memset(rezultat_criptare, 0, sizeof(rezultat_criptare));
		}
		for (int i = 0; i < dim; i++) {
			free(cheie_mat[i]);
		}
		free(cheie_mat);
		free(cerinta);
		for (int i = 0; i < dim; i++) {
			free(matrice_adjuncta[i]);
			free(matrice_inversa[i]);
		}
		free(matrice_adjuncta);
		free(matrice_inversa);
		free(cerinta_aux);
	}

	free(cheie);
	return 0;
}
