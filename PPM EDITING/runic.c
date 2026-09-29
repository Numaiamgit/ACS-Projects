// 311CB Gheorghe Alexandru-Nicolae
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define DIMENSIUNE 10000
#define ALOCARE_ESUATA -1

//Aici incep sa declar structurile folosite

struct lsystem {
	char *sursa;
	char *axioma;
	int num_reguli;
	char **reguli;
};

typedef struct {
	unsigned char r, g, b;
} pixel;

typedef struct {
	int latime, inaltime;
	pixel **data;
} image;

typedef struct {
	int n, r, g, b;
	double x, y, rotatie, pas_d, pas_u;
} pozitie_turtle;

typedef struct {
	image *img;
	struct lsystem *lsystem;
	char *confirmare;
	int undone;
	int nu_redo;
} istoricul;

//Aici incep functiile

//strdup pentru evitarea codului repetitiv
char *strdup(const char *s)
{
	if (!s) {
		return NULL;
	}
	size_t len = strlen(s);
	char *res = malloc(len + 1);
	if (!res) {
		perror("nu s-a executat alocarea\n");
		free(res);
		res = NULL;
		exit(ALOCARE_ESUATA);
	}

	if (res) {
		strcpy(res, s);
	}
	return res;
}

//functie de redimensionare
void *redimensionare(void *sursa, size_t dimensiune)
{
	void *tmp = realloc(sursa, dimensiune);

	if (!tmp) {
		perror("nu s-a alocat\n");
		free(tmp);
		tmp = NULL;
		exit(ALOCARE_ESUATA);
		return sursa;
	}
	return tmp;
}

//functie de citire a comenzilor
void citire_comanda(char **comanda)
{
	int dimensiune = DIMENSIUNE;
	int len = 0;
	int c;

	while ((c = getchar()) != EOF && c != '\n') {
		(*comanda)[len++] = (char)c;

		//lungimea poate varia(foloseste alocare dinamica)
		if (len + 1 >= dimensiune) {
			dimensiune *= 2;
			*comanda = realloc(*comanda, dimensiune);
			if (!comanda) {
				perror("nu s-a executat alocarea\n");
				free(comanda);
				comanda = NULL;
				exit(ALOCARE_ESUATA);
				return;
			}
		}
	}
	(*comanda)[len] = '\0';
}

//Functie pentru citirea din fisierele lsystem
void citire_fisier(char *dest, FILE *file)
{
	int dimensiune = DIMENSIUNE;
	int len = 0;
	int c;

	while ((c = fgetc(file)) != EOF && c != '\n') {
		if (c == '\r') {
			continue;
		}
		dest[len++] = (char)c;
		if (len + 1 > dimensiune) {
			dimensiune *= 2;
			dest = redimensionare(dest, dimensiune);
		}
	}

	dest[len++] = '\0';
}

// Functie clean pentru eliberarea memoriei ocupata de lsystem si evitarea
// codului repetitiv
void cleanlsystem(struct lsystem *lsystem)
{
	if (!lsystem) {
		return;
	}

	free(lsystem->sursa);
	free(lsystem->axioma);
	for (int i = 0; i < 256; i++) {
		if (lsystem->reguli[i]) {
			free(lsystem->reguli[i]);
		}
	}

	free(lsystem->reguli);
	free(lsystem);
}

// Functie clean pentru eliberarea memoriei ocupata de imagine si evitarea
// codului repetitiv
void cleanimage(image *img)
{
	if (!img) {
		return;
	}
	for (int y = 0; y < img->inaltime; y++) {
		free(img->data[y]);
	}
	free(img->data);
	free(img);
}

// Functie clean pentru eliberarea memoriei ocupata de istoric si evitarea
// codului repetitiv
void cleanistoric(int de_la, int pana_la, istoricul istoric[])
{
	for (int i = de_la; i < pana_la; i++) {
		if (istoric[i].lsystem) {
			cleanlsystem(istoric[i].lsystem);
			istoric[i].lsystem = NULL;
		}
		if (istoric[i].img) {
			cleanimage(istoric[i].img);
			istoric[i].img = NULL;
		}
		if (istoric[i].confirmare) {
			free(istoric[i].confirmare);
			istoric[i].confirmare = NULL;
		}
	}
}

