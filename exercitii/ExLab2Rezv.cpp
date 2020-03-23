/*
Modalitate de punctare:
- daca rezolvarea exercitiului se face cu citirea informatiilor din fisier 0.1 din punctajul pentru activitate seminar(max 2p)
- daca rezolvarea exercitiului se face cu citirea informatiilor de la tastatura 0.05 din punctajul pentru activitate seminar(max 2p)

Problema:

Se dau doua fisiere care contin informatii despre candidatii unui concurs de admitere la facultate. Un candidat este format din cnp(sir de caractere statice, dimensiune 14), nume(sir de caractere statice, dimensiune 50) si nota(valoarea reala).
Cele doua fisiere sunt incarcate intr-un program C in doua variabile de tip lista simpla inlantuita. De asemenea, este cunoscut faptul ca continutul celor doua liste la un anumit nod se unifica.

Se doreste sa se implementeze o metoda care sa afiseze la consola candidatul de unificare a celor doua liste. Consideram ca doi candidati sunt identici daca au acelas cnp.

Fiecare fisier este organizat astfel:
- prima linie contine o valoarea intreaga ce reprezinta numarul de candidatii din fisierul respectiv;
- urmatoarele linii contin datele necesare pentru citirea variabilelor de tip Candidat;

Restrictii:
- Problema este rezolvata in fisierul cpp din arhiva
- Pentru rezolvarea cerintei trebuie sa asigurati si implementarea functiilor incomplete din cpp
- Cele doua fisiere de tip text din arhiva sunt utilizate ca date de intrare pentru popularea listelor. Daca nu se doreste incarcarea prin fisier, atunci introduceti de la
tastatura continutul celor doua fisiere
- Functia main din fisierul cpp NU trebuie modificata
- Cititi cu atentie comentariile TODO din fisierul cpp pentru rezolvarea problemei

Exemplu:

Fisier1:
2
1971212123123
Popescu Ionel
10.0
2971212123111
Ionescu Alina
9.45

Fisier2:
3
1970101123111
Marcu Victor
6.57
1971212123123
Popescu Ionel
10.0
2971212123111
Ionescu Alina
9.45

Programul afiseaza la consola:
1971212123123
Popescu Ionel
10.0

- elementul de pe pozitia 1 din Fisier1, respectiv pozitia 2 din Fisier2. Au acelas CNP
*/

#define _CRT_SECURE_NO_WARNINGS 
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Candidat {
	char cnp[14];
	char nume[50];
	float nota;
};

struct nod {
	Candidat info;
	nod* next;
};

Candidat citire_candidat(FILE* fisier) {
	Candidat c;
	fgetc(fisier);
	fgets(c.cnp, 14, fisier);
	strtok(c.cnp, "\n");
	fgetc(fisier);
	fgets(c.nume, 50, fisier);
	strtok(c.nume, "\n");
	fscanf_s(fisier, "%f", &c.nota);
	return c;
}

nod* initializare_lista(const char* nume_fisier) {
	//TODO: Daca alegeti citirea din fisier, in aceasta zona se declara, initializeaza si apeleaza toate metodele necesare pentru lucru cu fiser
	FILE* fisier;
	fopen_s(&fisier, nume_fisier, "r");
	if (fisier != NULL) {
		nod* cap = NULL;
		int nr = 0;
		//TODO: Citire numar candidati. Din fisier/tastatura 
		fscanf_s(fisier, "%d", &nr);
		if (nr > 0) {
			cap = (nod*)malloc(sizeof(nod));
			cap->next = NULL;
			//TODO: apel citire candidat fisier/tastatura
			cap->info = citire_candidat(fisier);
			nod *cursor, *nou;
			cursor = cap;
			for (int i = 1; i < nr; i++) {
				nou = (nod*)malloc(sizeof(nod));
				nou->next = NULL;
				//TODO: apel citire candidat fisier/tastatura
				nou->info = citire_candidat(fisier);
				cursor->next = nou;
				cursor = nou;
			}
		}
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
		printf("\n %s %s %2.2f", cursor->info.cnp, cursor->info.nume, cursor->info.nota);
		cursor = cursor->next;
	}
}

void dezalocare(nod* cap) {
	nod* sters;
	while (cap != NULL) {
		sters = cap;
		cap = cap->next;
		free(sters);
	}
}

//TODO: Puteti modifica doar tipul si numarul paramterilor de intrare
int identificare_punct_unificare(nod* cap_1, nod* cap_2, Candidat& rezultat) {
	if (cap_1 != NULL && cap_2 != NULL) {
		nod* cursor_1 = cap_1;
		nod* cursor_2 = NULL;
		while (cursor_1 != NULL) {
			cursor_2 = cap_2;
			while (cursor_2 != NULL) {
				if (strcmp(cursor_1->info.cnp, cursor_2->info.cnp) == 0) {
					rezultat = cursor_1->info;
					return 1;
				}
				cursor_2 = cursor_2->next;
			}
			cursor_1 = cursor_1->next;
		}
	}
	else {
		printf("\n NU exista punct de unificare deoarece cel putin o lista este goala");
	}

	return -1;
}

void main() {
	nod* cap1 = initializare_lista("lista1.txt");
	printf("\nAfisare lista 1: ");
	afisare_lista(cap1);
	nod* cap2 = initializare_lista("lista2.txt");
	printf("\nAfisare lista 2: ");
	afisare_lista(cap2);
	Candidat nod_unificare;
	int rezultat = identificare_punct_unificare(cap1, cap2, nod_unificare);
	if (rezultat == 1) {
		printf("\nNodul de unificare este: %s %s %2.2f ", nod_unificare.cnp, nod_unificare.nume, nod_unificare.nota);
	}
	else {
		printf("\n NU am identificat un punct de unificare");
	}
	dezalocare(cap1);
	dezalocare(cap2);
}