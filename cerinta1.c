#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerinta1.h"

//functie de initializare a unui nod
List initList(Tronsoane p) {
    List l;
    l = (List) malloc(sizeof(struct list));
    if (l == NULL) {
        exit(-1);
    }
    l->detaliiTronsoane = p;
    l->next = l->prev = NULL;
    return l;
}

//functie de adaugare la sfarsit a unui nod
List adaugareSfarsit(List l, Tronsoane p) {
    if (l == NULL)
        return initList(p);
    List nou, iter = l;
    nou = (List)malloc(sizeof(struct list));
    if (nou == NULL) {
        exit(-1);
    }
    while (iter->next) {
        iter = iter->next;
    }
    iter->next = nou;
    nou->prev = iter;
    nou->next = NULL;
    nou->detaliiTronsoane = p;
    return l;
}

//functie de initializare a unui graf
Graph initGraph(int numarRute, int numarAni, int uzuraAcceptabila) {
    Graph g;
    g = (Graph) malloc(sizeof(struct graph));
    if (g == NULL) {
        exit(-1);
    }
    int i;
    g->numarRute = numarRute;
    g->numarAni = numarAni;
    g->uzuraAcceptabila = uzuraAcceptabila;
    g->oraseVecine = (List*) malloc(g->numarRute * 2 * sizeof(List));
    if (g->oraseVecine == NULL) {
        exit(-1);
    }
    for (i = 0 ; i < g->numarRute * 2; ++i) {
        g->oraseVecine[i] = NULL;
    }
    return g;
}

//functie de verificare daca un oras exista deja in vectorul de orase
int exista(Graph g, char *aux, char **orase) {
    int i;
    for (i = 0 ; i < g->numarRute * 2; ++i) {
        if (strcmp(aux, orase[i]) == 0)
            return i;
    }
    return -1;

}

//functie de citire a oraselor si tronsoanelor
void citireOrase(Graph g, char **orase, char**toateorase, FILE *f) {
    int i, j, poz = 0, index1, index2, pozsuplim = 0;
    for (i = 0; i < g->numarRute; ++i){
        Tronsoane p;
        char aux[100], aux2[100];
        fscanf(f, "%s %s %d ", aux, aux2, &p.numarTronsoane);
        //daca index = -1, inseamna ca nu exista, si il adaug in vectorul de orase
        if ((index1 = exista(g, aux, orase)) == -1) {
            strcpy(orase[poz], aux);
            index1 = poz;
            poz++;
        }
        //daca e diferit de -1, inseamna ca exista deja, si iau indexul
        if ((index2 = exista(g, aux2, orase)) == -1) {
            strcpy(orase[poz], aux2);
            index2 = poz;
            poz++;
        }
        p.pozitie = index2;
        for(j = 0; j < p.numarTronsoane; ++j)
            fscanf(f, "%f ", &p.tronsoane[j]);
        p.indexTronson = i + 1;
        //adaug in lista de vecini a orasului 1 orasul 2 si invers
        g->oraseVecine[index1] = adaugareSfarsit(g->oraseVecine[index1], p);
        g->numarVecini[index1]++;
        p.pozitie = index1;
        float *auxiliar = (float *)malloc(p.numarTronsoane * sizeof(float));
        if (auxiliar == NULL) {
            exit(-1);
        }
        //inversez tronsoanele pentru a le adauga in lista de vecini a orasului 2
        for (j = 0; j < p.numarTronsoane; ++j) 
            auxiliar[j] = p.tronsoane[p.numarTronsoane - j - 1];
        for (j = 0 ; j< p.numarTronsoane; ++j)
            p.tronsoane[j] = auxiliar[j];
        //adaug in lista de vecini a orasului 2 orasul 1
        g->oraseVecine[index2] = adaugareSfarsit(g->oraseVecine[index2], p);
        g->numarVecini[index2]++;
        strcpy(toateorase[pozsuplim++], aux);
        strcpy(toateorase[pozsuplim++], aux2);
        free(auxiliar);
    }
    //numarul total de orase
    g->numarOrase = poz;
}

void copieremasca(Graph g);