// Functie de load pentru lsystems
void setlsystem(struct lsystem **lsystem, char *sourcefile)
{
	FILE *file = fopen(sourcefile, "rb");
	if (!file) {
		printf("Failed to load %s\n", sourcefile);
		return;
	}
	if (*lsystem) {
		cleanlsystem(*lsystem);
	}
	*lsystem = malloc(sizeof(struct lsystem));
	if (!lsystem) {
		perror("nu s-a executat alocarea\n");
		cleanlsystem(*lsystem);
		lsystem = NULL;
		exit(ALOCARE_ESUATA);
	}
	(*lsystem)->sursa = malloc((strlen(sourcefile) + 1) * sizeof(char));
	if (!(*lsystem)->sursa) {
		perror("nu s-a executat alocarea\n");
		free((*lsystem)->sursa);
		cleanlsystem(*lsystem);
		(*lsystem)->sursa = NULL;
		exit(ALOCARE_ESUATA);
	}
	(*lsystem)->sursa[0] = '\0';
	strcpy((*lsystem)->sursa, sourcefile);
	(*lsystem)->axioma = malloc(DIMENSIUNE * sizeof(char));
		if (!(*lsystem)->axioma) {
			perror("nu s-a executat alocarea\n");
			free((*lsystem)->axioma);
			cleanlsystem(*lsystem);
			(*lsystem)->axioma = NULL;
			exit(ALOCARE_ESUATA);
		}
	(*lsystem)->axioma[0] = '\0';
	citire_fisier((*lsystem)->axioma, file);
	char *numar_reguli = malloc(DIMENSIUNE * sizeof(char));
	if (!numar_reguli) {
		perror("nu s-a executat alocarea\n");
		free(numar_reguli);
		numar_reguli = NULL;
		exit(ALOCARE_ESUATA);
	}
	numar_reguli[0] = '\0';
	citire_fisier(numar_reguli, file);
	(*lsystem)->num_reguli = atoi(numar_reguli);
	(*lsystem)->reguli = calloc(256, sizeof(char *));
	if (!(*lsystem)->reguli) {
		perror("nu s-a executat alocarea\n");
		free((*lsystem)->reguli);
		(*lsystem)->reguli = NULL;
		exit(ALOCARE_ESUATA);
	}
	for (int idx = 0; idx < (*lsystem)->num_reguli; idx++) {
		char *line = malloc(DIMENSIUNE * sizeof(char));
		if (!line) {
			perror("nu s-a executat alocarea\n");
			free(line);
			line = NULL;
			exit(ALOCARE_ESUATA);
		}
		line[0] = '\0';
		citire_fisier(line, file);
		char simbol = line[0];
		(*lsystem)->reguli[(int)simbol] = malloc(strlen(line) *
			sizeof(char));
		if (!(*lsystem)->reguli[(int)simbol]) {
			perror("nu s-a executat alocarea\n");
			free((*lsystem)->reguli[(int)simbol]);
			(*lsystem)->reguli[(int)simbol] = NULL;
			exit(ALOCARE_ESUATA);
		}
		(*lsystem)->reguli[(int)simbol][0] = '\0';
		strcpy((*lsystem)->reguli[(int)simbol], line + 2);
		int len = strlen((*lsystem)->reguli[(int)simbol]);
		(*lsystem)->reguli[(int)simbol][len] = '\0';
		free(line);
	}
	free(numar_reguli);
	fclose(file);
}

