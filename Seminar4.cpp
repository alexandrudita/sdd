#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct angajat {
	int cod;
	char* nume;
	float salariu;
};

struct nod {
	angajat info;
	nod* next;//pointer catre elementul urmator 
	nod* prev;//pointer catre elementul anterior
};

angajat citire_angajat_tastatura() {
	angajat a;
	printf("\nCitire angajat:\n");
	printf("\nCod: ");
	scanf_s("%d", &a.cod);
	printf("\nNume: ");
	getchar();
	char buf[30];
	gets_s(buf, 30);
	int dim = strlen(buf) + 1;
	a.nume = (char*)malloc(sizeof(char)*dim);
	strcpy_s(a.nume, dim, buf);
	printf("\nSalariu: ");
	scanf_s("%f", &a.salariu);
	return a;
}

nod* creare_lista() {
	nod*cap = NULL;//initializam capatul listei. OBS Niciodata sa nu pierdeti legatura capatului, pentru a nu pierde constructia listei
	int nr_el = 0;
	printf("\nIntroduceti numarul de elemente: ");
	scanf_s("%d", &nr_el);
	if (nr_el > 0) {
		//initializam pointerul de tip nod corespunzatorul primului element din lista
		cap = (nod*)malloc(sizeof(nod));//alocare spatiu de memorie pentru capul listei
		cap->next = NULL;//urmatorul element din lista este initializat cu NULL
		cap->prev = NULL;//elementul anterior din lista este initializat cu NULL
		cap->info = citire_angajat_tastatura();//se ataseaza primului nod(cap) informatia dorita
		nod *cursor, *nou;
		//orice parcurgere a listei se face cu ajutorului unui alt pointer, 
		//astfel incat sa pastram tot timpul primul element al liste intr-o variabila locala(cap). 
		//variabila cursor are ca scop sa parcurga lista de la inceput pana la final. 
		cursor = cap;
		//adaugam restul elementelor din lista. Tinem cont ca am initilizat primul element al listei, prin urmare iteratia for-ului incepe de la pozitia a doua
		for (int i = 1; i < nr_el; i++) {
			//se aloca spatiu in memorie pentru noul element din lista
			nou = (nod*)malloc(sizeof(nod));
			//urmatorul element pe care-l pointeaza este NULL
			nou->next = NULL;
			//elementul anterior pe care-l pointeaza este cursor
			nou->prev = cursor;
			//se adauga informatia dorita in nodul initializat
			nou->info = citire_angajat_tastatura();
			//se ataseaza noul element ca fiind urmatorul in lista 
			cursor->next = nou;
			//cursorul isi schimba pozitia pe ultimul element al listei
			cursor = nou;
		}
	}
	return cap;
}