//functie de inversare a tronsoaelor
void inversare(float *tronsonActualizat, Graph orasNou, int pozitieNoua, int pozitieVeche) {
    List iter = orasNou->oraseVecine[pozitieNoua];
    List tmp = iter;
    int i;
    while (iter->detaliiTronsoane.pozitie != pozitieVeche) {
        tmp = iter;
        iter = iter->next;
    } // in tmp o sa am pointer de la orasul 2 la orasul 1 si astfel modific
    float aux[SIZE];
    for (i = 0; i < tmp->detaliiTronsoane.numarTronsoane; ++i) {
        aux[i] = tronsonActualizat[iter->detaliiTronsoane.numarTronsoane - i - 1];
    }
    for (i = 0; i < tmp->detaliiTronsoane.numarTronsoane; ++i) {
        iter->detaliiTronsoane.tronsoane[i] = aux[i];
    }


}

//functie de cautare a maximului in vecinii orasului 2
//si de adaugare a acestuia intr un vector
float cautaresfarsit(List l, Graph g, int pozitieAnterioara) {
    List tmp = l;
    int poz = 0;
    float v[SIZE];
    //parcurg lista de vecini a orasului 2
    while (tmp) {
        //daca pozitia vecinului nu este cea a orasului 1, adaug in vector
        if (tmp->detaliiTronsoane.pozitie != pozitieAnterioara) {
            v[poz++] = tmp->detaliiTronsoane.masca[0]; 
        }
        tmp = tmp->next;
    }
    //daca am vecini, caut maximul
    if(poz != 0) {
        float maxim = v[0];
        int i;
        for(i = 1; i < poz; ++i) {
            if (v[i] > maxim)
                maxim = v[i];
        }
        return maxim;
    }
    //daca nu am vecini, returnez 0
    return 0;
}

//functie de copiere a mastilor in tronsoane
//pentru a putea fi folosite in calcularea uzurii
//si de marcare a oraselor ca fiind nevizitate


//functie de cautare a maximului in vecinii orasului 1
float cautaresinceput(List l, Graph g, int pozitieAnterioara) {
    List tmp = l;
    int poz = 0;
    float *v = (float*) calloc(g->numarOrase , sizeof(float));
    if (v == NULL) {
        exit(-1);
    }
    //parcurg lista de vecini a orasului 1
    while (tmp) {
        //daca pozitia vecinului nu este cea a orasului 2, adaug in vector
        if (tmp->detaliiTronsoane.pozitie != pozitieAnterioara) {
            v[poz++] = tmp->detaliiTronsoane.masca[0]; 
        }
        tmp = tmp->next;
    }
    //daca am vecini, caut maximul
    if (poz != 0) {
        int i;
        float maxim = v[0];
        for(i = 1; i < poz; ++i) {
            if (v[i] > maxim)
                maxim = v[i];
        }
        free(v);
        return maxim;
    }
    free(v);
    //daca nu am vecini, returnez 0
    return 0;
}

//functie de cautare a maximului in vecinii orasului 1 si 2
//daca am doar un tronson cu 0, caut maximul in vecinii ambelor orase
float cautareambeleparti(List l, List q) {
    List tmp = l;
    int poz = 0;
    float v[100];
    //parcurg lista de vecini a orasului 1
    while (tmp) {
        //adaug in vector doar primul tronson din vecinii orasului 1
        v[poz++] = tmp->detaliiTronsoane.masca[0]; 
        tmp = tmp->next;
    }
    tmp = q;
    //parcurg lista de vecini a orasului 2
    while (tmp) {
        //adaug in vector doar primul tronson din vecinii orasului 2
        v[poz++] = tmp->detaliiTronsoane.masca[0];
        tmp = tmp->next;
    }
    if (poz != 0) {
        float maxim = v[0];
        int i;
        for(i = 1; i < poz; ++i) {
            if (v[i] > maxim)
                maxim = v[i];
        }
        return maxim;
    }
    return 0;
}

//functie de comparare a doua numere
//pentru a putea fi folosita in qsort
int comparare(const void *a, const void*b) {
    return *(int *)a - *(int*)b;
}


void copieremasca(Graph g) {
    int i, j;
    for(i = 0; i < g->numarOrase; ++i) {
        List tmp = g->oraseVecine[i];
        g->vizitat[i] = 0;
        while (tmp) {
            for(j = 0; j < tmp->detaliiTronsoane.numarTronsoane; ++j) {
                tmp->detaliiTronsoane.masca[j] = tmp->detaliiTronsoane.tronsoane[j];
            }
            tmp = tmp->next;
        }
    }
}

