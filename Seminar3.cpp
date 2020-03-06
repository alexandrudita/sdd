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
	nod* next;//pointer catre urmatoarea structura de tip nod
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
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != cap) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = cap;
		nou->info = info;
		cursor->next = nou;
	}
	return cap;
}

nod* stergere_element_circulara(nod* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == cap) {
		free(cap);
		return NULL;
	}
	else {
		nod* cursor = cap;
		while (cursor->next->next != cap) {
			cursor = cursor->next;
		}
		nod* ultim = cursor->next;
		cursor->next = cap;
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

nod* creare_lista() {
	nod*cap = NULL;//initializam capatul listei. OBS Niciodata sa nu pierdeti legatura capatului, pentru a nu pierde constructia listei
	int nr_el = 0;
	printf("\nIntroduceti numarul de elemente: ");
	scanf_s("%d", &nr_el);
	if (nr_el > 0) {
		//initializam pointerul de tip nod corespunzatorul primului element din lista
		cap = (nod*)malloc(sizeof(nod));//alocare spatiu de memorie pentru capul listei
		cap->next = NULL;//urmatorul element din lista este initializat cu NULL
		cap->info = citire_angajat_tastatura();//se ataseaza primului nod(cap) informatia dorita
		nod *cursor, *nou;
		//orice parcurgere a listei se face cu ajutorului unui alt pointer, astfel incat sa pastram tot timpul primul element al liste intr-o variabila locala(cap). 
		//variabila cursor are ca scop sa parcurga lista de la inceput pana la final. 
		cursor = cap;
		//adaugam restul elementelor din lista. Tinem cont ca am initilizat primul element al listei, prin urmare iteratia for-ului incepe de la pozitia a doua
		for (int i = 1; i < nr_el; i++) {
			//se aloca spatiu in memorie pentru noul element din lista
			nou = (nod*)malloc(sizeof(nod));
			//urmatorul element pe care-l pointeaza este NULL
			nou->next = NULL;
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
		//acest nod fiind adaugat la finalul listei legatura sa (next) este NULL
		nou->next = NULL;
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
		free(cap);
		return NULL;
	}
	else {
		//se utilizeaza variabila cursor pentru a parcurge lista si a ne pozitiona pe penultimul element. 
		//Trebuie sa va pozitionati pe penultimul ca sa puteti rupe legatura sa fata de ultimul element. Daca va pozitionati pe ultimul nu puteti sa rupeti legatura nestiind care este adresa penultimului element. 
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
		cap = nou;
		rezultat = 1;
	}
	else {
		int contor = 0;
		nod* cursor = cap;
		//parcurg lista prin intermediul unui pointer auxiliar(cursor) pana pe elementul aflat inaintea pozitiei in care dorim sa inseram
		//Procedam astfel pentru a putea reface legaturile, pointerul next al pozitiei -1 ar trebui sa fie catre noul element, 
		//iar nextul noului element sa ce sa afla in momentul de fata in nextul elementului de pe pozitie-1
		while (cursor->next != NULL && contor < poz - 1) {
			cursor = cursor->next;
			contor++;
		}
		//fac legaturile. Ordinea este esentiala, altfel se pierde structura de lista
		nou->next = cursor->next;
		cursor->next = nou;
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
		cap = cap->next;
		free(cursor);
		rezultat = -1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		while (contor < pozitie - 1)
		{
			cursor = cursor->next;
			contor++;
		}
		nod* eliminat = cursor->next;
		cursor->next = eliminat->next;
		free(eliminat);
		rezultat = 1;
	}
	return rezultat;
}

void main() {
	nod* cap = NULL;
	cap = creare_lista();
	traversare(cap);
	cap = stergere_element(cap);
	traversare(cap);
	angajat a = citire_angajat_tastatura();
	cap = inserare_element(cap, a);
	traversare(cap);
	int pozitie;
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	int rez = inserare_element_pozitie(cap, a, pozitie);
	traversare(cap);
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	rez = stergere_pozitie(cap, pozitie);
	traversare(cap);
}