#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerinta2.h"
#include "cerinta1.h"

#define inf 1000000

// Initializare transport
Transport initTransp(int V, int maximCai) {
	int i;
    Transport t = (Transport) malloc(sizeof(struct transport));
    if (t == NULL) {
        exit(-1);
    }
	t->numarCai = V;
    t->maximCai = maximCai;
	t->caiVecine = (Nod *) malloc(t->numarCai * 2 * sizeof(struct node *));
    if (t->caiVecine == NULL) {
        exit(-1);
    }
	for (i = 0; i < t->numarCai * 2; ++i)
		t->caiVecine[i] = NULL;
	return t;
}

//functie pentru adaugarea unui oras in lista de vecini
Nod adaugareOras(Nod list, Pereche p) {
    Nod nou = (Nod) malloc(sizeof(struct node));
    if (nou == NULL) {
        exit(-1);
    }
    if(list == NULL) {
        nou->detaliiCale = p;
        nou->next = NULL;
        nou->prev = NULL;
        nou->vizitat = 0;
        return nou;
    }
    nou->detaliiCale = p;
    nou->vizitat = 0;
    nou->next = list;
    list->prev = nou;
    nou->prev = NULL;
    return nou;
}

//functie pentru verificarea existentei unui oras in vectorul de
//orase totale
int verificareExistenta(Transport t,char *oras, char **cai) {
    int i;
    for (i = 0; i < t->numarCai * 2; ++i)
        if(strcmp(oras, cai[i]) == 0)
            return i;
    return -1;


}

//functie pentru gasirea indexului unui oras in vectorul de orase
int gasireIndex(char *start, char **orase, int numarOrase) {
    int i;
    for (i = 0; i < numarOrase; ++i) {
        if (strcmp(start, orase[i]) == 0)
            return i;
    }
    return 0;
}

//functie pentru citirea input-ului, asemenator cu cerinta1
void citireDate(Transport t, FILE *in, char **cai, char** caiTotale) {
    int i, poz = 0, index1, index2, distanta, pozSupl = 0;
    Pereche detaliiCale;
    for(i = 0; i < t->numarCai; ++i) {
        char oras1[100], oras2[100];
        fscanf(in, "%s %s %d ", oras1, oras2, &distanta);
        //verific daca orasele exista deja in vectorul de orase
        if ((index1 = verificareExistenta(t, oras1, cai)) == -1) {
            //daca nu exista, le adaug in vectorul de orase
            strcpy(cai[poz], oras1);
            //indexul orasului este pozitia in vectorul de orase
            index1 = poz;
            poz++;
        }
        //analog pentru al doilea oras
        if ((index2 = verificareExistenta(t, oras2, cai)) == -1) {
            strcpy(cai[poz], oras2);
            index2 = poz;
            poz++;
        }
        detaliiCale.numarOrdine = i;
        detaliiCale.vizitat = 0;
        detaliiCale.distanta = distanta;
        detaliiCale.oras = index2;
        //adaug in lista de vecini a orasului 1 orasul 2
        t->caiVecine[index1] = adaugareOras(t->caiVecine[index1], detaliiCale);

        detaliiCale.oras = index1;
        //adaug in lista de vecini a orasului 2 orasul 1
        t->caiVecine[index2] = adaugareOras(t->caiVecine[index2], detaliiCale);
        //pun in vectorul de orase totale orasele neunificate
        strcpy(caiTotale[pozSupl++], oras1);
        strcpy(caiTotale[pozSupl++], oras2);
    }
    //
    t->numarOrase = poz;
}



// Initializare heap
 Heap initHeap(int capacity) {
 	Heap h = (Heap) malloc(sizeof(struct heap));
    if (h == NULL) {
        exit(-1);
    }
 	h->size = 0;
    h->vector = (Pereche *) malloc(capacity * sizeof(Pereche));
    if (h->vector == NULL) {
        exit(-1);
    }
 	h->capacity = capacity;
 	return h;
 }

//functie pentru shiftarea unui element in heap in sus
Heap shiftUp(Heap h, int index) {
    int parent = (index - 1) / 2;
    while (index >= 0 && h->vector[parent].distanta > h->vector[index].distanta)
    {
        Pereche aux = h->vector[parent];
        h->vector[parent] = h->vector[index];
        h->vector[index] = aux;
        index = parent;
        parent = (index - 1) / 2;
    }
    return h;
}

