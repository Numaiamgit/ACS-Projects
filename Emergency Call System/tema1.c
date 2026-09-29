//GHEORGHE Alexandru-Nicolae - 311CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _COADA_DINAMICA_

//definirea structurilor exact ca in cerinta
typedef struct unit
{
    int id;
    char type;
    int availability;
} TUnitate;

typedef struct incident
{
    int id;
    char priority[7];
    char *description;
    char status[11];
} TIncident;

typedef struct intervention
{
    TIncident *incident;
    TUnitate *unit;
} TInterventie;

//am scris structura de system insa nu am folosit-o
//probabil ar fi fost mai usor la trimiterea parametrilor daca o foloseam
typedef struct system
{
    struct unit *units;
    struct incident *incidents;
    struct intervention *interventions;
} TSystem;

//aici am ales sa fac implem separata pentru fiecare tip de
//lista/coada/stiva
typedef struct celula1 {
    TIncident info;
    struct celula1 *pre, *urm;
} TCelula2_incident, *TL2_incident;

typedef struct celula2 {
    TInterventie info;
    struct celula2 *pre, *urm;
} TCelula2_interventie, *TL2_interventie;

typedef struct celula3 {
    TUnitate *unitate;
    struct celula3 *urm;
} TCelula2_unitate, *TL2_unitate;

typedef struct stiva
{
    TL2_interventie *pointeri_coada;
    TL2_interventie *sf;
} TStiva_interventie;

typedef struct coada2
{
    TL2_incident *pointeri_coada;
    TL2_incident *inc, *sf;
} TCoada_incident;

typedef struct coada3
{
    TL2_unitate sf;
} TCoada_unitate;