// Functie load pentru imagini
image *load_ppm(const char *filename)
{
	FILE *f = fopen(filename, "rb");

	if (!f) {
		return NULL;
	}

	char format[3];

	// Citeste formatul(prima linie)
	if (fscanf(f, "%2s", format) != 1 || strcmp(format, "P6") != 0) {
		fclose(f);
		return NULL;
	}

	int latime, inaltime, maxval;

	if (fscanf(f, "%d %d %d", &latime, &inaltime, &maxval) != 3) {
		fclose(f);
		return NULL;
	}
	fgetc(f);

	image *img = malloc(sizeof(image));
	if (!img) {
		perror("nu s-a finalizat alocarea\n");
		free(img);
		img = NULL;
		exit(ALOCARE_ESUATA);
	}

	img->latime = latime; img->inaltime = inaltime;
	img->data = malloc(inaltime * sizeof(pixel *));
	if (!img->data) {
		perror("nu s-a finalizat alocarea\n");
		free(img->data);
		img->data = NULL;
		exit(ALOCARE_ESUATA);
	}
	for (int y = 0; y < inaltime; y++) {
		img->data[y] = malloc(latime * sizeof(pixel));
		if (!img->data[y]) {
			perror("nu s-a finalizat alocarea\n");
			free(img->data[y]);
			img->data[y] = NULL;
			exit(ALOCARE_ESUATA);
	}
	}
	// Aici se citeste matricea de pixeli
	for (int y = inaltime - 1; y >= 0; y--) {
		fread(img->data[y], sizeof(pixel), latime, f);
	}
	fclose(f);
	return img;
}

// Salveaza imaginea cu ajutorul caii date la parametru
void save_ppm(image *img, const char *filename)
{
	if (!img) {
		return;
	}
	FILE *f = fopen(filename, "wb");

	if (!f) {
		return;
	}
	fprintf(f, "P6\n%d %d\n255\n", img->latime, img->inaltime);
	for (int y = img->inaltime - 1; y >= 0; y--) {
		fwrite(img->data[y], 3, img->latime, f);
	}
	fclose(f);
}

// Aici incep functiile deepcopy(functioneaza pe structuri)
// Le-am folosit pentru a trece de la o stare la alta
struct lsystem *deepcopylsystem(struct lsystem *lsystem)
{
	struct lsystem *backup = NULL;

	if (!lsystem) {
		return NULL;
	}
	backup = malloc(sizeof(struct lsystem));
	if (!backup) {
		perror("nu s-a executat alocarea\n");
		free(backup);
		backup = NULL;
		exit(ALOCARE_ESUATA);
	}
	backup->sursa = malloc((strlen(lsystem->sursa) + 1) * sizeof(char));
	if (!backup->sursa) {
		perror("nu s-a executat alocarea\n");
		free(backup->sursa);
		backup->sursa = NULL;
		exit(ALOCARE_ESUATA);
	}
	strcpy(backup->sursa, lsystem->sursa);
	backup->axioma = malloc((strlen(lsystem->axioma) + 1) * sizeof(char));
	if (!backup->axioma) {
		perror("nu s-a executat alocarea\n");
		free(backup->axioma);
		backup->axioma = NULL;
		exit(ALOCARE_ESUATA);
	}
	strcpy(backup->axioma, lsystem->axioma);
	backup->num_reguli = lsystem->num_reguli;
	backup->reguli = malloc(256 * sizeof(char *));
	if (!backup->reguli) {
		perror("nu s-a executat alocarea\n");
		free(backup->reguli);
		backup->reguli = NULL;
		exit(ALOCARE_ESUATA);
	}
	for (int i = 0; i < 256; i++) {
		if (lsystem->reguli[i]) {
			backup->reguli[i] = malloc((strlen(lsystem->reguli[i]) + 1) *
										sizeof(char));
			if (!backup->reguli[i]) {
				perror("nu s-a executat alocarea\n");
				free(backup->reguli[i]);
				backup->reguli[i] = NULL;
				exit(ALOCARE_ESUATA);
			}
			strcpy(backup->reguli[i], lsystem->reguli[i]);
			continue;
		}
		backup->reguli[i] = NULL;
	}
	return backup;
}

