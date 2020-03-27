/*
										TABELA DISPERSIE

Tabela de dispersie este o structura de date care asigura stocare informatiilor in forma asociativa. 
In tabela de dispersie, datele sunt stocate intr-un vector unde fiecare element are un index unic. In 
felul acesta accesul devine foarte rapid. 
Indexul unic(pozitia in tabela de dispersie) este calculat pe baza unui camp/campuri din structura 
pe care dorim sa o stocam intr-o tabela de dispersie aplicand o functie cunoscuta drept functie hash.

Rolul functiei hash este de a prelucra cheia asociata fiecarei inregistrari si de a determina pozitia
in cadrul tabelei de dispersie a elementului respectiv. Nu exista o functie hash generala, iar alegerea 
acesteia depinde de tipul chei(camp int, float, sir de caractere, mai multe campuri dintr-o structura). 
Prin urmare, sunt utilizate urmatoarele metode de implementare a functiei hash:
- impartirea in modul: are un grad mare de utilizare datorita usurintei de implementare;
indiferent de forma cheii de cautare, functia hash o sa returneze in cazul acesta o valoare int in intervalul [0,n-1], 
unde n reprezinta dimensiunea tabelei de dispersie. FORMA DE UTILIZARE: cheie % dimensiune_tabela_dispersie
- inmultirea cu un numar real aleatoriu si prelucracrea partii zicimale. Valoarea cheii este inmultita cu 
un numar din intervalul [0,1) ce este ales aleatoriu, partea zecimala a rezultatului obtinut este o 
valoare in intervalul [0,1), acest rezultat este inmultit cu dimensiunea tabelei de dispersie astfel
se obtine cheia hash care are o valoare in intervalul [0, n-1], unde n dimensiune tabela dispersie.
- prelucrarea codurilor ASCII ale caracterelor alfanumerice. Aceasta forma este utilizata pentru situatia
in care cheia de cautare este un sir de caractere. Prelucrarea se face pe baza codului ASCII asociat 
primului caractere din cheie. FORMULA: string_cheie[0]%255

Rezolvarea coliziunii:
- chaining - se bazeaza pe liste, fiecare element din tabela de dispersie este varful unei liste simpla. 
Elementele aceleasi liste au proprietatea ca valoarea hash obtinuta pe baza cheii este egala. 
ATENTIE: Daca doua elemente au acelas hash, nu inseamna ca si cheile lor sunt egale.
- linear probing - se bazeaza pe cautarea secventiala ap primei pozitii libere in care sa fie inserat 
elementul nou. 

*/
#include<stdio.h>
#include<stdlib.h>

//informatia pe care dorim sa o procesam
struct Student {
	int cod_matricol;
	char nume[30];
	float nota;
};

Student citire_student() {
	Student s;
	printf("\nCod matricol: ");
	scanf_s("%d", &s.cod_matricol);
	getc(stdin);
	printf("\nNume: ");
	gets_s(s.nume, 30);
	printf("\nNota: ");
	scanf_s("%f", &s.nota);
	return s;
}

void afisare_student(Student s) {
	printf("\n%d %s %2.2f", s.cod_matricol, s.nume, s.nota);
}

//este necesar pentru a putea reprezenta elementele in tabela de dispersie
struct NodStudent {
	Student info;
	NodStudent* next;
};

//structura unei tabele de dispersie pentru informatia student
struct HashStudent {
	int dimensiune;
	NodStudent** elemente;
};

//Orice tabela de dispersie trebuie sa aibe o functie pentru a calcula hash pe baza unei chei
//cea mai simpla metoda de hash folosesti operatorul modulo folosind dimensiunea tabelei de dispersie si 
//o cheie aleasa din info pe care o stocam in Hash
int cod_hash(int cheie, HashStudent hs) {
	return cheie % hs.dimensiune;
}

//operatie de alocare in memorie a unei tabele de dispersie 
HashStudent alocare_memorie() { 
	HashStudent hs;
	printf("\nIntroduceti dimensiunea hash: ");
	scanf_s("%d", &hs.dimensiune);
	hs.elemente = (NodStudent**)malloc(sizeof(NodStudent)*hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++) {
		hs.elemente[i] = NULL;
	}
	return hs;
}
//functie pentru dezalocarea unei tabele de dispersie din memorie
void dezalocare_lista(NodStudent* cap) {
	//fiecare pozitie a hash-ului contine o lista simplu inlantuita, prin urmare
	//aplicat metoda de stergere a unei astfel de liste. 
	//stergem capul listei si trecem la urmatorul element cat timp nu am ajuns la final.
	if (cap != NULL) {
		NodStudent* sters;
		while (cap != NULL) {
			sters = cap;
			cap = cap->next;
			free(sters);
		}
	}
}
void dezalocare_memorie(HashStudent hs) {
	//verificam daca hash-ul a fost initializat
	if (hs.dimensiune > 0 && hs.elemente!=NULL) {
		for (int i = 0; i < hs.dimensiune; i++) {
			//dezalocare lista din pozitia i a vectorului 
			dezalocare_lista(hs.elemente[i]);
		}
		free(hs.elemente);
		hs.dimensiune = 0;
	}
}

