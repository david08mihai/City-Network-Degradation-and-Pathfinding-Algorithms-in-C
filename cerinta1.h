#ifndef CERINTA1_H
#define CERINTA1_H
#define SIZE 100

typedef struct tronsoane {
    int pozitie;
    float tronsoane[SIZE];
    int numarTronsoane;
    float masca[SIZE];
    int indexTronson;
} Tronsoane;


typedef struct list{
    Tronsoane detaliiTronsoane;
    struct list *next;
    struct list  *prev;
}*List;

typedef struct graph {
	int numarRute;
    int numarAni;
    int numarOrase;
    int uzuraAcceptabila;
	List* oraseVecine;
    int vizitat[SIZE];
    int numarVecini[SIZE];
} *Graph;

List initList(Tronsoane p);
List adaugareSfarsit(List l, Tronsoane p);
Graph initGraph(int numarRute, int numarAni, int uzuraAcceptabila);
int exista(Graph g, char *aux, char **orase);
void citireOrase(Graph g, char **orase, char**toateorase, FILE *f);
void copieremasca(Graph g);
void afisare(Graph g, char **nume, char**oraseTotale, FILE *out);
int exista_muchie(List l, char *oras);
void cerinta1(Graph g);
void medie(Graph g, FILE *out);
void inversare(float *tronsonActualizat, Graph orasNou, int pozitieNoua, int pozitieVeche);
float cautaresfarsit(List l, Graph g, int pozitieAnterioara);
void copieremasca(Graph g);
float cautaresinceput(List l, Graph g, int pozitieAnterioara);
int comparare(const void *a, const void *b);
float cautareambeleparti(List l, List q);
void cerinta1(Graph g);
void freeMemory(Graph g, char **orase, char **oraseTotale);

#endif