//aici incep functiile care ajuta la modificarea/initializarea/distrugerea
//interventiilor
TL2_interventie AlocCelula_interventie(TInterventie x)
{
    TL2_interventie aux = (TL2_interventie)malloc(sizeof(TCelula2_interventie));
    if (!aux)
        return NULL;

    aux->info = x;
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

TL2_interventie InitLista_interventie()
{
    TL2_interventie aux = (TL2_interventie)malloc(sizeof(TCelula2_interventie));
    if (!aux)
        return NULL;

    aux->pre = aux;
    aux->urm = aux;

    return aux;
}

TL2_interventie CitireLista_interventie(TL2_interventie s, TInterventie x)
{
    TL2_interventie aux, ultim;
    if (!s)
        return 0;

    ultim = s->pre;
    aux = AlocCelula_interventie(x);
    if (!aux)
        return 0;

    aux->pre = ultim;
    aux->urm = ultim->urm;
    ultim->urm->pre = aux;
    ultim->urm = aux;

    ultim = aux;
    return aux;
}

void DistrugeLista_interventie(TL2_interventie *s)
{
    TL2_interventie p = (*s)->urm, aux;
    while (p != *s) {
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*s);
    *s = NULL;
}


//aici se initialieaza stiva (se aloca memorie si se seteaza sf ca NULL)
TStiva_interventie *InitS_interventie(void)
{
    TStiva_interventie *c;
    c = (TStiva_interventie *)malloc(sizeof(TStiva_interventie));
    if (!c)
        return NULL;
    c->sf = NULL;
    return c;
}

//Aici se aloca memorie pentru pointeri_coada(care e practic un vector de
// pointeri la interventii) si se seteaza sf la inceputul acestuia
void InitStiva(TStiva_interventie *q, int initial_size)
{
    q->pointeri_coada = (TL2_interventie *)malloc(initial_size * sizeof(TL2_interventie));
    q->sf = q->pointeri_coada;
}

//Functia asta verifica daca stiva e plina si realoca in cazul in care este
//apoi adauga interventia in varful stivei
//pentru realocare se calculeaza offset-ul pentru sf, apoi se realoca si
// se seteaza sf la noua adresa + offset
void Introducere_stiva_interventie(TStiva_interventie *q, TL2_interventie s, int *current_cap)
{
    if (q->sf == q->pointeri_coada + (*current_cap)) {
        int offset_sf = q->sf - q->pointeri_coada;
        *current_cap *= 2;
        q->pointeri_coada = realloc(q->pointeri_coada, (*current_cap) * sizeof(TL2_interventie));
        q->sf = q->pointeri_coada + offset_sf;
    }

    *q->sf = s;
    q->sf++;
}

//Verifica daca stiva e goaka, in caz contrar scoate varful
TL2_interventie Extragere_stiva_interventie(TStiva_interventie *q)
{
    if (q->sf == q->pointeri_coada)
        return NULL;

    q->sf--;
    return *q->sf;
}

//functie de distrugere pt eliberarea memoriei
void DistrugeStiva(TStiva_interventie **s) {
    if (*s) {
        if ((*s)->pointeri_coada) free((*s)->pointeri_coada);
        free(*s);
        *s = NULL;
    }
}

//aici incep functiile care ajuta la modificarea/initializarea/distrugerea incidentelor
TL2_incident AlocCelula_incident(TIncident x)
{
    TL2_incident aux = (TL2_incident)malloc(sizeof(TCelula2_incident));
    if (!aux)
        return NULL;

    aux->info = x;
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

TL2_incident InitLista_incident()
{
    TL2_incident aux = (TL2_incident)malloc(sizeof(TCelula2_incident));
    if (!aux)
        return NULL;
    aux->pre = aux;
    aux->urm = aux;

    return aux;
}


TL2_incident CitireLista_incident(TL2_incident s, TIncident x)
{
    TL2_incident aux, ultim;
    if (!s)
        return 0;

    ultim = s->pre;
    aux = AlocCelula_incident(x);
    if (!aux)
        return 0;
    aux->pre = ultim;
    aux->urm = ultim->urm;
    ultim->urm->pre = aux;
    ultim->urm = aux;
    ultim = aux;
    return aux;
}

void DistrugeLista_incident(TL2_incident *s)
{
    TL2_incident p = (*s)->urm, aux;
    while (p != *s) {
        if (p->info.description)
            free(p->info.description);
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*s);
    *s = NULL;
}

//o logica asemanatoare cu cea a stivei, insa apare si inceput si final
//iar offset-ul trebuie calculat pentru ambele
TCoada_incident *InitQ_incident(void)
{
    TCoada_incident *c;
    c = (TCoada_incident *)malloc(sizeof(TCoada_incident));
    if (!c)
        return NULL;
    c->inc = NULL;
    c->sf = NULL;
    return c;
}

void InitCoada(TCoada_incident *q, int initial_size)
{
    q->pointeri_coada = (TL2_incident *)malloc(initial_size * sizeof(TL2_incident));
    q->sf = q->pointeri_coada;
    q->inc = q->pointeri_coada;
}

void Introducere_coada_incident(TCoada_incident *q, TL2_incident s, int *current_cap)
{
    if (q->inc == q->pointeri_coada + (*current_cap)) {
        int offset_inc = q->inc - q->pointeri_coada;
        int offset_sf = q->sf - q->pointeri_coada;
        *current_cap *= 2;
        q->pointeri_coada = realloc(q->pointeri_coada, (*current_cap) * sizeof(TL2_incident));
        q->inc = q->pointeri_coada + offset_inc;
        q->sf = q->pointeri_coada + offset_sf;
    }

    *q->inc = s;
    q->inc++;
}

//functie speciala pentru undo care adauga la inceputul cozii
void Introducere_coada_incident_inceput(TCoada_incident *q, TL2_incident s, int *current_cap)
{
    if (q->sf == q->inc) {
        *q->sf = s;
        q->inc++;
        return;
    }

    if (q->sf > q->pointeri_coada) {
        q->sf--;
        *q->sf = s;
        return;
    }

    if (q->inc == q->pointeri_coada + (*current_cap)) {
        int offset_inc = q->inc - q->pointeri_coada;
        int offset_sf = q->sf - q->pointeri_coada;
        *current_cap *= 2;
        q->pointeri_coada = realloc(q->pointeri_coada, (*current_cap) * sizeof(TL2_incident));
        q->inc = q->pointeri_coada + offset_inc;
        q->sf = q->pointeri_coada + offset_sf;
    }

    TL2_incident *p = q->inc;
    while (p > q->sf) {
        *p = *(p - 1);
        p--;
    }
    *q->sf = s;
    q->inc++;
}

TL2_incident Extragere_coada_incident(TCoada_incident *q)
{
    if (q->sf == q->inc)
        return NULL;

    TL2_incident res = *q->sf;
    q->sf++;

    if (q->sf == q->inc) {
        q->sf = q->pointeri_coada;
        q->inc = q->pointeri_coada;
    }

    return res;
}

void DistrugeCoada_incident(TCoada_incident **q)
{
    if (*q) {
        if ((*q)->pointeri_coada)
            free((*q)->pointeri_coada);
        free(*q);
        *q = NULL;
    }
}

//aici incep functiile care ajuta la modificarea/initializarea/distrugerii unitatilor
TL2_unitate AlocCelula(TUnitate *elem) {
    TL2_unitate aux = (TL2_unitate) malloc(sizeof(TCelula2_unitate));
    if (aux) {
        aux->unitate = elem;
        aux->urm = NULL;
    }
    return aux;
}

//cauta interventia cu un anumit id de incident si ii face unitatea available
//ajuta la solved
void gasire_unitate(int id_incident, TUnitate **unitate, TL2_interventie interv) {
    for (TL2_interventie p = interv->urm; p != interv; p = p->urm) {
        if (p->info.incident->id == id_incident) {
            *unitate = p->info.unit;
            (*unitate)->availability = 1;
            return;
        }
    }
}

TCoada_unitate* InitQ_unitate()
{
    TCoada_unitate* c;
    c = (TCoada_unitate*)malloc(sizeof(TCoada_unitate));
    if (!c) return NULL;

    c->sf = NULL;
    return c;
}

int IntrQ_unitate(TCoada_unitate *c, TUnitate *x)
{
    TL2_unitate celula = AlocCelula(x);
    if (!celula) {
        return 0;
    }
    if (!c->sf) {
        celula->urm = celula;
        c->sf = celula;
        c->sf->urm = celula;
    }
    else {
        celula->urm = c->sf->urm;
        c->sf->urm = celula;
        c->sf = celula;
    }
    return 1;
}

int ExtrQ_unitate(TCoada_unitate *c, TUnitate **x) {
    if (!c->sf) return 0;

    TL2_unitate prim = c->sf->urm;
    *x = prim->unitate;

    if (c->sf == prim) {
        c->sf = NULL;
    } else {
        c->sf->urm = prim->urm;
    }
    free(prim);
    return 1;
}

void DistrQ_unitate(TCoada_unitate **c) {
    if (!c || !*c) return;

    if ((*c)->sf != NULL) {
        TL2_unitate prim = (*c)->sf->urm;
        TL2_unitate curent = prim;
        TL2_unitate aux;
        do {
            aux = curent;
            curent = curent->urm;
            free(aux);
        } while (curent != prim);
    }

    free(*c);
    *c = NULL;
}

int AfisareQ_unitate(TCoada_unitate *c)
{
    int counter = 0;
    if (c->sf == NULL) {
        return counter;
    }
    TL2_unitate aux = c->sf->urm;
    counter = 1;
    while (aux != c->sf) {
        aux = aux->urm;
        counter++;
    }
    return counter;
}

//citirea comenzii este caracter cu caracter(pentru comenzi cu lungime variabila)
void citire_comanda(char **comanda, FILE *fin)
{
    int dimensiune = 500;
    int len = 0;
    int c;

    while ((c = fgetc(fin)) != EOF && c != '\n') {
        (*comanda)[len++] = (char)c;

        if (len + 1 >= dimensiune) {
            dimensiune *= 2;
            *comanda = realloc(*comanda, dimensiune);
            if (!comanda) {
                perror("nu s-a executat alocarea\n");
                free(comanda);
                comanda = NULL;
                exit(0);
                return;
            }
        }
    }
    (*comanda)[len] = '\0';
}

//aici se interpreteaza comanda pentru a putea folosi case-uri
//in main si pentru a pastra un main mai curat
int interpretare(char *comanda)
{
    if (strcmp(comanda, "EXIT") == 0) {
        return 0;
    } else if (strncmp(comanda, "ADD_INCIDENT", 12) == 0) {
        return 1;
    } else if (strncmp(comanda, "CHECK_UNITS_AVAILABILITY", 24) == 0) {
        return 2;
    } else if (strncmp(comanda, "DISPATCH", 8) == 0) {
        return 3;
    } else if (strncmp(comanda, "UNDO_LAST_DISPATCH", 18) == 0) {
        return 4;
    } else if (strncmp(comanda, "SOLVED_INCIDENT", 15) == 0) {
        return 5;
    } else if (strncmp(comanda, "SHOW_UNIT", 9) == 0) {
        return 6;
    } else if (strncmp(comanda, "SHOW_INCIDENT", 13) == 0) {
        return 7;
    } else if (strncmp(comanda, "SHOW_INTERVENTIONS", 18) == 0) {
        return 8;
    }
    return -1;
}


//aici incep functiile cerute in enunt
//add_incident ii aloca memorie descrierii din structura
//(exact strlen(descriere) + 1 - ca in cerinta)
//se introduce incidentul in coada corsesp prioritatii
void add_incident(TL2_incident s, char *comanda,
                  TCoada_incident *low, int *cap_l,
                  TCoada_incident *medium, int *cap_m,
                  TCoada_incident *high, int *cap_h) {
    TIncident nou;
    int id;
    char priority[7], *description;
    description = malloc(strlen(comanda));
    sscanf(comanda, "%d %s %[^\n]", &id, priority, description);
    nou.id = id;
    nou.description = malloc(strlen(description) + 1);
    strcpy(nou.priority, priority);
    strcpy(nou.description, description);
    strcpy(nou.status, "queued");
    TL2_incident nounou = CitireLista_incident(s, nou);
    if (strcmp(priority, "low") == 0) {
        Introducere_coada_incident(low, nounou, cap_l);
    } else if (strcmp(priority, "medium") == 0) {
        Introducere_coada_incident(medium, nounou, cap_m);
    } else if (strcmp(priority, "high") == 0) {
        Introducere_coada_incident(high, nounou, cap_h);
    }
    free(description);
}

//scoate o unitate din coada si verifica in functie de
//prioritate carui incident ii atribuie unitatea,
//apoi adauga interventia in stiva
void dispatch(TCoada_incident *high, TCoada_incident *medium, TCoada_incident *low, TL2_interventie interv, TCoada_unitate *unit, int *current_cap, TStiva_interventie *St, FILE *fout) {
    TL2_interventie Celula_interv;
    TInterventie interventie;
    TUnitate *unitate = NULL;
    ExtrQ_unitate(unit, &unitate);
    if (!unitate) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }
    TL2_incident h = Extragere_coada_incident(high);
    if (!h) {
        TL2_incident m = Extragere_coada_incident(medium);
        if (!m) {
            TL2_incident l = Extragere_coada_incident(low);
            if (!l) {
                fprintf(fout, "INVALID OPERATION! ERROR 404\n");
                IntrQ_unitate(unit, unitate);
                return;
            }
            else {
                interventie.incident = &(l->info);
                strcpy(l->info.status, "intervened");
                interventie.unit = unitate;
                (unitate)->availability = 0;
            }
        }
        else {
            interventie.incident = &(m->info);
            strcpy(m->info.status, "intervened");
            interventie.unit = unitate;
            (unitate)->availability = 0;
        }
    }
    else {
        interventie.incident = &(h->info);
        strcpy(h->info.status, "intervened");
        interventie.unit = unitate;
        (unitate)->availability = 0;
    }
    Celula_interv = CitireLista_interventie(interv, interventie);
    Introducere_stiva_interventie(St, Celula_interv, current_cap);
}

//se extrage varful pana cand se intalneste o interventie
//care nu este solved si adauga incidentul la capatul de extragere
// al coziic orespunzatoare prioritatii, iar unitatea la coada unitatilor disponibile
void undo(TStiva_interventie *St, TCoada_incident *low, int *cap_l,
          TCoada_incident *medium, int *cap_m,
          TCoada_incident *high, int *cap_h, TCoada_unitate *unit, TL2_interventie interv, FILE *fout) {

    //verifica daca stiva e goala
    if (!St || St->sf == St->pointeri_coada) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    TL2_interventie varf = Extragere_stiva_interventie(St);
    if (strcmp(varf->info.incident->status, "solved") == 0) {
        undo(St, low, cap_l, medium, cap_m, high, cap_h, unit, interv, fout);
        Introducere_stiva_interventie(St, varf, cap_l);
        return;
    }
    if (!varf) return;
    varf->info.unit->availability = 1;
    strcpy(varf->info.incident->status, "queued");
    TL2_incident celula_inc = (TL2_incident)varf->info.incident;
    if (strcmp(varf->info.incident->priority, "low") == 0) {
        Introducere_coada_incident_inceput(low, celula_inc, cap_l);
    }
    else if (strcmp(varf->info.incident->priority, "medium") == 0) {
        Introducere_coada_incident_inceput(medium, celula_inc, cap_m);
    }
    else if (strcmp(varf->info.incident->priority, "high") == 0) {
        Introducere_coada_incident_inceput(high, celula_inc, cap_h);
    }
    IntrQ_unitate(unit, varf->info.unit);
    varf->info.unit = NULL;
    varf->pre->urm = varf->urm;
    varf->urm->pre = varf->pre;
    free(varf);
}

//aici se foloseste gasire unitate, pentru a o adauga inapoi in coada
//incidentului i se schimba statusul in solved
void solved(char *comanda, TL2_incident s, TL2_interventie interv, TCoada_unitate *unit, FILE *fout) {
    int id, amgasit = 0;
    TUnitate *unit_gasit = NULL;
    if (sscanf(comanda, "%d", &id) != 1) return;

    for (TL2_incident p = s->urm; p != s; p = p->urm) {
        if (p->info.id == id && strcmp(p->info.status, "intervened") == 0) {
            amgasit = 1;
            strcpy(p->info.status, "solved");
            gasire_unitate(id, &unit_gasit, interv);

            if (unit_gasit != NULL) {
                IntrQ_unitate(unit, unit_gasit);
            }
            return;
        }
    }
    if (!amgasit) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
    }
}