image *deepcopyimage(image *img)
{
	if (!img) {
		return NULL;
	}
	image *copie = malloc(sizeof(image));
	if (!copie) {
		perror("nu s-a executat alocarea\n");
		free(copie);
		copie = NULL;
		exit(ALOCARE_ESUATA);
	}

	copie->latime = img->latime;
	copie->inaltime = img->inaltime;
	copie->data = malloc(copie->inaltime * sizeof(pixel *));
		if (!copie->data) {
			perror("nu s-a executat alocarea\n");
			free(copie->data);
			copie->data = NULL;
			exit(ALOCARE_ESUATA);
		}
	for (int y = 0; y < copie->inaltime; y++) {
		copie->data[y] = malloc(copie->latime * sizeof(pixel));
		if (!copie->data) {
			perror("nu s-a executat alocarea\n");
			free(copie->data);
			copie->data = NULL;
			exit(ALOCARE_ESUATA);
		}
		for (int x = 0; x < copie->latime; x++) {
			copie->data[y][x] = img->data[y][x];
		}
	}
	return copie;
}

char *derivarelsystem(struct lsystem *lsystem, char *cerinta_derivare,
					  char *rez)
{
	int n = atoi(cerinta_derivare);

	for (int d = 0; d < n; d++) {
		size_t nou_dim = DIMENSIUNE;
		size_t nou_len = 0;
		char *nou = malloc(nou_dim);
		if (!nou) {
			perror("nu s-a alocat\n");
			free(nou);
			nou = NULL;
			exit(ALOCARE_ESUATA);
		}

		nou[0] = '\0';
		for (size_t i = 0; rez[i]; i++) {
			char *rule = lsystem->reguli[(unsigned char)rez[i]];
			char *append = rule ? rule : (char[]){rez[i], '\0'};
			size_t rlen = strlen(append);

			while (nou_len + rlen + 1 >= nou_dim) {
				nou_dim *= 2;
				nou = realloc(nou, nou_dim);
				if (!nou) {
					perror("nu s-a alocat\n");
					free(nou);
					nou = NULL;
					exit(ALOCARE_ESUATA);
				}
			}
			strcpy(nou + nou_len, append);
			nou_len += rlen;
		}
		free(rez);
		rez = nou;
	}
	return rez;
}

//--------------------------------------------

// Algoritmul Bresenham(parametrii sunt afllati cu ajutorul altei functii)
void draw_line(image *img, int x0, int y0, int x1, int y1, pixel c)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1) {
		if (x0 >= 0 && x0 < img->latime && y0 >= 0 && y0 < img->inaltime) {
			img->data[y0][x0] = c;
		}
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			err += dx;
			y0 += sy;
		}
	}
}

// Aici se afla coordonatele pentru Bresenham
void coord_linie_turtle(image *img, char *comanda, pozitie_turtle pozitie)
{
	if (!img || !comanda) {
		return;
	}
	int len = strlen(comanda);
	pozitie_turtle *stiva = malloc(len * sizeof(pozitie_turtle));

	// Stiva pentru starile testoasei
	if (!stiva) {
		perror("nu s-a alocat\n");
		free(stiva);
		stiva = NULL;
		exit(ALOCARE_ESUATA);
	}
	int top = 0;
	double cur_x = pozitie.x;
	double cur_y = pozitie.y;
	double unghi = pozitie.rotatie;
	pixel culoare = { (unsigned char)pozitie.r,
					 (unsigned char)pozitie.g, (unsigned char)pozitie.b };

	for (int i = 0; comanda[i]; i++) {
		if (comanda[i] == 'F') {
			// Transformare in radiani
			double rad = unghi * 3.14159265358979323846 / 180.0;
			double urm_x = cur_x + (double)pozitie.pas_d * cos(rad);
			double urm_y = cur_y + (double)pozitie.pas_d * sin(rad);

			// Rotunjeste pentru a trimite pozitiile ca parametri
			int x0 = (int)round(cur_x);
			int y0 = (int)round(cur_y);
			int x1 = (int)round(urm_x);
			int y1 = (int)round(urm_y);
			draw_line(img, x0, y0, x1, y1, culoare);
			cur_x = urm_x;
			cur_y = urm_y;
		} else if (comanda[i] == '+') {
			unghi += pozitie.pas_u;
		} else if (comanda[i] == '-') {
			unghi -= pozitie.pas_u;
		} else if (comanda[i] == '[') {
			stiva[top].x = cur_x;
			stiva[top].y = cur_y;
			stiva[top].rotatie = unghi;
			top++;
		} else if (comanda[i] == ']') {
			if (top > 0) {
				top--;
				cur_x = stiva[top].x;
				cur_y = stiva[top].y;
				unghi = stiva[top].rotatie;
			}
		}
	}
	free(stiva);
}

