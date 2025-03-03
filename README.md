# City-Network-Degradation-and-Pathfinding-Algorithms-in-C
# Managementul rețelelor bazate pe grafuri și găsirea de drumuri optime în C

Acest proiect implementează algoritmi de graf pentru gestionarea unei rețele de orașe, urmărind degradarea secțiunilor de drum și găsirea drumurilor optime între orașe. Se concentrează pe simularea și gestionarea conexiunilor dintre orașe, analiza condiției drumurilor și furnizarea de capabilități de căutare a celor mai scurte drumuri folosind algoritmul Dijkstra.

## Cerința 1

- **`initList`**: Funcția inițializează fiecare element din lista de adiacență a unui nod din graf, având ca element stocat o structură ce conține informații despre numărul de tronsoane, poziția orașului, indexul tronsonului și doi vectori, unul în care se ține starea degradării unui tronson și o mască a acestui vector.
- **`adaugareSfarsit`**: Adaugă un nod în lista de adiacență.
- **`initGraph`**: Inițializează graful, stocând numărul de rute, numărul de ani, uzura maximă acceptabilă și un număr maxim de 2 * numărul de rute, fiind maximul posibil de noduri.
- **`exista`**: Verifică dacă orașul există deja în lista de orașe unice. Dacă există, returnează indexul acestuia, altfel îl adaugă.
- **`citireOrase`**: Citește două orașe pentru fiecare rută, verifică dacă există în lista de orașe unice și le adaugă dacă nu sunt deja prezente, actualizând indexurile și conexiunile dintre ele.
- **`inversare`**: După calcularea fiecărui tronson de la A la B, funcția inversează astfel încât tronsonul de la B la A să fie actualizat.
- **`cautareSfarsit`**: Căutăm în lista de vecini ai orașului B și adăugăm primul element din fiecare vecin al lui B. Apoi, se returnează valoarea maximă dintre ele pentru a o folosi în calculul următor.
- **`cautareinceput`**: Similar cu `cautareSfarsit`, dar se face căutarea în vecinii orașului A.
- **`cautareambeleparti`**: Funcție care verifică cazurile în care tronsonul are doar un singur element, căutând în ambii vecini și returnând maximul dintre ele.
- **`comparare`**: Funcție de comparare utilizată pentru sortare, în cadrul algoritmului `qsort`.
- **`copieremasca`**: Funcție care actualizează vectorul de tronsoane de la un an la altul, folosind o copie a vectorului de mască pentru a evita actualizările inutile la fiecare iterație.
- **`cerinta1`**: Implementarea principală a cerinței 1. Se actualizează vectorii de tronsoane pentru fiecare an, calculându-se maximul dintre tronsoane și actualizându-le în mod corespunzător.
- **`afisare`**: Afișează starea de degradare a tronsoanelor între fiecare pereche de orașe.
- **`medie`**: Calculează media tronsoanelor și afișează indexul tronsonului dacă media este sub pragul maxim.
- **`freeMemory`**: Eliberează memoria alocată pentru graf, orașele unice și listele de adiacență.

## Cerința 2

- Pentru această cerință, s-au utilizat structuri de date noi pentru graf și listele de adiacență. Algoritmul principal folosit este Dijkstra, implementat cu ajutorul unui min-heap pentru găsirea celui mai scurt drum între două orașe.
- **`citireDate`**: Citește datele în același mod ca în cerința 1, doar că structurile de date sunt diferite.
- **`muchie`**: Verifică dacă există o muchie între două orașe, returnând 1 dacă există și 0 în caz contrar.
- **`distanta`**: Calculează distanța între două orașe folosind algoritmul Dijkstra. Dacă nu există o conexiune directă, returnează infinit.
- **`Dijkstra`**: Aplică algoritmul Dijkstra pentru a găsi cele mai scurte distanțe de la un nod de start la alte noduri, actualizând distanțele și părinții în min-heap.
- **`fiecareDrum`**: Construiește drumurile de la nodul sursă la fiecare destinație, adăugând parinții fiecărui nod într-un vector pentru a obține drumul complet.
- **`freeElements`**: Eliberează memoria pentru elementele din graf și listele de adiacență.

În fișierul `tema3.c` se află apelarea funcțiilor prezentate mai sus pentru a obține output-ul dorit.

---

    
