//fisierele de test sunt in pachetul /util din git https://github.com/alexandrudita/sdd/tree/master/util
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int id;
	char titlu[50];
	float pret;
};

struct NodVecin;

struct NodGraf {
	Carte info;
	NodVecin* vecini;
	NodGraf* next;
};

struct NodVecin {
	NodGraf* info;
	NodVecin* next;
};

NodGraf* cautaNodGrafDupaCheie(NodGraf* cap, int id) {
	//definim un cursor pentru a nu pierde referinta inceputului de lista
	NodGraf* cursor = cap;
	//parcurgem lista pana cand gasim informatia dorita sau nu mai avem elemente
	while (cursor != NULL && cursor->info.id != id) {
		cursor = cursor->next;
	}
	//return rezultatul identificat
	return cursor;
}

NodGraf* adaugareNodGraf(NodGraf* cap, Carte carte) {
	//alocare spatiu de memorie pentru noul element
	NodGraf* nou = (NodGraf*)malloc(sizeof(NodGraf));
	//adaugare informatiei pe care dorim sa o stocam in nodul de graf
	nou->info = carte;
	//este adaugat la final prin urmare nu are alti frati pe pozitia urmatoare
	nou->next = NULL;
	//initial nu avem vreo muchie adaugata prin urmarea lista de vecini este initializata cu NULL
	nou->vecini = NULL;
	//verificam daca este primul nod al grafului
	if (cap == NULL) {
		return nou;
	}
	//daca nu este primul nod al grafului, definim un cursor si ne pozitionam in lista pe ultimul element.
	//caracteristica specifica ultimul element al listei este ca are valoarea pointerului 'next' NULL
	NodGraf* cursor = cap;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	//legam de lista noul nod
	cursor->next = nou;
	//returnam varful listei
	return cap;
}

NodVecin* adaugareNodVecin(NodVecin* cap, NodGraf* info) {
	//alocare spatiu de memorie pentru noul element
	NodVecin* nou = (NodVecin*)malloc(sizeof(NodVecin));
	//este adaugat la final listei de vecini
	nou->next = NULL;
	//adaugare informatiei pe care dorim sa o stocam in nodul de nodul vecin,
	//adica adresa de memorie a unui nodGraf din lista de noduri ale grafului
	nou->info = info;
	//verificam daca este primul vecini cu care dorim sa construim o muchie pentru acest nod
	if (cap == NULL) {
		return nou;
	}
	//daca nu este primul nod vecin, definim un cursor si ne pozitionam in lista pe ultimul element.
	//caracteristica specifica ultimul element al listei este ca are valoarea pointerului 'next' NULL
	NodVecin* cursor = cap;
	while (cursor->next!=NULL) {
		cursor = cursor->next;
	}
	//legam de lista noul element
	cursor->next = nou;
	//returnam varful listei de tip vecin
	return cap;
}

//pentru un graf un arc/muchie reprezinta legatura dintre 2 noduri ale grafului
//prin urmare avem nevoie de id-urile nodului de start si cel final + varfului listei care contine nodurile grafului
void adaugareArcInGraf(NodGraf* cap, int idStart, int idStop) {
	//validam ca lista de noduri ale grafului nu este goala
	if (cap!=NULL){
		//cautam in lista nodul start conform id-ului primit
		NodGraf* nodStart = cautaNodGrafDupaCheie(cap, idStart);
		//cautam in lista nodul stop conform id-ului primit
		NodGraf* nodStop = cautaNodGrafDupaCheie(cap, idStop);
		//verificam ca am identificat cu succes cele doua noduri
		if (nodStart != NULL && nodStop != NULL) {
			//adaugam in lista de vecini a nodului de start, nodul stop astfel incat sa 
			//trasam o muchide start->stop
			nodStart->vecini = adaugareNodVecin(nodStart->vecini, nodStop);
			//adaugam in lista de vecini a nodului de stop, nodul start astfel incat sa 
			//trasam o muchide stop->start
			nodStop->vecini = adaugareNodVecin(nodStop->vecini, nodStart);
		}
	}
}