void cerinta1(Graph g) {
    int i, j, k;
    //parcurg fiecare an
    for (k = 0; k < g->numarAni; ++k) {
        //marchez toate orasele ca fiind nevizitate
        //si copiez mastile in tronsoane
        copieremasca(g);
        for (i = 0; i < g->numarOrase; ++i) {
            List tmp = g->oraseVecine[i];
            g->vizitat[i] = 1;
            //pentru fiecare oras, parcurg lista de vecini
            while(tmp) {
                int n = tmp->detaliiTronsoane.numarTronsoane;
                //daca orasul nu a fost vizitat, si are mai mult de un tronson
                if(tmp->detaliiTronsoane.numarTronsoane != 1) {
                    if(g->vizitat[tmp->detaliiTronsoane.pozitie] == 0) {
                        //daca primul tronson este 0, caut maximul in vecinii orasului 1 si in tronson[1]
                        if(tmp->detaliiTronsoane.masca[0] == 0) {
                                float max1 = tmp->detaliiTronsoane.masca[1];
                                float max2 = cautaresinceput(g->oraseVecine[i], g,
                                tmp->detaliiTronsoane.pozitie);
                                    if (max1 > max2) 
                                        tmp->detaliiTronsoane.tronsoane[0] = max1 / 2;
                                    else
                                        tmp->detaliiTronsoane.tronsoane[0] = max2 / 2;
                        } else {
                            //daca primul tronson nu este 0, il dublez
                            if (tmp->detaliiTronsoane.tronsoane[0] * 2 <=100)
                                tmp->detaliiTronsoane.tronsoane[0] *= 2;
                            else
                                tmp->detaliiTronsoane.tronsoane[0] = 100;
                        }
                        if (tmp->detaliiTronsoane.numarTronsoane != 2) {
                            //pentru fiecare tronson, daca este 0, caut maximul in vecinii orasului 
                            //si il adaug in tronson
                            for (j = 1; j < tmp->detaliiTronsoane.numarTronsoane - 1; ++j) {
                                if (tmp->detaliiTronsoane.masca[j] == 0) {
                                    float max1 = tmp->detaliiTronsoane.masca[j - 1];
                                    float max2 = tmp->detaliiTronsoane.masca[j + 1];
                                    if (max1 > max2)
                                        tmp->detaliiTronsoane.tronsoane[j] = max1 / 2;
                                    else
                                        tmp->detaliiTronsoane.tronsoane[j] = max2 / 2;
                                } else {
                                    if (tmp->detaliiTronsoane.tronsoane[j] * 2 <= 100)
                                        tmp->detaliiTronsoane.tronsoane[j] *= 2;
                                    else
                                        tmp->detaliiTronsoane.tronsoane[j] = 100;

                                }
                            }
                        }
                        //pentru ultimul tronson, daca este 0, caut maximul in vecinii orasului 2 si il adaug in tronson
                        if (tmp->detaliiTronsoane.masca[n - 1] == 0) {
                                float max1 = tmp->detaliiTronsoane.masca[n - 2];
                                float max2 = cautaresfarsit(g->oraseVecine[tmp->detaliiTronsoane.pozitie], g, i);
                                    if (max1 > max2){ 
                                        tmp->detaliiTronsoane.tronsoane[n - 1] = max1 / 2;
                                    }else
                                        tmp->detaliiTronsoane.tronsoane
                                        [tmp->detaliiTronsoane.numarTronsoane - 1] = max2 / 2;
                        } else {
                            //daca ultimul tronson nu este 0, il dublez
                            if (tmp->detaliiTronsoane.tronsoane[n - 1] * 2 <= 100)
                                tmp->detaliiTronsoane.tronsoane[n - 1] *= 2;
                            else
                                tmp->detaliiTronsoane.tronsoane[n - 1] = 100;
                        }
                        inversare(tmp->detaliiTronsoane.tronsoane, g, tmp->detaliiTronsoane.pozitie, i);
                    }

                } else {
                    //daca orasul are un singur tronson, caut maximul in vecinii ambelor orase
                    if (tmp->detaliiTronsoane.tronsoane[0] == 0) {
                        float maxim = cautareambeleparti(g->oraseVecine[i], 
                        g->oraseVecine[tmp->detaliiTronsoane.pozitie]) / 2;
                        tmp->detaliiTronsoane.tronsoane[0] = maxim;
                    } else {
                        if(tmp->detaliiTronsoane.tronsoane[0] * 2 <= 100)
                            tmp->detaliiTronsoane.tronsoane[0] *= 2;
                        else
                            tmp->detaliiTronsoane.tronsoane[0] = 100;
                    }
                }
                //trec la urmatorul oras
                tmp = tmp->next;
            }

        }
    }
}

