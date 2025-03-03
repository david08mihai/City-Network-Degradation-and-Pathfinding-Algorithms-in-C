#ifndef CERINTA2_H
#define CERINTA2_H

typedef struct pereche {
    int oras, distanta, numarOrdine;
	int vizitat;
} Pereche;

typedef struct node {
	Pereche detaliiCale;
	int vizitat;
	struct node *prev, *next;
} *Nod;

typedef struct transport {
	int numarCai, numarOrase, maximCai;
	Nod *caiVecine;
}* Transport;

typedef struct detalii {
	int oras, distanta, parinte;
} Detalii;

typedef struct heap {
	Pereche *vector;
	int size;
	int capacity;
} *Heap;


Nod adaugareOras(Nod list, Pereche p);
Transport initTransp(int V, int maximCai);
void citireDate(Transport t, FILE *in, char **cai, char** caiTotale);
Heap initHeap(int capacity);
Heap shiftUp(Heap h, int index);
Heap insertHeap(Heap h, Pereche p);
Heap shiftDown(Heap h, int index);
Pereche extract_min(Heap h, int index);
int muchie(Transport t, int i, int j);
int isEmptyHeap(Heap h);
int distanta(Transport t, int i, int j);
void Dijkstra(Transport t, int start, int *d, int *parinte, Heap q);
int gasireIndex(char *start, char **orase, int numarOrase);
void adaugareDrum(int *parinte, int i, int *drum, int *pozDrum);
void fiecareDrum(Transport t, FILE *out, int *d, int *parinte, int start, char** caiTotale, Heap q);
void afDrum(Transport t, int *drum, int pozDrum, char **caiTotale, int *v, int *poz);
void freeElements(Transport t, char **cai, char** caiTotale, int *d, int *parinte);
void afisareFinalaa(Transport t, FILE *out, char **caiTotale, Heap q);
#endif