void afisareNodVecin(NodVecin* cap) {
	//definim cursor sa nu pierdem referinta varfului
	NodVecin* cursor = cap;
	//parcurgem secvential toata lista si afisam element cu element
	while (cursor != NULL) {
		printf("  %d %s %f\n", cursor->info->info.id,cursor->info->info.titlu, cursor->info->info.pret);
		cursor = cursor->next;
	}
}

void afisarNodGraf(NodGraf* cap) {
	//definim cursor sa nu pierdem referinta varfului
	NodGraf* cursor = cap;
	//parcurgem secvential toata lista si afisam element cu element
	while (cursor != NULL) {
		printf("\n%d %s %f are urmatorii vecini:\n", cursor->info.id,cursor->info.titlu, cursor->info.pret);
		afisareNodVecin(cursor->vecini);
		cursor = cursor->next;
	}
}

int numarNoduri(NodGraf* graf) {
	//definim cursor sa nu pierdem referinta varfului
	NodGraf* cursor = graf;
	int count = 0;
	//parcurgem secvential toata lista si incrementam valoarea variabile count
	while (cursor != NULL) {
		count++;
		cursor = cursor->next;
	}
	//returnam numarul de elemente
	return count;
}

//metoda folosita pentr parcurgerile BF si DF ale grafului
//este necesar sa marcam nodurile pe care le-am procesat astfel incat sa evitam procesarea multipla
int* initializareNoduriVizitate(NodGraf* graf) {
	int nrNoduri = numarNoduri(graf);
	//dimensiunea vectorului de vizitare trebuie sa fie egal cu numarul de noduri
	int* noduriVizitate = (int*)malloc(sizeof(int)*nrNoduri);
	//se intializeaza cu 0 astfel incat sa consideram ca toate nodurile nu sunt procesate
	//daca un nod vizitat are valoarea 1 inseamna ca acesta a fost procesat
	for (int i = 0; i < nrNoduri; i++) {
		noduriVizitate[i] = 0;
	}
	return noduriVizitate;
}

//================================= METODE LISTA CARTE ================================
struct NodCarte {
	Carte info;
	NodCarte* next;
};

NodCarte* adaugareNodCarte(NodCarte* cap, Carte info) {
	//alocare spatiu de memorie pentru noul nod al listei
	NodCarte* nou = (NodCarte*)malloc(sizeof(NodCarte));
	//adaugam informatia pe care dorim sa o stocam in nodul listei
	nou->info = info;
	//noul nod este adaugat la final, prin urmare valoarea pointerului 'next' este NULL
	nou->next = NULL;
	//daca este primul element al listei returnam noul nod
	if (cap == NULL) {
		return nou;
	}
	//definim un cursor pentru a nu pierde varful listei
	NodCarte* cursor = cap;
	//parcurgem lista pana la ultima pozitie
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	//atasam de lista noul nod
	cursor->next = nou;
	//returnam varful listei
	return cap;
}

void afisareNodCarte(NodCarte* cap) {
	//definim un cursor pentru a nu pierde varful listei
	NodCarte* cursor = cap;
	//parcurgem toata lista si afisam informatia din fiecare nod
	while (cursor != NULL) {
		printf("%d %s %f\n", cursor->info.id, cursor->info.titlu, cursor->info.pret);
		cursor = cursor->next;
	}
}

//============================== PARCURGERE DF =================================
//vezi SEMINAR 5 - lucru stiva
struct NodStiva {
	int id;
	NodStiva* next;
};

void pushStiva(NodStiva* &primul, int id) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = NULL;
	if (primul == NULL) {
		primul = nou;
	}
	else {
		nou->next = primul;
		primul = nou;
	}
}