void traversare(nod*cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;//se foloseste tot o variabila de tipul capului(cursor) pentru a asigura parcurgerea acesteia
	while (cursor) {//se parcurge lista pana cand cursorul devine NULL
		printf("\nCod: %d; Nume: %s; Salariu: %5.2f", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;//mutam pointerul cursor catre urmatorul elemente din lista. 'next' contine adresa urmatorului element
	}
}

nod* inserare_element(nod* cap, angajat info) {
	//prima data verificam daca lista este goala, asta inseamna ca nodul cap este NULL
	if (cap == NULL) {
		//se aloca spatiu de memorie pentru cap
		cap = (nod*)malloc(sizeof(nod));
		//se adauga informatia dorita pe acest nod
		cap->info = info;
		//urmatorul element din lista este NULL, deoarece lista a fost goala
		cap->next = NULL;
		//elementul anterior din lista este NULL, deoarece lista a fost goala
		cap->prev = NULL;
	}
	else
	{
		//utilizam o variabila pointer de nod numita cursor pentru a parcurge toata lista pana pe ultimul element
		nod* cursor = cap;
		//cursorul este ultimul element daca variabila next din acest nod este NULL
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		//alocam spatiu de memorie pentru noul nod
		nod* nou = (nod*)malloc(sizeof(nod));
		//acest nod fiind adaugat la finalul listei legatura next este NULL
		nou->next = NULL;
		//elementul anterior este cursor, cel care a fost ultimul pana in momentul acesta
		nou->prev = cursor;
		//se ataseaza informatia noului nod
		nou->info = info;
		//se ataseaza noul nod catre pointer 'next' al variabilei cursor
		cursor->next = nou;
	}
	return cap;
}

nod* stergere_element(nod* cap) {
	//daca nu avem elemente in lista nu putem sterge
	if (cap == NULL) {
		return NULL;
	}
	//daca avem un singur element in lista atunci pointerul cap trebuie dezalocat si devine NULL
	else if (cap->next == NULL) {
		//dezalocam si informatia nume deoarece este alocata dinamic
		free(cap->info.nume);
		free(cap);
		return NULL;
	}
	else {
		//se utilizeaza variabila cursor pentru a parcurge lista si a ne pozitiona pe penultimul element. 
		//Trebuie sa va pozitionati pe penultimul ca sa puteti rupe legatura sa fata de ultimul element. 
		//In cazul listei dublu inlantuita puteti sa va pozitionati si pe ultimul element deoarece aveti la dispozitie variabila prev 
		//care specifica adresa penultimului nod
		nod* cursor = cap;
		//cursor->next - ofera urmatorul element, iar cursor->next->next ofera nextul urmatorului element.
		while (cursor->next->next != NULL) {
			cursor = cursor->next;
		}
		//se utilizeaza o alta variabila de tip nod*(ultim) pentru a izola ultimul element al liste.
		//este esential sa se retina in aceasta variabila ultimul element pentru a putea mapa next-ul penultimului cu NULL.
		nod* ultim = cursor->next;
		//se rupe legatura fata de ultimul element
		cursor->next = NULL;
		//trebuie sa rupeti si legatura prev a ultimului element
		ultim->prev = NULL;
		//dezalocare nume
		free(ultim->info.nume);
		//se dezaloca ultimul element
		free(ultim);
		return cap;
	}
}

int nr_noduri(nod* cap) {
	int nr = 0;
	nod* cursor = cap;
	while (cursor) {
		cursor = cursor->next;
		nr++;
	}
	return nr;
}

int inserare_element_pozitie(nod* &cap, angajat a, int poz) {
	int rezultat = 0;
	int nr = nr_noduri(cap);
	printf("\nLista are %d elemente", nr);
	if ((poz < 0) || (poz > nr)) {//daca pozitia nu este pozitiva sau daca este mai mare decat nr atunci nu fac inserarea.
		rezultat = -1;
	}
	//alocam spatiul si informatia noului nod
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = a;
	if (poz == 0) {//daca doresc sa inserez pe pozitia 0 atunci trebuie sa schimb valoarea pointerului cap care specifica primul element al listei
		nou->next = cap;
		//mapez anteriorul elementului nou care trebuie sa fie NULL deoarece o sa devina noul cap
		nou->prev = NULL;
		//anteriorul capului curent devine elementul nou
		cap->prev = nou;
		//schimbam capul listei
		cap = nou;
		rezultat = 1;
	}
	else {
		int contor = 0;
		nod* cursor = cap;
		//parcurg lista prin intermediul unui pointer auxiliar(cursor) pana pe elementul aflat pe pozitia dorita
		while (cursor->next != NULL && contor < poz) {
			cursor = cursor->next;
			contor++;
		}
		//fac legaturile. Ordinea este esentiala, altfel se pierde structura de lista
		//definim un nod in care sa retinem elementul aflat prev-ul pozitiei curente pentru a putea reface legatura
		nod* anterior = cursor->prev;
		//fac lagtura din partea stanga, adica nextul elementului anterior nu mai este cursorul ci noul element
		anterior->next = nou;
		//iar prevul noului element este anteriorul cursorului
		nou->prev = anterior;
		//nextul celui nou o sa devina cursorul
		nou->next = cursor;
		//anteriorul cursorului o sa fie noul element
		cursor->prev = nou;
		rezultat = 1;
	}
	return rezultat;
}
//aceleasi explicatii ca la metoda inserare_element_pozitie
int stergere_pozitie(nod* &cap, int pozitie)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	if ((pozitie >= nr) || (pozitie < 0)) {
		rezultat = -1;
	}
	nod* cursor;
	if (pozitie == 0)
	{
		cursor = cap;
		//schimbam cap-ul cu urmatorul element
		cap = cap->next;
		//rupem legatura anterioara a noului cap care era adresa vechiului
		cap->prev = NULL;
		free(cursor->info.nume);
		free(cursor);
		rezultat = 1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		//parcurgem pana in pozitia in care dorim sa stergem
		while (contor < pozitie)
		{
			cursor = cursor->next;
			contor++;
		}
		//salvam intr-o variabila elementul anterior celui pe care dorim sa-l stergem
		nod* anterior = cursor->prev;
		//retinem intr-o variabila element urmatorului celui pe care dorim sa-l stergem
		nod* urmator = cursor->next;
		//eliminam legaturile celui pe care dorim sa-l stergem
		cursor->next = NULL;
		cursor->prev = NULL;
		//refacem legaturile intre anterior si urmator, astfel incat nodul din cursor sa fie izolat si scos din lista
		anterior->next = urmator;
		urmator->prev = anterior;
		free(cursor->info.nume);
		free(cursor);
		rezultat = 1;
	}
	return rezultat;
}

