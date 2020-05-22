#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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


void main()
{
	compresie_text();
}