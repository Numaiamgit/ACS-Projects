//Gheorghe Alexandru-Nicolae 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura pentru fisier
typedef struct fisier {
    char *id;
    int scor;
    int cate_cuv;
} Fisier;

//structura pentru lista dublu inlantuita
typedef struct celula2 {
    Fisier fisier;
    struct celula2 *pre, *urm;
} TCelula2, *TL2;

//structura pentru arbore(cu caracter ca info)
typedef struct node {
    char info;
    TL2 lista_fisiere;
    struct node *left;
    struct node *right;
} Node, *Tree;

//functie pentru heap
typedef int (*TFCmp)(Fisier, Fisier);

//structura heap
typedef struct Heap {
    int nrMax, nrElem;
    Fisier *v;
    TFCmp comp;
} THeap;

//functie pentru qsort
int cmp_str(const void *a, const void *b)
{
    return strcmp(*(const char **) a, *(const char **) b);
}

//alocare heap, preluata din lab apoi modificata
THeap *AlocaHeap(int nrMax, TFCmp comp)
{
    THeap *h = (THeap *) malloc(sizeof(struct Heap));
    if (!h) {
        return NULL;
    }

    h->v = (Fisier *) malloc(nrMax * sizeof(Fisier));
    if (!h->v) {
        free(h);
        return NULL;
    }

    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;

    return h;
}

//relatia pentru max heap, preluata din lab si modificata
int RelMaxHeap(Fisier a, Fisier b)
{
    if (a.scor != b.scor)
        return a.scor > b.scor;
    return strcmp(a.id, b.id) < 0;
}

//afisare heap (nu e folosita in rezolvarea task-urilor)
void AfisareHeap(THeap *h, int pos)
{
    if (pos >= h->nrMax) {
        printf("-");
        return;
    }

    printf(" %s %d ", h->v[pos].id, h->v[pos].scor);

    if (2 * pos + 1 >= h->nrMax && 2 * pos + 2 >= h->nrMax)
        return;

    printf("(");

    AfisareHeap(h, 2 * pos + 1);
    printf(",");

    AfisareHeap(h, 2 * pos + 2);
    printf(")");
}

//(distrugere heap)
void DistrugeHeap(THeap **h)
{
    free((*h)->v);
    free(*h);
    *h = NULL;
}

//insereaza in heap
void InsertHeap(THeap *h, Fisier val)
{
    int index;
    if (h->nrMax == h->nrElem) {
        printf("Nu mai pune nasule\n");
        return;
    }
    h->v[h->nrElem] = val;
    index = h->nrElem;
    h->nrElem++;
    int tatic_pozitie = (index - 1) / 2;
    while (index != 0) {
        if (h->comp(h->v[index], h->v[tatic_pozitie])) {
            Fisier aux_val = h->v[tatic_pozitie];
            h->v[tatic_pozitie] = h->v[index];
            h->v[index] = aux_val;
            index = tatic_pozitie;
            tatic_pozitie = (index - 1) / 2;
        } else {
            break;
        }
    }
}

//extrage din heap, fol in topk
Fisier ExtrHeap(THeap *h)
{
    Fisier rezultat = h->v[0];
    h->v[0] = h->v[h->nrElem - 1];
    h->nrElem--;

    int index = 0;
    while (1) {
        int swap = index;
        int stanga = index * 2 + 1;
        int dreapta = index * 2 + 2;

        if (stanga < h->nrElem && h->comp(h->v[stanga], h->v[swap]))
            swap = stanga;
        if (dreapta < h->nrElem && h->comp(h->v[dreapta], h->v[swap]))
            swap = dreapta;

        if (swap == index)
            break;

        Fisier aux_val = h->v[index];
        h->v[index] = h->v[swap];
        h->v[swap] = aux_val;
        index = swap;
    }
    return rezultat;
}

