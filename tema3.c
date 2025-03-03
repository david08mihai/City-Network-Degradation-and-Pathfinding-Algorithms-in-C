#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerinta1.h"
#include "cerinta2.h"


int main(int argc, char *argv[]){
    int i;
    FILE *in = fopen("tema3.in", "r");
    FILE *out = fopen("tema3.out", "w");
    if (in == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(-1);
    }
    if (out == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(-1);
    }
    if (argc == 2 && atoi(argv[1]) == 1) {
        int numarRute, numarAni;
        int uzuraAcceptabila;
        fscanf(in, "%d", &numarRute);
        fscanf(in, "%d", &numarAni);
        fscanf(in, "%d ", &uzuraAcceptabila);
        Graph g = initGraph(numarRute, numarAni, uzuraAcceptabila);
        //vector pentru a tine minte toate orasele in mod unic, pentru a tine index-ul lor
        char **orase = (char **) calloc (g->numarRute * 2, sizeof(char *));
        if (orase == NULL) {
            printf("Eroare la alocarea memoriei\n");
            exit(-1);
        }
        //vector pentru a tine minte toate orasele, pentru a le afisa la final
        char **oraseTotale = (char **)calloc(g->numarRute * 2, sizeof(char *));
        if (oraseTotale == NULL) {
            printf("Eroare la alocarea memoriei\n");
            exit(-1);
        }
        for (i = 0; i < g->numarRute * 2; ++i) {
            orase[i] = (char *)calloc(100, 1);
            if(orase[i] == NULL) {
                printf("Eroare la alocarea memoriei\n");
                exit(-1);
            }
            oraseTotale[i] = (char*)calloc(100, 1);
            if(oraseTotale[i] == NULL) {
                printf("Eroare la alocarea memoriei\n");
                exit(-1);
            }
        }
        //citeste in graf toate orasele si tronsoanele
        citireOrase(g, orase, oraseTotale, in);
        cerinta1(g);
        afisare(g, orase, oraseTotale, out);
        medie(g, out);
        freeMemory(g, orase, oraseTotale);
    } else if (argc == 2 && atoi(argv[1]) == 2) {
        char start[100];
        int i, maximCai, numarCai, indexStart;
        fscanf(in, "%s ", start);
        fscanf(in, "%d %d ", &maximCai, &numarCai);
        Transport t = initTransp(numarCai, maximCai);
        char **cai = (char **) malloc(t->numarCai * 2 * sizeof(char*));
        if (cai == NULL) {
            exit(-1);
        }
        char **caiTotale = (char **) malloc(t->numarCai * 2 * sizeof(char*));
        if (caiTotale == NULL) {
            exit(-1);
        }
        for (i = 0; i < t->numarCai * 2; ++i) {
            cai[i] = (char *) calloc(100, 1);
            if(cai[i] == NULL) {
                printf("Eroare la alocarea memoriei\n");
                exit(-1);
            }
            caiTotale[i] = (char *) calloc(100, 1);
            if(caiTotale[i] == NULL) {
                printf("Eroare la alocarea memoriei\n");
                exit(-1);
            }
        }
        citireDate(t, in, cai, caiTotale);
        indexStart = gasireIndex(start, cai, t->numarOrase);
        int *d = (int *) calloc(t->numarOrase, sizeof(int));
        if (d == NULL) {
            exit(-1);
        }
        int *parinte = calloc(t->numarOrase, sizeof(int));
        if (parinte == NULL) {
            exit(-1);
        }
        Heap q = initHeap(t->numarOrase * 3);
        Dijkstra(t, indexStart , d, parinte, q);
        fiecareDrum(t, out, d, parinte, indexStart, caiTotale, q);
        freeElements(t, cai, caiTotale, d, parinte);
        free(q->vector);
        free(q);
        fclose(in);
        fclose(out);
    }
    return 0;
}