//afiseaza unitatea cu id-ul dat in comanda
// in functie de valoarea availability afiseaza daca unitatea e disponibila sau nu
void show_unit(char *comanda, TUnitate *unitati, FILE *fout) {
    int id;
    sscanf(comanda, "%d", &id);
    if (unitati == NULL) {
        fprintf(fout, "Unitatea nu există.\n");
        return;
    }
    for (int i = 0; i < 51; i++) {
        if (unitati[i].id == id) {
            fprintf(fout, "Unit %d is type %c and is %s\n",
                    unitati[i].id, unitati[i].type,
                    unitati[i].availability ? "available" : "unavailable");
            return;
        }
    }
    fprintf(fout, "INVALID OPERATION! ERROR 404\n");
}


//afiseaza incidentul cu id-ul dat in comanda
void show_incident(char *comanda, TL2_incident s, FILE *fout) {
    int id;
    sscanf(comanda, "%d", &id);
    for (TL2_incident p = s->urm; p != s; p = p->urm) {
        if (p->info.id == id) {
            fprintf(fout, "Incident %d has %s priority, the following description: %s and is %s\n",
                    p->info.id, p->info.priority, p->info.description, p->info.status);
            return;
        }
    }
    fprintf(fout, "INVALID OPERATION! ERROR 404\n");
}