//urmeaza functii pentru lista
//alocarea celulei
TL2 AlocCelula(Fisier x)
{
    TL2 aux = (TL2) malloc(sizeof(TCelula2));
    if (!aux)
        return NULL;

    aux->fisier = x;
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

//initializarea listei
TL2 InitLista()
{
    TL2 aux = (TL2) malloc(sizeof(TCelula2));
    if (!aux)
        return NULL;
    aux->pre = NULL;
    aux->urm = NULL;
    return aux;
}

//citire in lista direct sortat lexicografic
TL2 CitireLista(TL2 *s, Fisier x)
{
    TL2 aux = AlocCelula(x);
    if (!aux)
        return NULL;
    aux->fisier.id = strdup(x.id);

    if (*s == NULL) {
        *s = aux;
        return aux;
    }
    if (strcmp(aux->fisier.id, (*s)->fisier.id) <= 0) {
        aux->urm = *s;
        (*s)->pre = aux;
        *s = aux;
        return aux;
    }
    TL2 p = *s;
    while (p->urm != NULL && strcmp(aux->fisier.id, p->urm->fisier.id) > 0) {
        p = p->urm;
    }

    aux->urm = p->urm;
    aux->pre = p;
    if (p->urm)
        p->urm->pre = aux;
    p->urm = aux;

    return aux;
}

//distrugerea listei
void DistrugeLista(TL2 *s)
{
    TL2 p = *s, aux;
    while (p != NULL) {
        aux = p;
        p = p->urm;
        free(aux->fisier.id);
        free(aux);
    }
    *s = NULL;
}

//creare nod
Tree createNode(char data)
{
    Tree newnode = malloc(sizeof(Node));
    if (!newnode)
        return NULL;
    newnode->info = data;
    newnode->lista_fisiere = NULL;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

//adaugare copil pentru un nod din arbore
void addChild(Tree parent, Tree child)
{
    child->right = NULL;

    if (parent->left == NULL || child->info < parent->left->info) {
        child->right = parent->left;
        parent->left = child;
        return;
    }
    Tree current = parent->left;
    while (current->right && current->right->info < child->info) {
        current = current->right;
    }
    child->right = current->right;
    current->right = child;
}


//functie de parcurgere a arborelui(adauga litere in arbore in functie de param creare)
//de asemenea returneaza nodul frunza pentru cuvantul pentru care se parcurge
//daca are o parte deja scrisa, merge in continuare si returneaza frunza)
// daca exista deja, nu mai adauga nimic si intoarce frunza, iar daca nu exista nimic din
//cuvant, il scrie de la 0 in arbore
Tree preorder(Tree root, char *cuvant_cheie, char *aux, int creare)
{
    if (!root)
        return NULL;

    if (root->info == '\0')
        return preorder(root->left, cuvant_cheie, aux, creare);

    int len = strlen(aux);

    aux[len] = root->info;
    aux[len + 1] = '\0';

    int len_aux = strlen(aux);
    int len_cuvant = strlen(cuvant_cheie);
    if (len_aux <= len_cuvant && strncmp(aux, cuvant_cheie, len_aux) == 0) {

        if (strcmp(aux, cuvant_cheie) == 0) {
            aux[len] = '\0';
            return root;
        }
        Tree rez = preorder(root->left, cuvant_cheie, aux, creare);

        if (rez) {
            aux[len] = '\0';
            return rez;
        }
        if (creare) {
            Tree curr = root;

            for (int i = strlen(aux); i < strlen(cuvant_cheie); i++) {
                Tree n1 = createNode(cuvant_cheie[i]);
                addChild(curr, n1);
                curr = n1;
            }

            aux[len] = '\0';
            return curr;
        }
    }

    aux[len] = '\0';


    return preorder(root->right, cuvant_cheie, aux, creare);
}

//functia care se apeleaza pentru a putea initializa aux
Tree preorder_cuvant_cheie(Tree root, char *cuvant_cheie, int creare)
{
    char *aux = calloc(strlen(cuvant_cheie) + 2, sizeof(char));
    Tree rez = preorder(root, cuvant_cheie, aux, creare);
    free(aux);
    return rez;
}

//functie preorder cu odificari pentru prefix
//returneaza nodul coresp unui prefix
Tree prefix_preorder(Tree root, char *prefix, char *aux)
{
    if (!root)
        return NULL;
    if (root->info == '\0')
        return prefix_preorder(root->left, prefix, aux);

    int len = strlen(aux);
    aux[len] = root->info;
    aux[len + 1] = '\0';

    if (strncmp(aux, prefix, strlen(aux)) == 0) {
        if (strcmp(aux, prefix) == 0)
            return root;
        if (root->left) {
            Tree rez = prefix_preorder(root->left, prefix, aux);
            if (rez)
                return rez;
        }
        aux[len] = '\0';
        return NULL;
    }

    aux[len] = '\0';
    return prefix_preorder(root->right, prefix, aux);
}

//citire comanda(ca in prima tema)
void citire_comanda(FILE *in, char **comanda)
{
    int dimensiune = 500;
    int len = 0;
    int c;

    while ((c = getc(in)) != EOF && c != '\n') {
        (*comanda)[len++] = (char) c;

        if (len + 1 >= dimensiune) {
            dimensiune *= 2;
            *comanda = realloc(*comanda, dimensiune);
            if (!*comanda) {
                perror("nu s-a executat alocarea\n");
                exit(0);
                return;
            }
        }
    }
    (*comanda)[len] = '\0';
}

//interpretarea comenzii, preluata tot din prima tema
//comenzile sunt ordonate in functie a.i. sa nu se poata incurca intre
//comenzi (ex: del si delkw)
int interpretare(char *comanda)
{
    if (strcmp(comanda, "EXIT") == 0) {
        return 0;
    } else if (strncmp(comanda, "ADDKW", 5) == 0) {
        return 3;
    } else if (strncmp(comanda, "DELKW", 5) == 0) {
        return 4;
    } else if (strncmp(comanda, "DEL", 3) == 0) {
        return 2;
    } else if (strncmp(comanda, "ADD", 3) == 0) {
        return 1;
    } else if (strncmp(comanda, "FIND", 4) == 0) {
        return 5;
    } else if (strncmp(comanda, "TOPK", 4) == 0) {
        return 6;
    } else if (strncmp(comanda, "PRINT", 5) == 0) {
        return 7;
    } else if (strncmp(comanda, "PREFIX", 6) == 0) {
        return 8;
    }
    return -1;
}

//sterge fisierul din fiecare frunza in care il gaseste
//apoi sterge fiecare nod frunza care nu mai are lista de fisiere
Tree trecere_del(Tree root, char *id_f)
{
    if (!root)
        return NULL;

    root->left = trecere_del(root->left, id_f);
    root->right = trecere_del(root->right, id_f);

    TL2 p = root->lista_fisiere;
    TL2 ant = NULL;
    while (p) {
        if (strcmp(p->fisier.id, id_f) == 0) {
            if (ant == NULL)
                root->lista_fisiere = p->urm;
            else
                ant->urm = p->urm;
            if (p->urm)
                p->urm->pre = ant;

            free(p->fisier.id);
            free(p);
            break;
        }
        ant = p;
        p = p->urm;
    }

    if (root->info != '\0' && root->lista_fisiere == NULL && root->left == NULL) {
        Tree frate_dreapta = root->right;
        free(root);
        return frate_dreapta;
    }
    return root;
}

//curata arborele dupa ce se scoate un fisier dintr-o frunza(daca e cazul)
Tree trecere_delkw(Tree root)
{
    if (!root)
        return NULL;

    root->left = trecere_delkw(root->left);
    root->right = trecere_delkw(root->right);

    if (root->info != '\0' && root->left == NULL && root->lista_fisiere == NULL) {

        Tree frate = root->right;
        free(root);
        return frate;
    }

    return root;
}

//indeplineste task-ul add
//parseaza comanda
//verifica daca fisierul a fost adaugat deja
//daca nu il introduce in lista
//foloseste preorder_cuvant_cheie ca sa introduca cuvintele si sa puna fisierul
//pe frunzele cuvintelor
void add(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    TL2 auxiliar = *lista_fisiere_completa;
    Fisier fisier;
    int lungime = 0;
    char *cuvant_cheie = malloc(strlen(comanda) * sizeof(char));
    fisier.id = malloc(strlen(comanda) * sizeof(char));
    sscanf(comanda, "%s %d %d%n", fisier.id, &fisier.scor, &fisier.cate_cuv, &lungime);
    while (auxiliar) {
        if (auxiliar->fisier.id && fisier.id) {
            if (strcmp(auxiliar->fisier.id, fisier.id) == 0) {
                fprintf(out, "EXISTS\n");
                free(fisier.id);
                free(cuvant_cheie);
                return;
            }
        }
        auxiliar = auxiliar->urm;
    }
    CitireLista(lista_fisiere_completa, fisier);
    for (int i = 0; i < fisier.cate_cuv; i++) {
        sscanf(comanda + lungime, "%s", cuvant_cheie);
        Tree frunza = preorder_cuvant_cheie(root, cuvant_cheie, 1);
        if (!frunza) {
            Tree prev = root;
            for (int k = 0; k < (int) strlen(cuvant_cheie); k++) {
                Tree n1 = createNode(cuvant_cheie[k]);
                addChild(prev, n1);
                prev = n1;
            }
            frunza = prev;
        }
        lungime += strlen(cuvant_cheie) + 1;
        int deja = 0;
        TL2 p = frunza->lista_fisiere;
        while (p) {
            if (strcmp(p->fisier.id, fisier.id) == 0) {
                deja = 1;
                break;
            }
            p = p->urm;
        }
        if (!deja) {
            if (!frunza->lista_fisiere) {
                TL2 lista_noua = NULL;
                CitireLista(&lista_noua, fisier);
                frunza->lista_fisiere = lista_noua;
            } else {
                CitireLista(&frunza->lista_fisiere, fisier);
            }
        }
    }
    fprintf(out, "OK\n");
    free(fisier.id);
    free(cuvant_cheie);
}

//gasete fisierul iar apoi foloseste trecere del pentru stergere
void del(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    TL2 auxiliar = *lista_fisiere_completa;
    if (!auxiliar) {
        fprintf(out, "NOT FOUND\n");
        return;
    }

    TL2 anterior = NULL;
    while (auxiliar) {
        TL2 urmator = auxiliar->urm;
        if (strcmp(auxiliar->fisier.id, comanda) == 0) {
            if (anterior == NULL)
                *lista_fisiere_completa = urmator;
            else
                anterior->urm = urmator;
            if (urmator)
                urmator->pre = anterior;
            free(auxiliar->fisier.id);
            free(auxiliar);
            root->left = trecere_del(root->left, comanda);
            fprintf(out, "OK\n");
            return;
        }
        anterior = auxiliar;
        auxiliar = auxiliar->urm;
    }
    fprintf(out, "NOT FOUND\n");
}

//functia de add kw, verifica si daca cuvantul cheie e deja atribuit
void addkw(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    TL2 auxiliar = *lista_fisiere_completa;
    int swtch = 0;
    char *id = malloc(strlen(comanda) * sizeof(char));
    char *cuvant = malloc(strlen(comanda) * sizeof(char));
    sscanf(comanda, "%s %s", id, cuvant);
    while (auxiliar) {
        if (auxiliar->fisier.id && id) {
            if (strcmp(auxiliar->fisier.id, id) == 0) {
                swtch = 1;
            }
        }
        auxiliar = auxiliar->urm;
    }
    if (!swtch) {
        fprintf(out, "NOT FOUND\n");
        free(id);
        free(cuvant);
        return;
    }
    Tree frunza = preorder_cuvant_cheie(root, cuvant, 1);
    if (!frunza) {
        Tree prev = root;
        for (int k = 0; k < (int) strlen(cuvant); k++) {
            Tree n1 = createNode(cuvant[k]);
            addChild(prev, n1);
            prev = n1;
        }
        frunza = prev;
    }
    auxiliar = *lista_fisiere_completa;
    while (auxiliar) {
        if (auxiliar->fisier.id && id) {
            if (strcmp(auxiliar->fisier.id, id) == 0) {
                Fisier fisier_gasit = auxiliar->fisier;
                if (!frunza->lista_fisiere) {;
                    CitireLista(&frunza->lista_fisiere, fisier_gasit);
                    fprintf(out, "OK\n");
                } else {
                    TL2 p = frunza->lista_fisiere;
                    int deja_are_kw = 0;
                    while (p) {
                        if (strcmp(p->fisier.id, id) == 0) {
                            deja_are_kw = 1;
                            break;
                        }
                        p = p->urm;
                    }
                    if (!deja_are_kw) {
                        CitireLista(&frunza->lista_fisiere, fisier_gasit);
                    }
                    fprintf(out, "OK\n");
                }
                free(id);
                free(cuvant);
                return;
            }
        }
        auxiliar = auxiliar->urm;
    }
}

//cauta fisierul in lista de la frunza unui cuvant cheie, il elimina apoi verifica daca 
//scurteaza/elimina cuvantul cheie
void delkw(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    char *fisier_id = malloc(strlen(comanda) + 1);
    char *cuvant = malloc(strlen(comanda) + 1);
    sscanf(comanda, "%s %s", fisier_id, cuvant);

    int exista_fisier_in_sistem = 0;
    TL2 p_global = *lista_fisiere_completa;
    while (p_global) {
        if (strcmp(p_global->fisier.id, fisier_id) == 0) {
            exista_fisier_in_sistem = 1;
            break;
        }
        p_global = p_global->urm;
    }

    if (!exista_fisier_in_sistem) {
        fprintf(out, "NOT FOUND\n");
        free(fisier_id);
        free(cuvant);
        return;
    }
    Tree frunza = preorder_cuvant_cheie(root, cuvant, 0);

    if (!frunza || !frunza->lista_fisiere) {
        fprintf(out, "OK\n");
        free(fisier_id);
        free(cuvant);
        return;
    }
    TL2 auxiliar = frunza->lista_fisiere;
    while (auxiliar) {
        if (strcmp(auxiliar->fisier.id, fisier_id) == 0) {
            if (auxiliar->pre == NULL) {
                frunza->lista_fisiere = auxiliar->urm;
                if (frunza->lista_fisiere)
                    frunza->lista_fisiere->pre = NULL;
            } else {
                auxiliar->pre->urm = auxiliar->urm;
                if (auxiliar->urm)
                    auxiliar->urm->pre = auxiliar->pre;
            }

            free(auxiliar->fisier.id);
            free(auxiliar);

            root->left = trecere_delkw(root->left);

            fprintf(out, "OK\n");
            free(fisier_id);
            free(cuvant);
            return;
        }
        auxiliar = auxiliar->urm;
    }

    fprintf(out, "OK\n");
    free(fisier_id);
    free(cuvant);
}

//cauta cuvantul chei cu preorder iar apoi afiseaza lista sau empty
void find(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    Tree frunza = preorder_cuvant_cheie(root, comanda, 0);
    if (!frunza || !frunza->lista_fisiere) {
        fprintf(out, "EMPTY\n");
        return;
    }
    TL2 auxiliar = frunza->lista_fisiere;
    int count = 0;
    while (auxiliar) {
        count++;
        auxiliar = auxiliar->urm;
    }
    auxiliar = frunza->lista_fisiere;
    fprintf(out, "%d ", count);
    while (auxiliar) {
        fprintf(out, "%s ", auxiliar->fisier.id);
        auxiliar = auxiliar->urm;
    }
    fprintf(out, "\n");
}

//trece fisierele unei frunze intr-un vector, pe care il transpune intr-un heap 
//din care extrage(heap-ul este maxheap dupa scorul de relevanta)
void topk(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    int nr;
    Fisier *k;
    char *cuvant = malloc(strlen(comanda) * sizeof(char));
    sscanf(comanda, "%s %d", cuvant, &nr);
    Tree frunza = preorder_cuvant_cheie(root, cuvant, 0);
    if (!frunza || !frunza->lista_fisiere) {
        fprintf(out, "EMPTY\n");
        free(cuvant);
        return;
    }
    if (!frunza->lista_fisiere) {
        fprintf(out, "EMPTY\n");
        return;
    }
    TL2 auxiliar = frunza->lista_fisiere;
    int count = 0;
    int i = 0;
    while (auxiliar) {
        count++;
        auxiliar = auxiliar->urm;
    }
    k = malloc(count * sizeof(Fisier));
    auxiliar = frunza->lista_fisiere;
    while (auxiliar) {
        k[i] = auxiliar->fisier;
        i++;
        auxiliar = auxiliar->urm;
    }
    int dimVec = count;
    THeap *h = NULL;
    h = AlocaHeap(dimVec, RelMaxHeap);
    for (int i = 0; i < dimVec; i++) {
        InsertHeap(h, k[i]);
    }
    int j = nr;
    if (nr > dimVec) {
        nr = dimVec;
    }
    Fisier *fis = malloc(nr * sizeof(Fisier));
    for (int i = 0; i < nr; i++) {
        fis[i] = ExtrHeap(h);
    }
    fprintf(out, "%d ", nr);
    for (int i = 0; i < nr; i++) {
        fprintf(out, "%s ", fis[i].id);
    }
    fprintf(out, "\n");
    free(cuvant);
    free(k);
    free(fis);
    DistrugeHeap(&h);
}

//printeaza lista dublu inlantuita de fisiere
void printLista(FILE *out, TL2 lista)
{
    TL2 p = lista;
    int c = 0;
    while (p != NULL) {
        c++;
        p = p->urm;
    }
    p = lista;
    fprintf(out, "%d ", c);
    while (p != NULL) {
        fprintf(out, "%s ", p->fisier.id);
        p = p->urm;
    }
    fprintf(out, "\n");
}

//printeaza cuvintel si face apel la printare de lista
void printTree_helper(Tree root, char **cuvant_curent, int *capacitate, int depth, FILE *out)
{
    if (!root)
        return;
    if (root->info == '\0') {
        printTree_helper(root->left, cuvant_curent, capacitate, depth, out);
        return;
    }

    if (depth + 2 > *capacitate) {
        *capacitate = (depth + 2) * 2;
        *cuvant_curent = realloc(*cuvant_curent, *capacitate * sizeof(char));
    }

    (*cuvant_curent)[depth] = root->info;
    (*cuvant_curent)[depth + 1] = '\0';

    if (root->lista_fisiere) {
        fprintf(out, "%s ", *cuvant_curent);
        printLista(out, root->lista_fisiere);
    }

    printTree_helper(root->left, cuvant_curent, capacitate, depth + 1, out);
    (*cuvant_curent)[depth] = '\0';
    printTree_helper(root->right, cuvant_curent, capacitate, depth, out);
}

//functia care se apeleaza pentru a se putea initializa si pt a verifica
//daca arborele e gol
void printTree(Tree root, int nivel, FILE *out)
{
    char *cuvant_curent = malloc(100 * sizeof(char));
    int capacitate = 100;
    if (!root->left) {
        fprintf(out, "EMPTY\n");
        free(cuvant_curent);
        return;
    }
    printTree_helper(root, &cuvant_curent, &capacitate, 0, out);
    free(cuvant_curent);
}

//Colecteaza toate id-urile unice dintr-un subarbore
void colecteaza_subarbore(Tree root, char **ids, int *nr)
{
    if (!root)
        return;

    TL2 p = root->lista_fisiere;
    while (p) {
        int deja = 0;
        for (int i = 0; i < *nr; i++) {
            if (strcmp(ids[i], p->fisier.id) == 0) {
                deja = 1;
                break;
            }
        }
        if (!deja)
            ids[(*nr)++] = p->fisier.id;
        p = p->urm;
    }

    colecteaza_subarbore(root->left, ids, nr);

    colecteaza_subarbore(root->right, ids, nr);
}

//cauta prefix-ul, iar dupa ce il gaseste apeleaza colecteaza_subarbore
//pentru a afisa fisierele fara duplicate
void prefix(Tree root, char *comanda, TL2 *lista_fisiere_completa, FILE *out)
{
    char *aux = calloc(strlen(comanda) + 2, sizeof(char));

    Tree nod = prefix_preorder(root, comanda, aux);

    free(aux);

    if (!nod) {
        fprintf(out, "EMPTY\n");
        return;
    }

    int total = 0;
    TL2 p = *lista_fisiere_completa;

    while (p) {
        total++;
        p = p->urm;
    }

    char **ids = malloc(total * sizeof(char *));
    int nr = 0;

    TL2 q = nod->lista_fisiere;

    while (q) {
        int deja = 0;

        for (int i = 0; i < nr; i++) {
            if (strcmp(ids[i], q->fisier.id) == 0) {
                deja = 1;
                break;
            }
        }

        if (!deja)
            ids[nr++] = q->fisier.id;

        q = q->urm;
    }

    colecteaza_subarbore(nod->left, ids, &nr);

    if (nr == 0) {
        fprintf(out, "EMPTY\n");
        free(ids);
        return;
    }

    qsort(ids, nr, sizeof(char *), cmp_str);

    fprintf(out, "%d ", nr);

    for (int i = 0; i < nr; i++) {
        fprintf(out, "%s ", ids[i]);
    }

    fprintf(out, "\n");

    free(ids);
}

//elibereaza arborele si listele frunzelor
void freeTree(Tree root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    DistrugeLista(&root->lista_fisiere);
    free(root);
}

//main-ul, aici doar se dau fisierele de citire si afisare
//se initializeaza arborele se citeste numarul de comenzi, se aloca
//spatiu pt comanda iar apoi se intra in bucla(pana la nr de comenzi citit)
//si se apeleaza functile aferente fiecarui task
//la final memoria este eliberata
int main()
{
    FILE *in = fopen("indexare.in", "r");
    FILE *out = fopen("indexare.out", "w");
    TL2 lista_fisiere_completa = NULL;
    Tree root = createNode('\0');
    int nr_comenzi;
    if (fscanf(in, "%d", &nr_comenzi) != 1) {
        return -1;
    }
    char *comanda = malloc(500 * sizeof(char));
    if (!comanda) {
        return -1;
    }
    getc(in);
    for (int j = 0; j < nr_comenzi + 1; j++) {
        citire_comanda(in, &comanda);
        int tip = interpretare(comanda);
        if (tip == 0) {
            break;
        }
        switch (tip) {
        case 1:
            add(root, comanda + 3, &lista_fisiere_completa, out);
            break;
        case 2:
            del(root, comanda + 4, &lista_fisiere_completa, out);
            break;
        case 3:
            addkw(root, comanda + 6, &lista_fisiere_completa, out);
            break;
        case 4:
            delkw(root, comanda + 6, &lista_fisiere_completa, out);
            break;
        case 5:
            find(root, comanda + 5, &lista_fisiere_completa, out);
            break;
        case 6:
            topk(root, comanda + 5, &lista_fisiere_completa, out);
            break;
        case 7:
            printTree(root, 0, out);
            break;
        case 8:
            prefix(root, comanda + 7, &lista_fisiere_completa, out);
            break;
        }

    }
    free(comanda);
    DistrugeLista(&lista_fisiere_completa);
    freeTree(root);
    fclose(in);
    fclose(out);
    return 0;
}