int popStiva(NodStiva* &primul) {
	if (primul) {
		NodStiva* eliminat = primul;
		int id = primul->id;
		primul = primul->next;
		free(eliminat);
		return id;
	}
	return -1;
}
/* PARCURGEREA DF: 
	-> pentru afisarea nodurilor in adancime se foloseste o stiva pentru adaugarea elemente 
	pe care dorim sa le procesam plecand de la un nod de inceput. O procesare presupune adaugarea 
	noduluiProcesat in lista rezultat, adaugarea in stiva a vecinilor directi(cei cu care formeaza o muchie) 
	si marcarea noduluiProcesat cu 1 in vectorul vizitat astfel incat sa evitam multpla procesare
	-> algoritm:
	  1. definire si initializare cu 0 a unui vector vizitate
	  2. adaugare in stiva nod start
	  3. marcare vizitat nod start
	  4. extragerea urmat element din stiva pentru procesare
	  5. adaugare in stiva a vecinilor directi a element extras
	  6. adaugare in lista rezultat a element procesat
	  7. marcheaza toti vecini nodului procesat cu 1 in vectorul vizitat
	  8. repetare pas 4-7 pana cand stiva devine goala
*/
NodCarte* parcurgereAdancime(NodGraf* graf, int idNodStart) {
	if (graf == NULL) {
		return NULL;
	}
	NodCarte* rezultat = NULL;
	int* noduriVizitate = initializareNoduriVizitate(graf);
	NodStiva* stiva = NULL;
	pushStiva(stiva, idNodStart);
	noduriVizitate[idNodStart] = 1;
	while (stiva != NULL) {
		//extragerea urmatorului nod de procesat din stiva
		int idNodCurent = popStiva(stiva);
		//identificare variab NodGraf din graf
		NodGraf* nodCurent = cautaNodGrafDupaCheie(graf, idNodCurent);
		//adaugare in lista de rezultat
		rezultat = adaugareNodCarte(rezultat, nodCurent->info);
		//definim variabila intermediara cu vecinii nodului procesat, pentru a nu pierde structura de tip lista
		NodVecin* cursor = nodCurent->vecini;
		//parcurgem lista vecinilor nodului procesat
		while (cursor != NULL) {
			int idVecin = cursor->info->info.id;
			//daca vecinului nu a fost procesat il marcam ca procesat si il adaugam in stiva
			if (noduriVizitate[idVecin] == 0) {
				//adaugare stiva
				pushStiva(stiva, idVecin);
				//marcare nod procesat
				noduriVizitate[idVecin] = 1;
			}
			//trecem la urmatorul vecin
			cursor = cursor->next;
		}
	}
	return rezultat;
}

//============================== PARCURGERE BF =================================
//vezi SEMINAR 5 - lucru coada
struct NodCoada {
	int id;
	NodCoada* next;
};