// Logica de copiere a starii anterioare pentru redo
void cautare_confirmare(istoricul *istoric, int i, int indice_stare)
{
		cleanlsystem(istoric[indice_stare].lsystem);
		istoric[indice_stare].lsystem = deepcopylsystem(istoric[i].lsystem);
		istoric[indice_stare].img = deepcopyimage(istoric[i].img);

}

// Interpretare a comenzii pentru a folosi switch in main
int interpretare(char *comanda)
{
	if (strcmp(comanda, "EXIT") == 0) {
		return 0;
	} else if (strncmp(comanda, "LSYSTEM", 7) == 0) {
		return 1;
	} else if (strncmp(comanda, "DERIVE", 6) == 0) {
		return 2;
	} else if (strncmp(comanda, "UNDO", 4) == 0) {
		return 3;
	} else if (strncmp(comanda, "REDO", 4) == 0) {
		return 4;
	} else if (strncmp(comanda, "LOAD", 4) == 0) {
		return 5;
	} else if (strncmp(comanda, "SAVE", 4) == 0) {
		return 6;
	} else if (strncmp(comanda, "TURTLE", 6) == 0) {
		return 7;
	}
	return -1;
}

// Tratarea cazurilor de la comenzi pentru modularizarea codului
int lsys_caz(int *indice_stare, istoricul istoric[], char *comanda,
			 int *max_stare)
{
	int prev_idx = *indice_stare;

	*indice_stare = *max_stare + 1;
	cleanistoric(*indice_stare + 1, DIMENSIUNE, istoric);
	cleanlsystem(istoric[*indice_stare].lsystem);
	istoric[*indice_stare].lsystem = NULL;
	free(istoric[*indice_stare].confirmare);
	istoric[*indice_stare].confirmare = malloc(DIMENSIUNE);
	if (!istoric[*indice_stare].confirmare) {
		perror("nu s-a alocat\n");
		free(istoric[*indice_stare].confirmare);
		istoric[*indice_stare].confirmare = NULL;
		exit(ALOCARE_ESUATA);
	}
	setlsystem(&istoric[*indice_stare].lsystem, comanda + 8);
	if (!istoric[*indice_stare].lsystem) {
		return -1;
	}
	if (*indice_stare > 0 && istoric[prev_idx].img) {
		cleanimage(istoric[*indice_stare].img);
		istoric[*indice_stare].img = deepcopyimage(istoric[prev_idx].img);
	}
	printf("Loaded %s (L-system with %d rules)\n", comanda + 8,
		   istoric[*indice_stare].lsystem->num_reguli);
	sprintf(istoric[*indice_stare].confirmare,
			"Loaded %s (L-system with %d rules)\n",
			comanda + 8, istoric[*indice_stare].lsystem->num_reguli);
	for (int i = 0; i < *indice_stare; i++) {
		if (istoric[i].undone == 1) {
			// nu_redo tine minte daca o stare undone
			// poate fi refacuta prin redo sau ramane doar undone si la alte
			// undo-uri trebuie sarita
			istoric[i].nu_redo = 1;
		}
	}
	return 0;
}

