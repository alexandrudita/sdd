/*
Sa se rezolve urmatoarele cerinte:

1. a. Sa se implementeze o functie care creeaza o lista simpla inlantuita ce stocheaza informatii
despre siruri de caractere preluate dintr-un fisier text.
b. Sa se implementeze o functie noua care citeste de la tastatura un vector static de siruri
de caractere care are o dimensiune de 20 elemente.
c. Sa se implementeze o metoda care sa determine frecventa de aparitie a fiecarui sir de caractere
din vectorul preluat la subpunctul b in lista incarcata la punctul a.
Observatie: Un element din vector este considerat gasit daca si numai daca acesta este egal cu
un element din lista, nu se accepta subsiruri.

Exemplu:
lista: {"abc", "an", "dc", "abc", "abc", "an", "ds"};
vector: {"abc", "an","dd"}
rezultat: {3,2,0} -> am gasit de 3 ori "abc", de 2 ori "an" si 0 ori "dd"

2. Se da un fisier text in care sunt stocate informatii legate de statiunile unei companii.
Structura Statiune este definita astfel: denumire(siruri de caractere alocate dinamic),
tarif(variabila reala), capacitateTuristica(variabila intreaga). Sa se implementeze un program C
care sa efectueze urmatoarele operatii:

a. Citirea unei liste simplu inlantuita circul dintr-un fisier text.
b. Afisarea statiunilor din lista la consola.
c. Sa se implementeze o metoda care genereaza un raport text ce contine pe fiecare linie numele statiunii si venitul total al acesteia, iar pe ultima linie apare venitul total al companiei.
*/

#define _CRT_SECURE_NO_WARNINGS 
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct nod {
	char info[20];
	nod* next;
};

struct statiune {
	char* denumire;
	float tarif;
	int capacitateTuristica;
};

struct nod_circular {
	statiune info;
	nod_circular* next;
};

