///*										STIVA:
//	O stiva este o lista simplu inlantuita care are urmatoarele proprietati:
//		- elementele pot fi inserate si sterse doar din varful listei.
//		- elementele sunt sterse in ordinea inversa inserarii, motiv pentru care aceasta urmeaza principiul LIFO.
//		- pentru gestionarea unei stive este nevoie sa lucrati cu un singur pointer in care sa se retina varful stivei.
//
//	LIFO = Last In First Out - ultimul introdus este primul sters.
//
//										COADA:
//	O coada este o lista simplu inlantuita care are urmatoarele proprietati:
//		- elementele pot fi inserate doar la finalul listei;
//		- elementele pot fi sterse doar din varful listei.
//		- urmeaza principiul FIFO.
//		- pentru gestionarea unei cozei este nevoie sa lucrati cu 2 pointer in care sa se retina primul si ultimul element.
//		  Ultimul element este tinut intr-un pointer pentru a nu realiza de fiecare data cand dorim sa introducem un nou
//		  element in coada o parcurgere a acesteia din varf pana la final.
//
//	FIFO = First In First Out - primul introdus este primul sters
//
//*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Angajat {
	char nume[30];
	float salariu;
};

struct nod_stiva {
	Angajat info;
	nod_stiva* next_stack;
};

struct nod_coada {
	Angajat info;
	nod_coada* next_queue;
};

Angajat citire_angajat_tastatura() {
	Angajat a;
	printf("\n+++++++++++++++++++++++++++++++++++++++\n");
	printf("Introducere angajat:");
	printf("\nNume: ");
	getc(stdin);
	gets_s(a.nume, 30);
	printf("\nSalariu: ");
	scanf_s("%f", &a.salariu);
	return a;
}

void afisare_angajat_tastatura(Angajat a) {
	printf("\n Nume: %s, Salariu: %2.2f", a.nume, a.salariu);
}

//------------------- STIVA ------------------------------------
//void push(nod_stiva* *primul, Angajat info);
//nod_stiva* push(nod_stiva* primul, Angajat info);
void push(nod_stiva* &primul, Angajat info) {
	//initializare element nou
	nod_stiva* nou = (nod_stiva*)malloc(sizeof(nod_stiva));
	nou->info = info;
	nou->next_stack = NULL;
	if (primul == NULL) {
		//initializare primul element din stiva
		primul = nou;
	}
	else {
		//adaugare element nou in stiva. 
		//conform specificatiilor, intr-o stiva se adauga doar prin capat.
		//prin urmare face modificare primul-ul pointer din lista
		nou->next_stack = primul;
		primul = nou; // schimbare varf stiva
	}
}
void pop(nod_stiva* &primul, Angajat &info) {
	//verificam daca stiva este initializata
	if (primul) {
		//eliminarea elementelor din stiva se face tot prin varful acesteia
		//prin urmare, ar trebui sa schimbam adresa primului pointer
		//declaram variabila intermediar pentru a izola elementul pe care dorim sa-l stergem
		nod_stiva* eliminat = primul;
		//preluam info pe care o scoatem din stiva
		info = primul->info;
		//schimbam varful stivei
		primul = primul->next_stack;
		//dezalocare
		free(eliminat);
	}
}

void afisare_stiva(nod_stiva* primul) {
	//declaram un pointer intermediar, cursor pentru a nu pierde legatura 
	nod_stiva* cursor = primul;
	while (cursor) {
		afisare_angajat_tastatura(cursor->info);
		cursor = cursor->next_stack;
	}
}
//------------------- COADA ------------------------------------
//void push(nod_coada* *primul, nod_coada* *ultimul, Angajat info);
void push(nod_coada* &primul, nod_coada* &ultimul, Angajat info) {
	//initializare element nou 
	nod_coada* nou = (nod_coada*)malloc(sizeof(nod_coada));
	nou->info = info;
	nou->next_queue = NULL;
	if (primul == NULL && ultimul == NULL) {
		//adaugam primul element in coada
		primul = nou;
		ultimul = nou;
	}
	else {
		//coada are cel putin un element
		//conform specificatiilor intr-o coada tot timpul se adauga la final
		//prin urmare, trebuie sa schimbam tot timpul valoarea pointerului ultimul
		//folosim acest pointer ca sa nu facem o parcurgere prin toata coada de fiecare data cand dorim
		//sa adaugam un elemenet nou. Salvam timp de procesare
		ultimul->next_queue = nou;
		ultimul = nou;//schimbam ultimul element din lista
	}
}
void pop(nod_coada* &primul, nod_coada* &ultimul, Angajat &info) {
	//intr-o coada eliminarea se face prin varful cozii. Verificati specificatii
	if (primul != NULL) {
		//declaram variabila intermediar in care punem elementul pe care dorim sa-l eliminam din coada
		nod_coada* eliminat = primul;
		//extragere info din pointerul pe care-l eliminam
		info = primul->info;
		//schimbare varful cozii
		primul = primul->next_queue;
		//verificam daca acesta a fost singurul element al cozii. 
		//In caz afirmativ, trebuie sa initializam pointerul ultimul cu NULL
		if (primul == NULL) {
			ultimul = NULL;
		}
		//dezalocare pointer eliminat
		free(eliminat);
	}
}
void afisare_coada(nod_coada* primul, nod_coada* ultimul) {
	//declaram pointer intermediar pentru a parcurge coada
	nod_coada* cursor = primul;
	while (cursor) {
		afisare_angajat_tastatura(cursor->info);
		cursor = cursor->next_queue;
	}
}

nod_stiva* intializare_stiva() {
	nod_stiva* primul = NULL;
	int ok = 1;
	//citesc cat timp ok este 1
	while (ok == 1) {
		//citire angajat de la tastatura
		Angajat a = citire_angajat_tastatura();
		//introducere element in stiva
		push(primul, a);
		printf("\nDoriti sa continuati? Da-1/Nu-0 ");
		scanf_s("%d", &ok);
	}
	return primul;
}

void initializare_coada(nod_coada* *primul, nod_coada* *ultimul) {
	int ok = 1;
	//citesc cat timp ok este 1
	while (ok == 1) {
		//citire angajat de la tastatura
		Angajat a = citire_angajat_tastatura();
		//introducere element in stiva
		push(*primul,*ultimul, a);
		printf("\nDoriti sa continuati? Da-1/Nu-0 ");
		scanf_s("%d", &ok);
	}
}
void main() {
   	nod_stiva* primul = intializare_stiva();
	afisare_stiva(primul);
	Angajat a;
	pop(primul,a);
	afisare_stiva(primul);
	printf("\n Afisare angajat scos din stiva: ");
	afisare_angajat_tastatura(a);
	nod_coada* primul_c = NULL;
	nod_coada* ultimul_c = NULL;
	initializare_coada(&primul_c, &ultimul_c);
	afisare_coada(primul_c, ultimul_c);
	pop(primul_c,ultimul_c, a);
	afisare_coada(primul_c, ultimul_c);
	printf("\n Afisare angajat scos din coada: ");
	afisare_angajat_tastatura(a);
}