int load_caz(int *indice_stare, istoricul istoric[], char *comanda,
			 int *max_stare)
{
	cleanistoric(*indice_stare + 1, DIMENSIUNE, istoric);
	int prev_idx = *indice_stare;

	*indice_stare = *max_stare + 1;
	cleanimage(istoric[*indice_stare].img);
	free(istoric[*indice_stare].confirmare);
	istoric[*indice_stare].confirmare = malloc(DIMENSIUNE);
	if (!istoric[*indice_stare].confirmare) {
		perror("nu s-a alocat\n");
		free(istoric[*indice_stare].confirmare);
		istoric[*indice_stare].confirmare = NULL;
		exit(ALOCARE_ESUATA);
	}
	istoric[*indice_stare].lsystem = deepcopylsystem(istoric[prev_idx].lsystem);
	istoric[*indice_stare].img = load_ppm(comanda + 5);
	if (istoric[*indice_stare].img) {
		printf("Loaded %s (PPM image %dx%d)\n", comanda + 5,
			   istoric[*indice_stare].img->latime,
			   istoric[*indice_stare].img->inaltime);
		sprintf(istoric[*indice_stare].confirmare,
				"Loaded %s (PPM image %dx%d)\n", comanda + 5,
				istoric[*indice_stare].img->latime,
				istoric[*indice_stare].img->inaltime);
	} else {
		printf("Failed to load %s\n", comanda + 5);
		sprintf(istoric[*indice_stare].confirmare,
				"Failed to load %s\n", comanda + 5);
		return -1;
	}
	return 0;
}

int turtle_caz(int *indice_stare, istoricul istoric[], char *comanda,
			   int *max_stare)
{
	if (!istoric[*indice_stare].img || !istoric[*indice_stare].lsystem) {
		if (!istoric[*indice_stare].img) {
			printf("No image loaded\n");
		} else {
			printf("No L-system loaded\n");
		}
		return -1;
	}
	int prev_idx = *indice_stare;

	*indice_stare = *max_stare + 1;
	cleanistoric(*indice_stare, *indice_stare, istoric);
	istoric[*indice_stare].img = deepcopyimage(istoric[prev_idx].img);
	istoric[*indice_stare].confirmare = malloc(DIMENSIUNE);
	if (!istoric[*indice_stare].confirmare) {
		perror("nu s-a alocat\n");
		free(istoric[*indice_stare].confirmare);
		istoric[*indice_stare].confirmare = NULL;
		exit(ALOCARE_ESUATA);
	}
	istoric[*indice_stare].lsystem = deepcopylsystem(istoric[prev_idx].lsystem);
	pozitie_turtle initial;
	if (sscanf(comanda + 7, "%lf %lf %lf %lf %lf %d %d %d %d",
			   &initial.x,
			   &initial.y,
			   &initial.pas_d,
			   &initial.rotatie,
			   &initial.pas_u,
			   &initial.n,
			   &initial.r,
			   &initial.g,
			   &initial.b) == 9) {
	}
	char n_str[15];

	sprintf(n_str, "%d", initial.n);
	char *turtle_string = strdup(istoric[*indice_stare].lsystem->axioma);

	turtle_string = derivarelsystem(istoric[*indice_stare].lsystem,
									n_str, turtle_string);
	coord_linie_turtle(istoric[*indice_stare].img, turtle_string, initial);
	printf("Drawing done\n");

	//se tin minte confirmarile pentru a le reafisa la redo
	sprintf(istoric[*indice_stare].confirmare, "Drawing done\n");

	free(turtle_string);
	*max_stare = *indice_stare;
	for (int i = 0; i < *indice_stare; i++) {
		if (istoric[i].undone == 1) {
			istoric[i].nu_redo = 1;
		}
	}
	return 0;
}

int redo_caz(int *indice_stare, istoricul istoric[], int *max_stare,
			 int *undone)
{
	*undone = 0;
	*indice_stare = *max_stare + 1;
	for (int i = 0; i <= *max_stare; i++) {
		if (istoric[i].undone) {
			*undone = 1;
			if (istoric[i].nu_redo) {
				// aici verifica nu_redo in caz ca a fost executata o
				// comanda undo-able intre undo si redo
				*undone = 0;
				continue;
			}
			istoric[i].undone = 0;
			cautare_confirmare(istoric, i, *indice_stare);
			istoric[*indice_stare].undone = 0;
			free(istoric[*indice_stare].confirmare);
			istoric[*indice_stare].confirmare =
				strdup(istoric[i].confirmare);
			printf("%s", istoric[*indice_stare].confirmare);
			*max_stare = *indice_stare;
			break;
		}
	}
	return 0;
}