//functie pentru inserarea unui element in heap
Heap insertHeap(Heap h, Pereche p) {
    if (h->size == h->capacity) {
        h->capacity = h->capacity * 2;
        h = realloc(h, h->capacity * sizeof(int));
    }
	h->vector[h->size] = p;
	h = shiftUp(h, h->size);
	h->size++;
	return h;
}

//functie pentru shiftarea unui element in heap in jos
Heap shiftDown(Heap h, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int max = index;
    if (left < h->size && h->vector[left].distanta < h->vector[max].distanta) {
        max = left;
    }
    if (right < h->size && h->vector[right].distanta < h->vector[max].distanta) {
        max = right;
    }
    if (max != index) {
        Pereche aux = h->vector[max];
        h->vector[max]= h->vector[index];
        h->vector[index] = aux;
        h = shiftDown(h, max);
    }
    return h;
}

//functie pentru stergerea unui element din heap
void remove_from_heap(Heap h, int i) {
    if (i < h->size) {
        h->vector[i] = h->vector[h->size - 1];
        h->size--;
        h = shiftDown(h, i);
    }
}


//functie pentru extragerea minimului din heap
Pereche extract_min(Heap h, int index) {
    Pereche min = h->vector[0];
    h->vector[index] = h->vector[h->size - 1];
    h->size--;
    h = shiftDown(h, 0);
    return min;
}

//functie pentru verificarea daca heap-ul este gol
int isEmptyHeap(Heap h) {
	return h == NULL || h->size == 0;
}

