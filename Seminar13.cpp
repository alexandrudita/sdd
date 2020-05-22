#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
Sa se utilizeze conceptul de compresie pentru a imbunatatii exemplul din Seminarul 7.
In cadrul exemplului se utiliza o structura de tip max-heap pentru a procesa apelurile 
de urgenta ale unui spital. Structura unui apel de urgenta era forma din urmatoarele
atribute: cod, prioritate si adresa.
*/
struct ApelUrgenta {
	int cod;
	int prioritate;
	char adresa[100];
};

struct NodApel {
	ApelUrgenta info;
	NodApel* next;
};

struct NodGrup {
	int prioritate;
	int nr_elemente;
	NodApel* coadaInceputApeluri;
	NodApel* coadaFinalApeluri;
	NodGrup* next;
};

//sugetii de implelementare pentru metodele de mai jos
ApelUrgenta citireApelUrgentFisier(FILE* fisier);
void adaugaNodApel(NodApel* &primul, NodApel* &ultim, ApelUrgenta apel);
ApelUrgenta eliminaNodApel(NodApel* &primul, NodApel* &ultim);
void adaugaNodGrup(NodGrup* &cap, ApelUrgenta apel);
void eliminareNodGrup(NodGrup* &cap, int cod);
NodGrup* initializareNodGrupuri();


int frecventa(char* sir, char c, int poz) {
	int nr = 0;
	int lungime = strlen(sir) - 1;
	for (int i = poz; i < lungime; i++) {
		if (sir[i] == sir[i + 1]) {
			nr++;
		}
		else {
			break;
		}
	}
	return nr + 1;
}

void compresie_text() {
	FILE *sursa, *destinatie;
	fopen_s(&destinatie, "Compresie.txt", "w");
	fopen_s(&sursa, "in.txt", "r");
	if (sursa && destinatie)
	{
		printf("Fisier deschis");
		char cuvant[1024];
		fgets(cuvant, 1024, sursa);
		printf("%s ", cuvant);
		int lungime_cuvant = strlen(cuvant);
		int ok = 1;
		int nr;
		for (int i = 0; i <  lungime_cuvant && (ok == 1); i++) {
			nr = frecventa(cuvant, cuvant[i], i);
			if (nr > 1) {
				fprintf(destinatie, "%d%c", nr, cuvant[i]);
				i = i + nr - 1;
				if (i > lungime_cuvant) {
					ok = 0;
				}
			}
			else {
				fprintf(destinatie, "%c", cuvant[i]);
			}
				
		}
		fclose(sursa);
		fclose(destinatie);
	} else {
		printf("Nu s-a deschis fisierul!");
	}
}

void main() {
	compresie_text();
}