int derive_caz(int *indice_stare, istoricul istoric[], char *comanda)
{
	if (!istoric[*indice_stare].lsystem) {
		printf("No L-system loaded\n");
		return -1;
	}
	char *rezultat_derivare =
		strdup(istoric[*indice_stare].lsystem->axioma);

	rezultat_derivare = derivarelsystem(istoric[*indice_stare].lsystem,
										comanda + 7, rezultat_derivare);
	printf("%s\n", rezultat_derivare);
	free(rezultat_derivare);
	return 0;
}

int undo_caz(int *indice_stare, istoricul istoric[])
{
	if (*indice_stare <= 0) {
		printf("Nothing to undo\n");
	} else {
		istoric[*indice_stare].undone = 1;
		for (int i = *indice_stare - 1; i >= 0; i--) {
			if (istoric[i].undone == 0) {
				*indice_stare = i;
				break;
			}
		}
	}
	return 0;
}

// Istoricul se poate redimensiona in cazul in care sunt foarte multe stari
// adaugate
void redim_istoric(istoricul **istoric, int *dim_ist)
{
	*dim_ist *= 2;
	istoricul *tmp = realloc(*istoric, *dim_ist * sizeof(istoricul));
	if (!tmp) {
		perror("nu se poate realoca");
		free(tmp);
		tmp = NULL;
		exit(ALOCARE_ESUATA);
	}
	*istoric = tmp;
	free(tmp);
}

// Regula pentru cod defensiv
void fail_istoric(void *istoric)
{
		perror("nu s-a executat alocarea\n");
		free(istoric);
		istoric = NULL;
		exit(ALOCARE_ESUATA);
}

int main(void)
{
	istoricul *istoric = calloc(DIMENSIUNE, sizeof(istoricul));
	if (!istoric) {
		fail_istoric(istoric);
	}
	int indice_stare = 0;
	int undone = 0;
	int max_stare = 0;
	int dim_ist = DIMENSIUNE;
	char *comanda = malloc(DIMENSIUNE * sizeof(char));
	if (!comanda) {
		fail_istoric(comanda);
	}
	while (1) {
		if (indice_stare == DIMENSIUNE)
			redim_istoric(&istoric, &dim_ist);
		citire_comanda(&comanda);
		int tip = interpretare(comanda);
		if (tip == 0) {
			break;
		}
		switch (tip) {
		case 1:
			if (lsys_caz(&indice_stare, istoric, comanda,
						 &max_stare) == -1) {
				indice_stare--;
			}
			max_stare = indice_stare;
			break;
		case 2: // DERIVE
			derive_caz(&indice_stare, istoric, comanda);
			break;
		case 3: // UNDO
			undo_caz(&indice_stare, istoric);
			break;
		case 4: // REDO
			redo_caz(&indice_stare, istoric, &max_stare, &undone);
			if (!undone) {
				indice_stare--;
				printf("Nothing to redo\n");
			}
			break;
		case 5: // LOAD (image)
			if (load_caz(&indice_stare, istoric, comanda,
						 &max_stare) == -1) {
				indice_stare--;
			}
			max_stare = indice_stare;
			break;
		case 6: // SAVE
			if (!istoric[indice_stare].img) {
				printf("No image loaded\n");
				break;
			}
			save_ppm(istoric[indice_stare].img, comanda + 5);
			printf("Saved %s\n", comanda + 5);
			break;
		case 7: // TURTLE
			if (turtle_caz(&indice_stare, istoric, comanda,
						   &max_stare) == -1) {
				break;
			}
			undone = 0;
			break;
		}
	}
	free(comanda);
	cleanistoric(0, DIMENSIUNE, istoric);
	free(istoric);
	return 0;
}

