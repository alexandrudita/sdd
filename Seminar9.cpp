#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int isbn;
	float pret;
};

struct NodArb {
	Carte info;
	NodArb* stanga;
	NodArb* dreapta;
	int ge;
};

//=============================================== METODE CARTE =============================
Carte citire_carte() {
	Carte c;
	printf("\nISBN: ");
	scanf_s("%d", &c.isbn);
	printf("\nPret: ");
	scanf_s("%f", &c.pret);
	return c;
}

void afisare_carte(Carte c) {
	printf("\nISBN: %d Pret: %2.2f", c.isbn, c.pret);
}

//============================================= METODE AVL ====================================
NodArb* creare_nod(Carte c) {
	NodArb* nod = (NodArb*)malloc(sizeof(NodArb));
	nod->dreapta = NULL;
	nod->stanga = NULL;
	nod->ge = 0;
	nod->info = c;
	return nod;
}

// Radacina Stanga Dreapta
void afisare(NodArb* radacina) {
	if (radacina) {
		afisare_carte(radacina->info);
		afisare(radacina->stanga);
		afisare(radacina->dreapta);
	}
}

int inaltime_arbore(NodArb* radacina) {
	if (radacina) { 
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return 1 + (inaltime_stanga > inaltime_dreapta ? inaltime_stanga : inaltime_dreapta);
	}
	else {
		return 0;
	}
}

int grad_echilibru(NodArb* radacina) {
	if (radacina) {
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return inaltime_stanga - inaltime_dreapta;
	}
	else {
		return 0;
	}
}

//=================== METODE DE ROTIRE AVL INCEPUT ============================
NodArb* rotire_stanga(NodArb* radacina) {
	if (radacina) {
		NodArb* copil_dreapta = radacina->dreapta;
		radacina->dreapta = copil_dreapta->stanga;
		copil_dreapta->stanga = radacina;
		//calculam gradul de echilibru dupa rotire
		radacina->ge = grad_echilibru(radacina);
		copil_dreapta->ge = grad_echilibru(copil_dreapta);
		return copil_dreapta;
	}
	else {
		return radacina;
	}
}

NodArb* rotire_dreapta(NodArb* radacina) {
	if (radacina) {
		NodArb* copil_stanga = radacina->stanga;
		radacina->stanga = copil_stanga->dreapta;
		copil_stanga->dreapta = radacina;
		//calculam gradul de echilibru dupa rotire
		radacina->ge = grad_echilibru(radacina);
		copil_stanga->ge = grad_echilibru(copil_stanga);
		return copil_stanga;
	}
	else {
		return radacina;
	}
}

NodArb* rotire_stanga_dreapta(NodArb* radacina) {
	if (radacina) {
		//rotim la stanga subarborele stang
		radacina->stanga = rotire_stanga(radacina->stanga);
		//rotim la dreapta arborele
		return rotire_dreapta(radacina);
	}
	else {
		return radacina;
	}
}

NodArb* rotire_dreapta_stanga(NodArb* radacina) {
	if (radacina) {
		//rotim la dreapta subarborele drept
		radacina->dreapta = rotire_dreapta(radacina->dreapta);
		//rotim la stanga arborele
		return rotire_stanga(radacina);
	}
	else {
		return radacina;
	}
}
//=================== METODE DE ROTIRE AVL FINAL ============================
NodArb* echilibrare(NodArb* radacina) {
	if (!radacina) {
		return radacina;
	}
	//calculam gradul de echilibru al arborelui dupa ce s-a facut inserarea noului nod
	radacina->ge = grad_echilibru(radacina);
	//avem dezechilibru pe partea stanga a arborelui
	if (radacina->ge == 2) {
		//daca gradul de echilibru al sub arborelui stang este 1 atunci facem o singura rotire la dreapta
		//altfel se face o rotire dubla una la stanga urmata de una la dreapta
		return radacina->stanga->ge == 1
			? rotire_dreapta(radacina)
			:rotire_stanga_dreapta(radacina);
	}
	//avem dezechilibru pe partea dreapta a arborelui
	if (radacina->ge == -2) {
		//daca gradul de echilibru al sub arborelui drept este 1 atunci facem o singura rotire la stanga
		//altfel se face o rotire dubla una la dreapta urmata de una la stanga
		return radacina->dreapta->ge == -1
			? rotire_stanga(radacina)
			: rotire_dreapta_stanga(radacina);
	}
	//returnam radacina daca nu se face vreo rotire
	return radacina;
}

//inserare nod
NodArb* inserare_nod(Carte carte, NodArb* radacina) {
	//verificam daca radacina este populata
	if (radacina) {
		//verificam in ce directie ar trebui sa fie adaugat nodul in functie de isbn
		if (radacina->info.isbn > carte.isbn) {
			//apelam recursiv pe sub arborele stanga astfel incat sa identificam pozitia in arbore
			radacina->stanga = inserare_nod(carte, radacina->stanga);
		}
		else {
			//apelam recursiv pe sub arborele dreapta astfel incat sa identificam pozitia in arbore
			radacina->dreapta = inserare_nod(carte, radacina->dreapta);
		}
		//apelam metoda de echilibrare a arborelui pentru a pastra structura de AVL
		return echilibrare(radacina);
	}
	else {
		//nodul radacina este null-> se adauga un nod nou
		return creare_nod(carte);
	}
}

//stergere nod 
// functie pentru stergerea nodului radacina 
void stergere_nod_radacina(NodArb* &radacina)
{
	//salvam radacina intr-un pointer intermediar
	NodArb* nod = radacina;
	// daca avem un subarbore drept
	if (nod->dreapta)
	{
		// facem legatura
		radacina = nod->dreapta;
		// daca avem si un subarbore stang
		if (nod->stanga)
		{
			// cautam cel mai mic element din subarborele drept
			NodArb* temp = nod->dreapta;
			//cel mai mic se afla in extremitatea stanga 
			while (temp->stanga != NULL) temp = temp->stanga;
			// si adaugam subarborele stang ca descendent al celui mai mic element din subarborele drept
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

void sterge_nod(NodArb* &radacina, int isbn) {
	if (radacina) {
		//verificam daca codul se afla in radacina 
		if (radacina->info.isbn == isbn) {
			stergere_nod_radacina(radacina);
		}
		else {
			//codul nu se afla in radacina
			NodArb * nodCurent = radacina;
			if (isbn < nodCurent->info.isbn) {
				sterge_nod(nodCurent->stanga, isbn);
			}
			else {
				sterge_nod(nodCurent->dreapta, isbn);
			}
		}
		//apelam metoda de echilibrare a arborelui pentru a pastra structura de AVL
		radacina = echilibrare(radacina);
	}
}
void main() {
	int ok = 1;
	NodArb* radacina = NULL;
	while (ok == 1) {
		Carte c = citire_carte();
		radacina = inserare_nod(c, radacina);
		printf("\nDoriti sa continuare? Da-1 Nu-0");
		scanf_s("%d", &ok);
	}
	printf("\nAfisare AVL:\n");
	afisare(radacina);
	printf("\nStergere nod cu ISBN: ");
	int isbn;
	scanf_s("%d", &isbn);
	sterge_nod(radacina, isbn);
	printf("\nAfisare AVL:\n");
	afisare(radacina);
}