//cerinta 1.a
nod* initializare_lista_fisier() {
	FILE* fisier;
	fopen_s(&fisier, "tema2_cerinta1.txt", "r");
	//structura fisierului este astfel: prima linie nr de element, dupa care pe fiecare linie valoarea pe care ar trebui sa o folosim pentru construirea listei
	if (fisier != NULL) {
		nod* cap = NULL;
		int nr = 0;
		//citire nr de stringuri din fisier
		fscanf_s(fisier, "%d", &nr);
		if (nr > 0) {
			//initializare cap lista
			cap = (nod*)malloc(sizeof(nod));
			cap->next = NULL;
			//curatare buffer. in versiunile noi de visual studio nu mai functioneaza fflush
			fgetc(fisier);
			fgets(cap->info, 20, fisier);
			//eliminam caracter \n care apare in fisierle text
			strtok(cap->info, "\n");
			nod *cursor, *nou;
			cursor = cap;
			//dupa initializarea capului ar trebui sa parcurgem de la index 1.
			for (int i = 1; i < nr; i++) {
			//se aloca spatiu in memorie pentru noul element din lista
			nou = (nod*)malloc(sizeof(nod));
			//urmatorul element pe care-l pointeaza este NULL
			nou->next = NULL;
			//se adauga informatia dorita in nodul initializat
			fgets(nou->info, 20, fisier);
			//eliminam caracter \n care apare in fisierle text
			strtok(nou->info, "\n");
			//se ataseaza noul element ca fiind urmatorul in lista 
			cursor->next = nou;
			//cursorul isi schimba pozitia pe ultimul element al listei
			cursor = nou;	
			}
		}
		//inchidere fisier
		fclose(fisier);
		return cap;
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

void afisare_lista(nod* cap) {
	nod* cursor = cap;
	while (cursor) {
		printf("\n%s", cursor->info);
		cursor = cursor->next;
	}
}

//cerinta 1.b
void citire_vector_tastatura(char vector[20][20], int &nr) {
	int ok = 1;
	do {
		printf("\n stringul %d ", nr);
		gets_s(vector[nr], 20);
		printf("\nDoriti sa continuati? Da-1/Nu-0 ");
		scanf_s("%d", &ok);
		getc(stdin);
		nr++;
	} while (ok == 1 && nr < 20);
}

//cerinta 1.c
void determinare_frecventa_aparitie(char vector[20][20], int nr, nod* cap) {
	int frecventa = 0;
	//deoarece parcurgerea prin lista este mai rapid, fiind prin pointeri, o sa parcurgem fiecare element
	//din vector si o sa-l cautam in lista
	for (int i = 0; i < nr; i++) {
		//initializam frecventa cu 0 cand schimbam indexul
		frecventa = 0;
		//definim o variabila nod* pentru a traversa lista
		nod* cursor = cap;
		while (cursor) {
			if (strcmp(cursor->info, vector[i]) == 0) {
				frecventa++;
			}
			//schimbare element lista
			cursor = cursor->next;
		}
		//afisare rezultat
		printf("\n textul %s apare de %d ori ", vector[i], frecventa);
	}
}

statiune citire_statiune_fisier(FILE* fisier) {
	statiune s;
	//citire denumire
	char buf[50];
	fgetc(fisier);
	fgets(buf, 50, fisier);
	strtok(buf, "\n");
	int dim = strlen(buf) + 1;
	s.denumire = (char*)malloc(sizeof(char)*dim);
	strcpy(s.denumire, buf);
	//citire tarif
	fscanf_s(fisier, "%f", &s.tarif);
	//citire capacitate turistica
	fscanf_s(fisier, "%d", &s.capacitateTuristica);
	return s;
}

//cerinta 2.a
nod_circular* initializare_lista_statiuni_fisier() {
	FILE* fisier;
	fopen_s(&fisier, "tema2_cerinta2.txt", "r");
	//structura fisierului este astfel: prima linie nr de element, dupa care pe fiecare linie valoarea pe care ar trebui sa o folosim pentru construirea listei
	if (fisier != NULL) {
		nod_circular* cap = NULL;
		int nr = 0;
		//citire nr de statiuni din fisier
		fscanf_s(fisier, "%d", &nr);
		if (nr > 0) {
			//initializare cap lista
			cap = (nod_circular*)malloc(sizeof(nod_circular));
			cap->next = NULL;
			cap->info = citire_statiune_fisier(fisier);
			nod_circular *cursor, *nou;
			cursor = cap;
			//dupa initializarea capului ar trebui sa parcurgem de la index 1.
			for (int i = 1; i < nr; i++) {
				//se aloca spatiu in memorie pentru noul element din lista
				nou = (nod_circular*)malloc(sizeof(nod_circular));
				//urmatorul element pe care-l pointeaza este NULL
				nou->next = NULL;
				//se adauga informatia dorita in nodul initializat
				nou->info = citire_statiune_fisier(fisier);
				//se ataseaza noul element ca fiind urmatorul in lista 
				cursor->next = nou;
				//cursorul isi schimba pozitia pe ultimul element al listei
				cursor = nou;
			}
			//find lista circulara trebuie sa marcam ca ultimul element din lista are next-ul catre cap
			cursor->next = cap;
		}
		//inchidere fisier
		fclose(fisier);
		return cap;
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}
//cerinta 2.b
void afisare_lista_statiuni(nod_circular* cap) {
	nod_circular* cursor = cap;
	do {
		printf("\n %s - %2.2f - %d", cursor->info.denumire, cursor->info.tarif, cursor->info.capacitateTuristica);
		cursor = cursor->next;
	} while (cursor != cap);
}

//cerinta 2.c
void raport(nod_circular* cap) {
	//lucrul cu fisier: se poate folosie fie fopen/fopen_s pentru deschidere. 
	//Mare atentie la ultimul paramteru care reprezinta modalitate de utilizare a fisierului 
	// r-read(nu-l modifica) w-write(suprascrie continutul) 
	// r+ - citire plus modificare
	FILE* fisier;
	fopen_s(&fisier, "raport.txt", "w");
	if (fisier != NULL && cap!=NULL) {
		//variabila intermediara utilizata pentru parcurgere lista
		nod_circular* cursor = cap;
		float venit_total = 0;
		float venit_per_statiune = 0;
		do {
			//calculam venitul statiunii din nodul curent
			venit_per_statiune = cursor->info.tarif*cursor->info.capacitateTuristica;
			//adaugam la venitul total
			venit_total += venit_per_statiune;
			//scriem venitul statiunii din nodul curent in fisier
			fprintf(fisier, "%s %2.2f\n", cursor->info.denumire, venit_per_statiune);
			//mutam cursorul catre urmatorul nod
			cursor = cursor->next;
		} while (cursor != cap);
		//scriem venitul total
		fprintf(fisier,"%2.2f", venit_total);
		//inchidem fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
}

void dezalocare_liste(nod* cap, nod_circular* cap_c) {
	//dezalocam cele 2 liste 
	//pentr cea simpla stergem cap si il schimbam cu urmatorul element pana cand devine null
	if (cap != NULL) {
		nod* sters;
		while (cap != NULL) {
			sters = cap;
			cap = cap->next;
			free(sters);
		}
	}
	//in cazul listei circulare stergem incepand cu al doilea element pana cand ramanem cu cap-ul listei
	//la final stergem capul
	if (cap_c != NULL) {
		nod_circular* sters;
		nod_circular* cursor = cap_c->next;
		while (cursor != cap_c) {
			sters = cursor;
			cursor = cursor->next;
			cap_c->next = cursor;
			free(sters->info.denumire);
			free(sters);
		}
		free(cap_c->info.denumire);
		free(cap_c);
	}
}
void main() {
	////cerinta 1.a
	nod* cap = initializare_lista_fisier();
	afisare_lista(cap);
	//cerinta  1.b
	char vector[20][20];
	int nr = 0;
	citire_vector_tastatura(vector, nr);
	for (int i = 0; i < nr; i++) {
		printf("\n%s", vector[i]);
	}
	//cerinta 1.c
	determinare_frecventa_aparitie(vector, nr, cap);
	//cerinta 2.a
	nod_circular* cap_c=initializare_lista_statiuni_fisier();
	//cerinta 2.b
	afisare_lista_statiuni(cap_c);
	//cerinta 2.c
	raport(cap_c);
	//dezalocare
	dezalocare_liste(cap, cap_c);
}