nod* creare_lista_circulara() {
	nod*cap = NULL;
	int nr_el = 0;
	printf("\nIntroduceti numarul de elemente: ");
	scanf_s("%d", &nr_el);
	if (nr_el > 0) {
		cap = (nod*)malloc(sizeof(nod));
		cap->next = NULL;
		cap->info = citire_angajat_tastatura();
		nod *cursor, *nou;
		cursor = cap;
		for (int i = 1; i < nr_el; i++) {
			nou = (nod*)malloc(sizeof(nod));
			nou->next = NULL;
			nou->info = citire_angajat_tastatura();
			cursor->next = nou;
			cursor = nou;
		}
		//diferenta cursorul se afla la final
		cursor->next = cap;
	}
	return cap;
}

nod* inserare_element_circulara(nod* cap, angajat info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		cap->info = info;
		//diferenta
		cap->next = cap;
		cap->prev = cap;
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != cap) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = cap;
		nou->prev = cursor;
		nou->info = info;
		cursor->next = nou;
		cap->prev = nou;
	}
	return cap;
}

nod* stergere_element_circulara(nod* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == cap) {
		free(cap->info.nume);
		free(cap);
		return NULL;
	}
	else {
		nod* cursor = cap;
		while (cursor->next->next != cap) {
			cursor = cursor->next;
		}
		//refacem legaturile, prin urmare avem nevoie de o variabila pentru a retine ultimul element
		nod* ultim = cursor->next;
		cursor->next = cap;
		cap->prev = cursor;
		free(ultim);
		return cap;
	}
}

void traversare_circulara(nod*cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	do {
		printf("\nCod: %d; Nume: %s; Salariu: %5.2f", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;
	} while (cursor != cap);
}

void main() {
	nod* cap = NULL;
	printf("\n++++++++++++++++ Citire lista ++++++++++++++\n");
	cap = creare_lista();
	traversare(cap);
	printf("\n++++++++++++++++ Stergere element final ++++++++++++++\n");
	cap = stergere_element(cap);
	traversare(cap);
	angajat a = citire_angajat_tastatura();
	printf("\n++++++++++++++++ Inserare element final ++++++++++++++\n");
	cap = inserare_element(cap, a);
	traversare(cap);
	printf("\n++++++++++++++++ Inserare element pozitie ++++++++++++++\n");
	int pozitie;
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	a = citire_angajat_tastatura();
	int rez = inserare_element_pozitie(cap, a, pozitie);
	traversare(cap);
	printf("\n++++++++++++++++ Stergere element pozitie ++++++++++++++\n");
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	rez = stergere_pozitie(cap, pozitie);
	traversare(cap);
}