void pushCoada(NodCoada* &primul, NodCoada* &ultimul, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (primul == NULL && ultimul == NULL) {
		primul = nou;
		ultimul = nou;
	}
	else {
		ultimul->next = nou;
		ultimul = nou;
	}
}
int popCoada(NodCoada* &primul, NodCoada* &ultimul) {
	if (primul!=NULL) {
		NodCoada* eliminat = primul;
		int id = primul->id;
		primul = primul->next;
		if (primul == NULL) {
			ultimul = NULL;
		}
		//dezalocare pointer eliminat
		free(eliminat);
		return id;
	}
	return -1;
}
/* PARCURGEREA BF:
	-> pentru afisarea nodurilor in latime se foloseste o coada pentru adaugarea elemente
	pe care dorim sa le procesam plecand de la un nod de inceput. O procesare presupune adaugarea
	noduluiProcesat in lista rezultat, adaugarea in coada a vecinilor directi(cei cu care formeaza o muchie)
	si marcarea noduluiProcesat cu 1 in vectorul vizitat astfel incat sa evitam multipla procesare
	-> algoritm:
	  1. definire si initializare cu 0 a unui vector vizitate
	  2. adaugare in coada nod start
	  3. marcare vizitat nod start
	  4. extragerea urmat element din coada pentru procesare
	  5. adaugare in coada a vecinilor directi a element extras
	  6. adaugare in lista rezultat a element procesat
	  7. marcheaza toti vecini nodului procesat cu 1 in vectorul vizitat
	  8. repetare pas 4-7 pana cand coada devine goala
*/
NodCarte* parcurgereLatime(NodGraf* graf, int idNodStart) {
	if (graf == NULL) {
		return NULL;
	}
	NodCarte* rezultat = NULL;
	int* noduriVizitate = initializareNoduriVizitate(graf);
	NodCoada *primul = NULL, *ultimul = NULL;
	pushCoada(primul, ultimul, idNodStart);
	noduriVizitate[idNodStart] = 1;
	while (primul != NULL) {
		//extragerea urmatorului nod de procesat din coada
		int idNodCurent = popCoada(primul, ultimul);
		//identificare variab NodGraf din graf
		NodGraf* nodCurent = cautaNodGrafDupaCheie(graf, idNodCurent);
		//adaugare nodCurent in lista rezultat
		rezultat = adaugareNodCarte(rezultat, nodCurent->info);
		//definim variabila intermediara in care punem vecinii nodului curent. 
		//Facem acest lucru pentru a nu pierde referinta varfului 
		//astfel incat sa putem procesa si alte operatii cu vecinii nodului curent
		NodVecin* cursor = nodCurent->vecini;
		//parcurgem lista de vecini
		while (cursor != NULL) {
			int idVecin = cursor->info->info.id;
			//daca vecinul nu a fost deja procesat il adaugam in coada si il marcam ca procesat
			if (noduriVizitate[idVecin] == 0) {
				//adaugare in coada a elementului vecin
				pushCoada(primul, ultimul, idVecin);
				//marcam vecinul ca vizitat
				noduriVizitate[idVecin] = 1;
			}
			//trecem la urmatorul vecin
			cursor = cursor->next;
		}
	}
	return rezultat;
}

Carte citesteCarteFisier(FILE* fisier) {
	Carte c;
	fscanf_s(fisier, "%d", &c.id);
	fgetc(fisier);
	fgets(c.titlu, 50, fisier);
	//eliminam caracter \n care apare in fisierle text
	strtok(c.titlu, "\n");
	fscanf_s(fisier, "%f", &c.pret);
	return c;
}

NodGraf* citesteNodGrafFisier() {
	int n = 0;
	NodGraf* graf = NULL;
	Carte carte;
	FILE* fisier;
	//deschidere fisier
	fopen_s(&fisier, "carti.txt", "r");
	if (fisier != NULL) {
		//preluam numarul de noduri
		fscanf_s(fisier, "%d", &n);
		//citim informatiile fiecarui noid si le adaugam in lista de noduri ale grafului
		for (int i = 0; i < n; i++) {
			carte = citesteCarteFisier(fisier);
			graf = adaugareNodGraf(graf, carte);
		}
		//inchidem fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
	//returnam graf
	return graf;
}

void citesteMuchiiGrafFisier(NodGraf* &graf) {
	FILE* fisier;
	fopen_s(&fisier, "graf.txt", "r");
	if (fisier != NULL) {
		int nr_muchii;
		int idStart;
		int idStop;
		//citim numarul de muchii din fisier
		fscanf_s(fisier, "%d", &nr_muchii);
		//citim combinatiile nodStart si nodStop din fisierul graf.txt
		//pentru a prelua muchiile dintre nodurile grafului
		for (int i = 0; i < nr_muchii; i++) {
			fscanf_s(fisier, "%d %d", &idStart, &idStop);
			adaugareArcInGraf(graf, idStart, idStop);
		}
		//inchidem fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

void main() {
	printf("\n========================CITIRE NODURI GRAF===============================\n");
	NodGraf* graf = citesteNodGrafFisier();
	afisarNodGraf(graf);
	printf("\n========================ADAUGARE MUCHII===============================\n");
	citesteMuchiiGrafFisier(graf);
	afisarNodGraf(graf);
	printf("\n==========================PARCURGERE DF=============================\n");
	NodCarte* capDf = parcurgereAdancime(graf, 1);
	afisareNodCarte(capDf);
	printf("\n==========================PARCURGERE BF=============================\n");
	NodCarte* capBf = parcurgereLatime(graf, 1);
	afisareNodCarte(capBf);
}
