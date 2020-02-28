#include "pch.h"
#include<stdio.h>
#include<stdlib.h>

//definire structura matrice rara
struct MatriceRara {
	int linie;
	int coloana;
	double valoare;
};

double** citire_matrice_fisier(
	FILE* fisier,
	int& nr_linii,
	int& nr_coloane) {
	
	double** matrice;
	if (fisier != NULL && !feof(fisier)) {
		//citesc date din fisier
		fscanf_s(fisier, "%d", &nr_linii);
		fscanf_s(fisier, "%d", &nr_coloane);
		//alocare dinamica matrice
		matrice = (double**)
			malloc(sizeof(double*)
				*nr_linii);
		for (int i = 0; i < nr_linii; i++) {
			matrice[i] = (double*)
				malloc(sizeof(double)
					*nr_coloane);
		}
		//citire matrice
		for (int i = 0; i < nr_linii;
			i++) {
			for (int k = 0; k < nr_coloane; k++) {
				fscanf_s(fisier,
					"%lf", 
					&matrice[i][k]);
			}
		}
		fclose(fisier);
		return matrice;
	}
}

int calculare_dimensiune_mr(
	double** matrice,
	int nr_linii,
	int nr_coloane) {
	int dim = 0;
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_coloane; j++) {
			//calculam cate sunt nule
			if (matrice[i][j] == 0) {
				dim++;
			}
		}
	}
	if (dim > nr_linii*nr_coloane * 2 / 3) {
		return nr_linii 
			* nr_coloane - dim;
	}
	else {
		return 0;
	}
}

MatriceRara* conversie_catre_mr(
	double** matrice,
	int nr_linii,
	int nr_coloane,
	int& dim) {
	MatriceRara* mr;
	//calculare dimensiune matrice rara
	//daca dim =0 nu avem matrice rara
	dim = calculare_dimensiune_mr(matrice,
		nr_linii, nr_coloane);
	if (dim > 0) {
		mr = (MatriceRara*)malloc(
			sizeof(MatriceRara)*dim);
		int k = 0;
		for (int i = 0; i < nr_linii; i++) {
			for (int j = 0; j < nr_coloane; j++) {
				if (matrice[i][j] != 0) {
					mr[k].linie = i;
					mr[k].coloana = j;
					mr[k].valoare = matrice[i][j];
					k++;
				}
			}
		}
		return mr;
	}
}

void afisare_mr(MatriceRara* mr,
	int dim) {
	printf("\n afisare matrice rara\n");
	for (int i = 0; i < dim; i++) {
		printf("\nMatrice pozitie %d", i);
		printf("\nlinia %d, coloana %d, valoare %f",
			mr[i].linie, mr[i].coloana, mr[i].valoare);
	}
}

void dezalocare(double** matrice,
	int nr_linii,
	MatriceRara* mr,
	int dim) {
	if (nr_linii > 0) {
		for (int i = 0; i < nr_linii; i++) {
			free(matrice[i]);
		}
		free(matrice);
	}
	if (dim > 0) {
		free(mr);
	}
}
void main() {
	int nr_linii, nr_coloane;
	FILE* fisier;
	fopen_s(&fisier, "matrice.txt", "r");
	double** matrice
		= citire_matrice_fisier(
			fisier, 		
			nr_linii,
			nr_coloane);
	int dim = 0;
	MatriceRara* mr = conversie_catre_mr(
		matrice,
		nr_linii,
		nr_coloane,
		dim);
	if (dim > 0) {
		afisare_mr(mr, dim);
	}
	else {
		printf("\n Nu avem matrice rara\n");
	}

	dezalocare(matrice, nr_linii,
		mr, dim);
}
