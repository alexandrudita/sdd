#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct ApelUrgenta {
	int cod;
	int prioritate;
	char adresa[100];
};

struct BinaryTree {
	ApelUrgenta info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

//==================================== GESTIONARE FISIER =========================================

ApelUrgenta citire_apel_urgenta_fisier(FILE* fisier) {
	ApelUrgenta apel;
	fscanf_s(fisier, "%d", &apel.cod);
	fscanf_s(fisier, "%d", &apel.prioritate);
	fgetc(fisier);//fflush
	fgets(apel.adresa, 100, fisier);
	strtok(apel.adresa, "\n");
	return apel;
}

ApelUrgenta citire_apel_urgenta_consola() {
	ApelUrgenta apel;
	printf("\nCod: ");
	scanf_s("%d", &apel.cod);
	printf("\nPrioritate: ");
	scanf_s("%d", &apel.prioritate);
	getc(stdin);
	printf("\nAdresa: ");
	gets_s(apel.adresa, 100);
	return apel;
}

void afisare_apel_urgenta(ApelUrgenta apel) {
	printf("\nCod: %d Prioritate: %d Adresa: %s", apel.cod, apel.prioritate, apel.adresa);
}

ApelUrgenta* citire_apeluri_urgenta_fisier(int &nr) {
	ApelUrgenta* apeluri = NULL;
	//declaram variabila pentru lucru cu fisier
	FILE* fisier;
	//deschidere fisier
	fopen_s(&fisier, "apeluri_urgenta.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier != NULL) {
		//preluare numar de elemente din fisier. Restrictie linia 1 din fisier avem numarul de elemente
		fscanf_s(fisier, "%d", &nr);
		//alocare spatiu de memorie pentru vector
		apeluri = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*nr);
		//citim fiecare element din fisier
		for (int i = 0; i < nr; i++) {
			apeluri[i] = citire_apel_urgenta_fisier(fisier);
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
	return apeluri;
}

void afisare_apeluri_urgenta(ApelUrgenta* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

//==================================== GESTIONARE BINARY TREE =========================================
//creare nod
BinaryTree* creare_nod(ApelUrgenta apel, BinaryTree* stanga, BinaryTree* dreapta) {
	//definire nod nou si alocare spatiu de memorie
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}
//inserare nod
BinaryTree* inserare_nod(ApelUrgenta apel, BinaryTree* radacina) {
	//verificam daca radacina este populata
	if (radacina) {
		//verificam in ce directie ar trebui sa fie adaugat nodul in functie de codul apelului
		//proprietatea cod este utilizata pentru realizarea arborelui
		if (radacina->info.cod > apel.cod) {
			//apelam recursiv pe sub arborele stanga astfel incat sa identificam pozitia in arbore
			radacina->stanga = inserare_nod(apel, radacina->stanga);
		}
		else {
			//apelam recursiv pe sub arborele stanga astfel incat sa identificam pozitia in arbore
			radacina->dreapta = inserare_nod(apel, radacina->dreapta);
		}
		//la final returnam radacina
		return radacina;
	}
	else {
		//nodul radacina este null-> se adauga un nod nou
		return creare_nod(apel, NULL, NULL);
	}
}
//stergere nod

// functie pentru stergerea nodului radacina 
void stergere_nod_radacina(BinaryTree* &radacina)
{
	//salvam radacina intr-un pointer intermediar
	BinaryTree* nod = radacina;
	// daca avem un subarbore drept
	if (nod->dreapta)
	{
		// facem legatura
		radacina = nod->dreapta;
		// daca avem si un subarbore stang
		if (nod->stanga)
		{
			// cautam cel mai mic element din subarborele drept
			BinaryTree* temp = nod->dreapta;
			while (temp->stanga != NULL) temp = temp->stanga;
			// si adaugam subarborele stang
			temp->stanga = nod->stanga;
		}
	}// daca avem doar un subarbore stang
	else if (nod->stanga != NULL) {
		// facem legatura la acesta
		radacina = nod->stanga;
	}
	else {
		// daca nu avem nici un subarbore
		radacina = NULL;
	}
	// stergem vechea radacina
	free(nod);
}

void sterge_nod(BinaryTree* &radacina, int cod) {
	if (radacina != NULL) {
		//verificam daca codul se afla in radacina 
		if (radacina->info.cod == cod) {
			stergere_nod_radacina(radacina);
		}
		else {
			//codul nu se afla in radacina
			BinaryTree * nodCurent = radacina;
			if (cod < nodCurent->info.cod) {
				sterge_nod(nodCurent->stanga, cod);
			}
			else {
				sterge_nod(nodCurent->dreapta, cod);
			}
		}
	}
}
//cautare nod dupa criteriu
ApelUrgenta cautare_cod(BinaryTree* radacina, int cod) {
	if (radacina != NULL) {
		if (radacina->info.cod == cod) {
			//info se afla in radacina
			return radacina->info;
		}
		else if (radacina->info.cod > cod) {
			//cautam in sub arborele stang
			cautare_cod(radacina->stanga, cod);
		}
		else {
			cautare_cod(radacina->dreapta, cod);
		}
	}
	else {
		ApelUrgenta apel;
		apel.cod = -1;
		apel.prioritate = -1;
		return apel;
	}
}
//determinare numar de noduri
void numara(BinaryTree* radacina, int &nr)
{
	if (radacina != NULL)
	{
		numara(radacina->stanga, nr);
		nr++;
		numara(radacina->dreapta, nr);
	}
}
//afisare arbore -- cele trei tipuri: preordine, inordine postordine
//Radacina Stanga Dreapta
void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}

// Stanga Radacina Dreapta
void afisare_inordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_preordine(radacina->stanga);
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->dreapta);
	}
}

// Stanga Dreapta Radacina
void afisare_postordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
		afisare_apel_urgenta(radacina->info);
	}
}
//inaltime arbore
int inaltime_arbore(BinaryTree* radacina) {
	if (radacina) {
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return 1 + (inaltime_stanga > inaltime_dreapta ? inaltime_stanga : inaltime_dreapta);
	}
	else {
		return 0;
	}
}
//afisare nivel arbore 
void afisare_pe_nivel(BinaryTree* radacina, int nivelCautat, int nivelCurent) {
	if (radacina) {
		if (nivelCautat == nivelCurent) {
			afisare_apel_urgenta(radacina->info);
		}
		else {
			afisare_pe_nivel(radacina->stanga, nivelCautat, nivelCurent + 1);
			afisare_pe_nivel(radacina->dreapta, nivelCautat, nivelCurent + 1);
		}
	}
}
//dezalocare arbore
void dezalocare(BinaryTree* &radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
void main() {
	int nr;
	ApelUrgenta* apeluri = citire_apeluri_urgenta_fisier(nr);
	//afisare_apeluri_urgenta(apeluri, nr);
	BinaryTree* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(apeluri[i], radacina);
	}
	afisare_preordine(radacina);
	int cod = 0;
	printf("\nIntroducere cod pentru stergere: ");
	scanf_s("%d", &cod);
	sterge_nod(radacina, cod);
	afisare_preordine(radacina);
	dezalocare(radacina);
}