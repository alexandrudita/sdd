///*
// Suport teoretic HEAP: http://acs.ase.ro/Media/Default/documents/structuri/2019/Struct-heap.pdf
//
// Pentru acest seminar de vazut urmatoarele fisiere: 
// - sursa de date pentru vectorul de apeluri https://github.com/alexandrudita/sdd/blob/master/util/apeluri_urgenta.txt
// - pseudocodul pentru initializarea unui heap plecand de la vectorul de mai sus https://github.com/alexandrudita/sdd/blob/master/util/ex_initializare_heap_seminar7.txt
//*/
//
//#define _CRT_SECURE_NO_WARNINGS 
//#include<stdlib.h>
//#include<stdio.h>
//#include<string.h>
//
//struct ApelUrgenta {
//	int cod;
//	int prioritate;
//	char adresa[100];
//};
//
//struct Heap {
//	ApelUrgenta* elemente;
//	int dim_maxima;
//	int dim_efectiva;
//};
//
////==================================== GESTIONARE FISIER =========================================
//
//ApelUrgenta citire_apel_urgenta_fisier(FILE* fisier) {
//	ApelUrgenta apel;
//	fscanf_s(fisier, "%d", &apel.cod);
//	fscanf_s(fisier, "%d", &apel.prioritate);
//	fgetc(fisier);//fflush
//	fgets(apel.adresa, 100, fisier);
//	strtok(apel.adresa, "\n");
//	return apel;
//}
//
//ApelUrgenta citire_apel_urgenta_consola() {
//	ApelUrgenta apel;
//	printf("\nCod: ");
//	scanf_s("%d", &apel.cod);
//	printf("\nPrioritate: ");
//	scanf_s("%d", &apel.prioritate);
//	getc(stdin);
//	printf("\nAdresa: ");
//	gets_s(apel.adresa, 100);
//	return apel;
//}
//
//void afisare_apel_urgenta(ApelUrgenta apel) {
//	printf("\nCod: %d Prioritate: %d Adresa: %s", apel.cod, apel.prioritate, apel.adresa);
//}
//
//ApelUrgenta* citire_apeluri_urgenta_fisier(int &nr) {
//	ApelUrgenta* apeluri = NULL;
//	//declaram variabila pentru lucru cu fisier
//	FILE* fisier;
//	//deschidere fisier
//	fopen_s(&fisier, "apeluri_urgenta.txt", "r");
//	//verificam daca fisierul s-a deschis
//	if (fisier != NULL) {
//		//preluare numar de elemente din fisier. Restrictie linia 1 din fisier avem numarul de elemente
//		fscanf_s(fisier, "%d", &nr);
//		//alocare spatiu de memorie pentru vector
//		apeluri = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*nr);
//		//citim fiecare element din fisier
//		for (int i = 0; i < nr; i++) {
//			apeluri[i] = citire_apel_urgenta_fisier(fisier);
//		}
//		//inchidere fisier
//		fclose(fisier);
//	}
//	else {
//		printf("\nFisierul nu s-a putut deschide");
//	}
//	return apeluri;
//}
//
//void afisare_apeluri_urgenta(ApelUrgenta* apeluri, int nr) {
//	for (int i = 0; i < nr; i++) {
//		afisare_apel_urgenta(apeluri[i]);
//	}
//}
//
////================================ METODE HEAP ========================================
//
//void interschimbare(Heap &heap, int max, int pozitie) {
//	ApelUrgenta aux = heap.elemente[max];
//	heap.elemente[max] = heap.elemente[pozitie];
//	heap.elemente[pozitie] = aux;
//}
//
//void filtrare(Heap &heap, int parinte) {
//	//formula pentru a identifica pozitia fiului stanga 
//	int pozitieFiuStanga = 2 * parinte + 1;
//	//formula pentru a identifica pozitia fiului dreapta
//	int pozitieFiuDreapta = 2 * parinte + 2;
//	//intializam o variabila intermediara pentru a identifica care este pozitia cu prioritatea cea mai mare
//	int max = parinte;
//	//verificam daca prioritatea fiului din stanga este mai mare decat a parintelui
//	if (pozitieFiuStanga < heap.dim_efectiva &&
//		heap.elemente[max].prioritate < heap.elemente[pozitieFiuStanga].prioritate) {
//		//schimbam pozitia elementului cu prioritatea mai mare
//		max = pozitieFiuStanga;
//	}
//	//verificam daca prioritatea fiului din dreapta este mai mare decat a parintelui
//	if (pozitieFiuDreapta < heap.dim_efectiva &&
//		heap.elemente[max].prioritate < heap.elemente[pozitieFiuDreapta].prioritate) {
//		//schimbam pozitia elementului cu prioritatea mai mare
//		max = pozitieFiuDreapta;
//	}
//	//verificam daca am gasit un fiu cu o prioritate mai mare decat a parintelui
//	if (max != parinte) {
//		//inlocuim parintele acestui subarbore
//		interschimbare(heap, max, parinte);
//		//daca am schimbat maxim trebuie sa reapelam filtrarea pentru noua pozitie
//		filtrare(heap, max);
//	}
//}
//
//void afisare_heap(Heap heap) {
//	for (int i = 0; i < heap.dim_efectiva; i++) {
//		afisare_apel_urgenta(heap.elemente[i]);
//	}
//}
//
//void initializare_heap(Heap *heap, ApelUrgenta elemente[], int numar_elemente, int dimensiune_maxima)
//{
//	// initializam dimensiunile din heap
//	heap->dim_maxima = dimensiune_maxima;
//	heap->dim_efectiva = numar_elemente;
//	// copiem elementele din vector in heap
//	heap->elemente = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*numar_elemente);
//	for (int i = 0; i < numar_elemente; i++)
//	{
//		heap->elemente[i] = elemente[i];
//	}
//	//Ca sa obtinem structura de heap trebuie sa respectam proprietatile din algoritm, 
//	//si anume elementul cu priotatea cea mai mare se afla in radacina arborelui, adica pozita 0 
//	//din vectorul elemente.
//	//Pentru realizarea acestui lucru trebuie sa utilizam metoda de filtrare definita mai sus. 
//	//Metoda este apelata doar pentru elementele din prima jumatate a vectorului 
//	//deoarece elementele din cea de a doua jumatate sunt subarbori care au maxim 1 element.
//	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
//	{
//		filtrare(*heap, i);
//	}
//}
//
//void inserare_heap(Heap &heap, ApelUrgenta apel) {
//	//verificam daca mai avem loc in heap.
//	if (heap.dim_efectiva < heap.dim_maxima) {
//		//trebuie sa aplicam algoritmul de adaugare a unui element intr-un vector alocat dinamic
//		//prima data se initializeaza o variabila temp pentru a stoca noul vector cu o dimensiune mai mare
//		ApelUrgenta* temp = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*(heap.dim_efectiva + 1));
//		//copiere elemente deja stocate
//		for (int i = 0; i < heap.dim_efectiva; i++) {
//			temp[i] = heap.elemente[i];
//		}
//		//conform conceptului de heap noul element se adauga pe ultima pozitia din arbore astfel incat
//		//sa nu stricam ordinea existanta.
//		temp[heap.dim_efectiva] = apel;
//		//dezalocare elemente existente
//		free(heap.elemente);
//		//actualizare noua dimensiune efectiva
//		heap.dim_efectiva++;
//		//adaugam noua lista de elemente in heap
//		heap.elemente = temp;
//		//a doua conditie a unui heap este sa contina elementul cu prioritatea cea mai mare in varful arborelui
//		//prin urmare, incercam sa urcam noul element cat mai sus in heap in functie de prioritate
//		int indexFiu = heap.dim_efectiva - 1;//initial este ultimul element, adica cel pe care l-am adaugat
//		int indexParinte = (indexFiu - 1) / 2;//calculam parintele acestuia in vector
//		//facem urcarea in vector cat timp prioritatea parintelui este mai mica decat prioritatea fiului
//		while (indexParinte >= 0 
//			&& heap.elemente[indexFiu].prioritate > heap.elemente[indexParinte].prioritate) {
//			interschimbare(heap, indexFiu, indexParinte);
//			indexFiu = indexParinte;
//			indexParinte = (indexFiu - 1) / 2;
//		}
//	}
//	else {
//		printf("\nNu mai este loc disponibil in heap");
//	}
//}
//
//ApelUrgenta extragere_heap(Heap &heap) {
//	//verificam daca mai avem elemente in heap, altfel nu avem ce sa stergem
//	if (heap.dim_efectiva > 0) {
//		//extragem elementul maxim
//		ApelUrgenta apel = heap.elemente[0];
//		//aplicam algoritmul de extragere a unui element dintr-un vector alocat dinamic
//		//definim o variabila intermediara in care stocam noul vector
//		ApelUrgenta* temp = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*(heap.dim_efectiva - 1));
//		//copiem elementele in noul vector
//		for (int i = 1; i < heap.dim_efectiva; i++) {
//			temp[i - 1] = heap.elemente[i];
//		}
//		//inlocuirea noului element
//		free(heap.elemente);
//		heap.elemente = temp;
//		//recalculam dimensiunea efectiva
//		heap.dim_efectiva--;
//		//reaplicam algoritmul de filtrare, astfel incat sa pastram conceptul de heap
//		for (int i = (heap.dim_efectiva - 1) / 2; i >= 0; i--) {
//			filtrare(heap, i);
//		}
//		return apel;
//	}
//	else {
//		printf("\nNu mai exista elemente in heap");
//	}
//}
//
//void dezalocare_heap(Heap heap) {
//	if (heap.dim_efectiva > 0 && heap.elemente != NULL) {
//		free(heap.elemente);
//	}
//}
//
//void main() {
//	int nr;
//	ApelUrgenta* apeluri = citire_apeluri_urgenta_fisier(nr);
//	afisare_apeluri_urgenta(apeluri, nr);
//	printf("\n-------------------------- Alocare Heap ----------------------------------------\n");
//	Heap heap;
//	initializare_heap(&heap, apeluri, nr, 100);
//	afisare_heap(heap);
//	printf("\n-------------------------- Inserare Heap ----------------------------------------\n");
//	int ok = 1;
//	while (ok == 1) {
//		ApelUrgenta apelNou = citire_apel_urgenta_consola();
//		inserare_heap(heap, apelNou);
//		printf("\nDoriti sa mai adaugati apeluri? Da-1/Nu-0");
//		scanf_s("%d", &ok);
//	}
//	afisare_heap(heap);
//	printf("\n-------------------------- Extragere Heap ----------------------------------------\n");
//	ApelUrgenta extrax = extragere_heap(heap);
//	afisare_heap(heap);
//	dezalocare_heap(heap);
//}