//  functie pentru verificarea existentei unei muchii intre 2 orase
int muchie(Transport t, int i, int j) {
    Nod tmp = t->caiVecine[i];
    while(tmp) {
        if(tmp->detaliiCale.oras == j)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

//functie pentru calcularea distantei dintre 2 orase
int distanta(Transport t, int i, int j) {
    Nod tmp = t->caiVecine[i];
    while(tmp) {
        if(tmp->detaliiCale.oras == j)
            return tmp->detaliiCale.distanta;
        tmp = tmp->next;
    }
    return inf;

}


void Dijkstra(Transport t, int start, int *d, int *parinte, Heap q) {
    int i;
    int *viz = calloc(t->numarOrase, sizeof(int));
    viz[start] = 1;
    Heap h = initHeap(t->numarOrase);
    Pereche p;
    for (i = 0; i < t->numarOrase; ++i) {
        //daca nodul este start, distanta este 0
        if (i == start) {
            d[i] = 0;
            parinte[i] = -1;
        }
        //daca exista muchie intre start si i, distanta este distanta dintre ele
        else if (muchie(t, start, i)) {
            d[i] = distanta(t, start, i);
            parinte[i] = start;
            //iau numarul de ordine pentru a sti ce pereche sa o afisez
            Nod tmp = t->caiVecine[start];
            while(tmp->detaliiCale.oras != i)
                tmp = tmp->next;
            p.numarOrdine = tmp->detaliiCale.numarOrdine;
            p.oras = i;
            p.distanta = d[i];
            //adaug in heap
            h = insertHeap(h, p);
            q = insertHeap(q, p);
        }
        //daca nu exista muchie, distanta este infinit
        else {
            d[i] = inf;
            parinte[i] = -1;
        }
    }
    //cat timp heap-ul nu este gol
    while(!isEmptyHeap(h)) {
        Pereche min = extract_min(h, 0);
        //marchez orasul ca vizitat
        viz[min.oras] = 1;
        for (i = 0 ; i < t->numarOrase; ++i) {
            //daca orasul nu este vizitat si distanta este mai mare decat distanta minima
            // + distanta dintre ele
            if (viz[i] == 0 && d[i] > d[min.oras] + distanta(t, min.oras, i)) {
                //actualizez distanta si parintele
                d[i] = d[min.oras] + distanta(t, min.oras, i);
                p.oras = i;
                Nod tmp = t->caiVecine[min.oras];
                while(tmp->detaliiCale.oras != i)
                    tmp = tmp->next;
                p.numarOrdine = tmp->detaliiCale.numarOrdine;
                parinte[i] = min.oras;
                p.distanta = d[i];
                //adaug in heap
                h = insertHeap(h, p);
                q = insertHeap(q, p);
            }
        }
    }
    free(h->vector);
    free(h);
    free(viz);
}


//functie recursiva pentru a adauga in vectorul drum parintii orasului
//i, pana la orasul start
void adaugareDrum(int *parinte, int i, int *drum, int *pozDrum) {
    if (parinte[i] == -1)
        return;

    adaugareDrum(parinte, parinte[i], drum, pozDrum);
    drum[(*pozDrum)++] = i;

}


void afDrum(Transport t, int *drum, int pozDrum, char **caiTotale, int *v, int *poz) {
    int i;
    //odata ce am drumul, parcurg doua cate doua orasele si adaug in v numarul de ordine al 
    //tronsonului
    for(i = 0; i < pozDrum - 1; ++i) {
        //caut in lista de vecini a orasului drum[i] orasul drum[i+1]
        Nod tmp = t->caiVecine[drum[i]];
        while(tmp->detaliiCale.oras != drum[i+1])
            tmp = tmp->next;
        //daca tronsonul nu a fost vizitat, il adaug in vectorul v
        if (tmp->detaliiCale.vizitat == 0) {
            v[(*poz)++] = tmp->detaliiCale.numarOrdine;
            tmp->detaliiCale.vizitat = 1;
        }
    }
}

//functie pentru a lasa in heap doar un oras cu costul cel mai mic
void verificare(Heap q) {
    int i, j;
    for (i = 0; i < q->size - 1; ++i)
        for (j = i + 1; j < q->size; ++j)
            if (q->vector[i].oras == q->vector[j].oras) {
                if (q->vector[i].distanta < q->vector[j].distanta){
                     remove_from_heap(q, j);
                }
                else{
                    remove_from_heap(q, i);
                }
            }
}


void fiecareDrum(Transport t, FILE *out, int *d, int *parinte, int start, char**caiTotale, Heap q) {
        int i, poz = 0, j;
        int *drum = (int *)calloc(t->numarCai, sizeof(int));
        if (drum == NULL) {
            exit(-1);
        }
        int *v = (int *) calloc(t->numarCai, sizeof(int));
        if (v == NULL) {
            exit(-1);
        }
        drum[0] = start;
        for (i = 0; i < t->numarOrase; i++) {
            if (i != start) {
                int pozDrum = 1;
                adaugareDrum(parinte, i, drum, &pozDrum); // pun intr un vector drumul
                afDrum(t, drum, pozDrum, caiTotale, v, &poz); // pun in vector caiTotale
                 //doar numarultronsonului dintre ele
            }

    }
    qsort(v, poz, sizeof(int), comparare);
    //daca numarul de cai este mai mic decat maximul de cai, afisez toate caiile
    if (poz <= t->maximCai) {
        fprintf(out, "%d\n", poz);
        for(i = 0; i < poz; ++i)
            fprintf(out, "%s %s\n", caiTotale[2*v[i]], caiTotale[2* v[i] + 1]);
    }
    //altfel, afisez doar maximul de cai
    else {
        //verific daca exista doua orase identice ce au numar diferit de cost
        verificare(q);
        //daca da, elimin pe cel cu costul mai mare
        fprintf(out, "%d\n", t->maximCai);
        int *v = (int *) calloc(t->numarCai, sizeof(int));
        int poz = 0;
        //extrag minimul de maximCai ori
        for (j = 0; j < t->maximCai; ++j) {
            Pereche min = extract_min(q, 0);
            v[poz++] = min.numarOrdine;
        }
        //sortez vectorul de ordine
        qsort(v, poz, sizeof(int), comparare);
        for(i = 0; i < poz; ++i)
            printf("%d\n", v[i]);
        for(i = 0; i < poz; ++i)
        //afisez tronsoanele
            fprintf(out, "%s %s\n", caiTotale[2 *v[i]], caiTotale[2 * v[i] + 1]);
        free(v);
    }
    free(drum);
    free(v);
}

void freeElements(Transport t, char **cai, char** caiTotale, int *d, int *parinte) {
    int i;
    for (i = 0; i < t->numarCai * 2; ++i) {
        free(cai[i]);
        free(caiTotale[i]);
        Nod iter = t->caiVecine[i];
        while (iter) {
            Nod tmp = iter;
            iter = iter->next;
            free(tmp);
        }
    }
    free(t->caiVecine);
    free(d);
    free(cai);
    free(caiTotale);
    free(parinte);
    free(t);
}
