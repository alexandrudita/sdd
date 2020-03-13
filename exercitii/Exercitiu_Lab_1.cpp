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
//------------------- STIVA ------------------------------------
void push(nod_stiva* primul, Angajat info);
void pop(nod_stiva* primul, Angajat info);
void afisare_stiva(nod_stiva* primul);
//------------------- COADA ------------------------------------
void push(nod_coada* primul, nod_coada* ultimul, Angajat info);
void pop(nod_coada* primul, nod_coada* ultimul, Angajat info);
void afisare_coada(nod_coada* primul, nod_coada* ultimul);

void main() {
}