//afiseaza toate interventiile, daca nu exista niciuna afiseaza un mesaj corespunzator
void show_interventions(TL2_interventie interv, FILE *fout) {
    int swtch = 0;
    char *show_prima = malloc(256 * sizeof(char));
    if (interv->urm != interv) {
        if (!sprintf(show_prima, "Incident %d was assigned to unit %d, and has the following status: \"%s\"",
                     interv->urm->info.incident->id,
                     interv->urm->info.unit->id,
                     interv->urm->info.incident->status)) {
            fprintf(fout, "error\n");
        }
        else {
            fprintf(fout, "%s\n", show_prima);
            swtch = 1;
        }
    }
    for (TL2_interventie p = interv->urm->urm; p != interv; p = p->urm) {
        if (fprintf(fout, "Incident %d was assigned to unit %d, and has the following status: \"%s\"\n",
                    p->info.incident->id,
                    p->info.unit->id,
                    p->info.incident->status)) {
            swtch = 1;
        }
    }

    if (!swtch) {
        fprintf(fout, "No intervention has been initiated\n");
    }
    free(show_prima);
}

//main-ul citeste nr de echipaje, apoi tipul si id-ul acestora
//apoi citeste nr de comenzi si pentru fiecare comanda citeste comanda de lungime variabila
//in mare parte, main-ul apeleaza functiile de init, distrugere si imparte problema
//pe case-uri care apeleaza functiile
int main() {
    FILE *fin = fopen("tema1.in", "r");
    FILE *fout = fopen("tema1.out", "w");

    int numar_echipaje, nr_comenzi;
    TUnitate unitati[51] = {0};
    TCoada_unitate *q_unitate = InitQ_unitate();
    fscanf(fin, "%d", &numar_echipaje);
    for (int i = 0; i < numar_echipaje; i++) {
        fscanf(fin, "%d %c", &unitati[i].id, &unitati[i].type);
        unitati[i].availability = 1;
        IntrQ_unitate(q_unitate, &unitati[i]);
    }
    fscanf(fin, "%d", &nr_comenzi);
    TStiva_interventie *St = InitS_interventie();
    TL2_interventie interv = InitLista_interventie();
    TL2_incident incid = InitLista_incident();
    TCoada_incident *low = InitQ_incident();
    TCoada_incident *medium = InitQ_incident();
    TCoada_incident *high = InitQ_incident();
    int cap_low = 10, cap_medium = 10, cap_high = 10, cap_stiva = 10;
    InitCoada(low, cap_low);
    InitCoada(medium, cap_medium);
    InitCoada(high, cap_high);
    InitStiva(St, cap_stiva);
    char *comanda = (char *)malloc(500 * sizeof(char));
    if (!comanda) {
        return -1;
    }
    // consuma newline-ul ramas dupa fscanf-ul pentru nr_comenzi
    fgetc(fin);
    for (int j = 0; j < nr_comenzi; j++) {
        citire_comanda(&comanda, fin);
        int tip = interpretare(comanda);
        if (tip == 0) {
            break;
        }
        switch (tip) {
        case 1:
            add_incident(incid, comanda + 13, low, &cap_low, medium, &cap_medium, high, &cap_high);
            break;
        case 2:
            fprintf(fout, "Number of available units: %d\n", AfisareQ_unitate(q_unitate));
            break;
        case 3:
            dispatch(high, medium, low, interv, q_unitate, &cap_stiva, St, fout);
            break;
        case 4:
            undo(St, low, &cap_low, medium, &cap_medium, high, &cap_high, q_unitate, interv, fout);
            break;
        case 5:
            solved(comanda + 16, incid, interv, q_unitate, fout);
            break;
        case 6:
            show_unit(comanda + 9, unitati, fout);
            break;
        case 7:
            show_incident(comanda + 13, incid, fout);
            break;
        case 8:
            show_interventions(interv, fout);
            break;
        }

    }
    free(comanda);
    DistrQ_unitate(&q_unitate);
    DistrugeLista_incident(&incid);
    DistrugeLista_interventie(&interv);
    DistrugeCoada_incident(&low);
    DistrugeCoada_incident(&medium);
    DistrugeCoada_incident(&high);
    DistrugeStiva(&St);

    fclose(fin);
    fclose(fout);
    return 0;
}