void afisare(Graph g, char **nume, char**oraseTotale, FILE *out) {
    //marchez toate orasele ca fiind nevizitate
    copieremasca(g);
    int poz1, poz2, i, j, k;
    //pentru fiecare oras, din 2 in 2, in vectorul de orasetotale, caut indexul orasului in
    //vectorul de orase si al celui de langa el, pentru a le afisa ca in starea de input
    for(i = 0 ; i < g->numarRute * 2; i+=2){
        for (j = 0; j < g->numarOrase; ++j) {
            if (strcmp(oraseTotale[i], nume[j]) == 0)
                poz1 = j;
            if (strcmp(oraseTotale[i + 1], nume[j]) == 0)
                poz2 = j;
        }
        fprintf(out, "%s %s ", oraseTotale[i], oraseTotale[i + 1]);
        // parcurg lista de vecini a orasului 1 pana dau de orasul 2
        // si afisez tronsoanele
        List temp = g->oraseVecine[poz1];
        while (temp->detaliiTronsoane.pozitie != poz2) {
            temp = temp->next;
        }
        fprintf(out, "%d", temp->detaliiTronsoane.numarTronsoane);
        for (k = 0; k < temp->detaliiTronsoane.numarTronsoane; ++k)
            fprintf(out, " %0.2f", temp->detaliiTronsoane.tronsoane[k]);
        fprintf(out, "\n");
    }
}

//functie de eliberare a memoriei pentru graf si vectorii de orase
void freeMemory(Graph g, char **orase, char **oraseTotale) {
    int i;
    for(i = 0; i < g->numarOrase; ++i) {
        List iter = g->oraseVecine[i];
        while (iter) {
            List tmp = iter;
            iter = iter->next;
            free(tmp);
        }
    }
    free(g->oraseVecine);

    for(i = 0; i < 2 * g->numarRute; ++i) {
        free(orase[i]);
        free(oraseTotale[i]);
    }
    free(orase);
    free(g);
    free(oraseTotale);
}


//functie de calculare a mediei tronsoanelor
void medie(Graph g, FILE *out) {
    int *pozitii = (int *) malloc(g->numarOrase * sizeof(int));
    if (pozitii == NULL) {
        exit(-1);
    }
    int i, j, poz = 0;
    //pentru fiecare oras, parcurg lista de vecini
    for (i = 0; i < g->numarOrase; ++i) {
        List tmp = g->oraseVecine[i];
        //parcurg lista de vecini a orasului
        while (tmp) {
            float suma = 0, medie = 0;
            int exista = 0;
            //calculez suma tronsoanelor
            for (j = 0; j < tmp->detaliiTronsoane.numarTronsoane; ++j) {
                suma += tmp->detaliiTronsoane.tronsoane[j];
            }
                medie = suma / tmp->detaliiTronsoane.numarTronsoane;
            if (medie < g->uzuraAcceptabila) {
                //daca media este mai mica decat uzura acceptabila, adaug in vectorul de pozitii
                for (j = 0; j < poz; ++j) {
                    if (pozitii[j] == tmp->detaliiTronsoane.indexTronson)
                        exista = 1;
                }
                //daca nu exista, adaug
                if (!exista)
                    pozitii[poz++] = tmp->detaliiTronsoane.indexTronson;
            }
            tmp = tmp->next;
        }
    }
    //sortez vectorul de pozitii si afisez  
    if (poz != 0) {
        qsort(pozitii, poz, sizeof(int), comparare);
        fprintf(out, "%d", pozitii[0]);
        for (i = 1; i < poz; i++) {
            fprintf(out, " %d", pozitii[i]);
        }
    }
    free(pozitii);
}