//functie pentru adaugare unui element in tabela de dispersie
int inserare(Student s, HashStudent &hs) {
	//returnam 1 daca s-a inserat elementul cu succes sau -1 in caz de esec
	//verificam ca avem hash-ul initializat
	if (hs.dimensiune == 0 || hs.elemente == NULL || s.cod_matricol<0) {
		return -1;
	}
	//apelam functia hash pentru a determina pozitia pe care ar trebui sa adaugam acest student
	int hash = cod_hash(s.cod_matricol, hs);
	//verificam daca pe pozitia respectiva s este primul element(cap al listei)
	if (hs.elemente[hash] == NULL) {
		//aplicam metoda de inserare a unui cap intr-o lista simpla 
		hs.elemente[hash] = (NodStudent*)malloc(sizeof(NodStudent));
		//urmatorul element pe aceasta pozitie este NULL deoarece nu exista
		hs.elemente[hash]->next = NULL;
		//adaugam informatia in hash
		hs.elemente[hash]->info = s;
	}
	else { //pe pozitia calculata exista deja un element. - coliziune
		//aplicam metode de inserare a unui element intr-o lista simpla 
		//folosim o variabila intermediara cursor pentru a parcurge lista pana la finalul acesteia
		NodStudent* cursor = hs.elemente[hash];
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		//initializam o variabila nou in care adaugam toate informatiile unui NodStudent (next, info)
		NodStudent* nou = (NodStudent*)malloc(sizeof(NodStudent));
		nou->info = s;
		nou->next = NULL;
		//adaugam noul nod la sfarsitul listei de pe pozitia tinta
		cursor->next = nou;
	}
	return 1;
}
//functie pentru stergerea unui element din tabela de dispersie folosind cheia de hash
int stergere(int cod_matricol, HashStudent& hs) {
	//returnam 1 daca s-a inserat elementul cu succes sau -1 in caz de esec
	//verificam ca avem hash-ul initializat
	if (hs.dimensiune == 0 || hs.elemente == NULL || cod_matricol<0) {
		return -1;
	}
	//calculam pozitia in hash a acestui cod
	int hash = cod_hash(cod_matricol, hs);
	//verificam daca pe pozitia hash-ul exista elemente
	if (hs.elemente[hash] != NULL) {
		//aplicam metoda de stergere a unui element dintr-o lista simpla
		//cautam studentul care are codul matricol primit ca parametru de intrare
		if (hs.elemente[hash]->info.cod_matricol == cod_matricol) {
			//stergem capul listei de pe pozitia hash-ului, prin urmare aplicam modificarea de cap 
			NodStudent* sters = hs.elemente[hash];
			//schimbam capul listei
			hs.elemente[hash] = hs.elemente[hash]->next;
			//rupem legatura nodul de lista de valori
			sters->next = NULL;
			//stergem nodul
			free(sters);
		} else {
			//definim o variabila intermediara ca sa nu 'stricam' structura listei de pe pozitia respectiva
			NodStudent* cursor = hs.elemente[hash];
			//parcurgem lista si cautam studentul cu codul matricol tinta
			//Mare atentie trebuie sa ne pozitionam pe elementul din fata celui pe care dorim sa-l stergem
			//Motivul: avem o lista simpla prin urmare nu putem reface legatura celui aflat inainte nodului 
			//de sters cu cel de dupa
			while (cursor->next != NULL && cursor->next->info.cod_matricol != cod_matricol) {
				cursor = cursor->next;
			}
			//daca ne-am oprit ptr ca am gasit codul matricol il stergem
			if (cursor->next != NULL && cursor->next->info.cod_matricol == cod_matricol) {
				//stergem nodul urmator
				NodStudent* sters = cursor->next;
				//rupem legatura din lista
				cursor->next = sters->next;
				sters->next = NULL;
				free(sters);
			}
			else {
				return -1;
			}
		}
	}
	else {
		return -1;
	}
	return 1;
}
//functie pentru afisarea la consola a informatiilor din tabela de dispersie
void afisare_lista(NodStudent* cap) {
	if (cap != NULL) {
		NodStudent* cursor = cap;
		while (cursor != NULL) {
			afisare_student(cursor->info);
			cursor = cursor->next;
		}
	}
}

void afisare_hash(HashStudent hs) {
	printf("\nAfisare hash: ");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			printf("\nElemente pozitia %d: ", i);
			afisare_lista(hs.elemente[i]);
		}
	}
}

void adaugare_studenti_hash(HashStudent& hs) {
	int ok = 1;
	while (ok == 1) {
		//citim studentul de la tastatura
		Student s = citire_student();
		//adaugam in hash
		int rezultat = inserare(s, hs);
		printf("\nStudentul cu cod matricol %d a fost inserat cu %d", s.cod_matricol, rezultat);
		printf("\nContinuati? Da-1 Nu-0");
		scanf_s("%d", &ok);
	}
}

void stergere_student_cod_matricol(HashStudent& hs) {
	int cod;
	printf("\nCodul pe care doriti sa-l stergeti: ");
	scanf_s("%d", &cod);
	stergere(cod, hs);
}

void main() {
	printf("\n+++++++++++++++++++++++++alocare_memorie+++++++++++++++++++++++\n");
	HashStudent hs = alocare_memorie();
	afisare_hash(hs);
	printf("\n+++++++++++++++++++++adaugare_studenti_hash+++++++++++++++++++++++++++\n");
	adaugare_studenti_hash(hs);
	afisare_hash(hs);
	printf("\n+++++++++++++++++++++stergere_student_cod_matricol+++++++++++++++++++++++++++\n");
	stergere_student_cod_matricol(hs);
	afisare_hash(hs);
	dezalocare_memorie(hs);
}