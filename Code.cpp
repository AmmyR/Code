/*
 * [!] Il programma NON FUNZIONA su sistemi operativi non Windows.
 */
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <iostream>

using namespace std;

#define SOPRA 'T'
#define SOTTO 'G'
#define ENTER 13

//Definizione della lista (struttura)
struct prodotti
{
	int id;
	char nome[50]; //Massimo 50 caratteri
	struct prodotti *primo;
} *ultimo = NULL, *assistente = NULL, *prim = NULL;

//Prototipi di funzione
void insersire(void); //Inserisce un elemento nella coda della lista
void lista(void);	  //Mostra tutti gli elementi della lista
void menu(void);	  //Invia al menu principale del programma
void rimuovi(void);   //Elimina la voce corrente nella coda della lista
char tastiera(void);  //Ottiene i caratteri dalla tastiera per potersi muovere tra le pozioni nel menu principale
void gotoxy(int x, int y);
int selezione(string titolo, const char *opzioni[], int n);

int main()
{
	setlocale(LC_ALL, "Italian");
	menu();
	
	return 0;
}

void menu(void)
{
	bool valido = false;
	
	string titolo = "\t\t>> C/C++ Code << \n\t\t      - Menu principale -             \n\tNavigazione: T -> SOPRA, G -> SOTTO. ENTER per selezionare.\n";
	const char *opciones[] = {"Aggiungi un elemento alla coda", "Visualizza tutti gli elementi della lista", "Rimuovi elemento dalla coda", "Sali"};
	int n = 4;
	
	do
	{
		int opzione = selezione(titolo, opciones, n);
		
		switch(opzione)
		{
			case 1:
				insersire();
				valido = true;
			break;
			
			case 2:
				lista();
				valido = true;
			break;
			
			case 3:
				rimuovi();
				valido = true;
			break;
			
			case 4:
				exit(EXIT_SUCCESS);
			break;
		}
	} while(valido == false);
}

void insersire(void)
{
	system("cls");
	
	assistente = (struct prodotti*) malloc(sizeof( struct prodotti));
	
	if (assistente == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 12);
		cout << "[!] Nessuna memoria disponibile";
		exit(EXIT_FAILURE);
	}
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 11);
	cout << "\t\t- Aggiungi un elemento alla coda -\n\n";
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
	cout << "\t> Indica l'ID del prodotto: "; scanf("%i", &assistente->id);
	cout << "\n\t> Scrivi il nome del prodotto: "; scanf("%s", assistente->nome);
	
	assistente->primo= NULL;
	
	if (prim == NULL)
	{
		ultimo = assistente;
		prim = ultimo;
	}
	else
	{
		ultimo->primo = assistente;
		ultimo = assistente;			 
	}
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 10);
	cout << "\n\t- Dati salvati con successo. ";
	system("pause");
	
	menu();
}

void lista(void)
{
	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 11);
	cout << "\t\t- Visualizza tutti gli elementi della lista -\n\n";
	
	if(prim == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 12);     
		printf("[!] La coda non contiene elementi salvati. ");
		system("pause");
		menu();
	}
	
	assistente = prim;
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
	while(assistente != NULL)
	{                       
		cout << "\t> ID: " << assistente->id << "   Nome: " << assistente->nome << "\n";
		assistente = assistente->primo;		
	}
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 10);
	cout << "\n- Non ci sono più articoli da visualizzare. ";
	system("pause");
	menu();
}

void rimuovi(void)
{
	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 11);
	cout << "\t\t- Rimuovi elemento dalla coda -\n\n";
	
	if(prim == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 12);     
		printf("[!] La coda non contiene elementi salvati. ");
		system("pause");
		menu();
	}
	
	assistente = prim;

	if(prim == ultimo){
		prim = NULL;
		ultimo = NULL;
	}
	else prim = prim->primo;
	
	free(assistente);
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 10);
	cout << "\n\t- L'elemento che era in coda è stato rimosso. ";
	system("pause");
	
	menu();
}

char tastiera(void)
{
	char c = 0;
	DWORD mod, contabile;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	
	//Disabilita la scrittura all'interno del terminale
	SetConsoleMode(ih, mod & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	
	ReadConsole(ih, &c, 1, &contabile, NULL);
	
	if (c == 0)
	  ReadConsole(ih, &c, 1, &contabile, NULL);
	
	//Restituisce il controllo normale al terminale
	SetConsoleMode(ih, mod);
	
	return c;
}

void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

int selezione(string titolo, const char *opzioni[], int n)
{
	//Indica la posizione selezionata
	int posizione = 1, tasto;
	
	//Controlla il ciclo do-while
	bool ripeti = true;
	
	do
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 8);
		cout << "\tQuesto progetto è di dominio pubblico. Github: https://github.com/AmmyR";
		
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 10);
		gotoxy(5, 5 + posizione); cout << "\t>>" << endl;
		
		//Mostra il titolo
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 11);
		gotoxy(15, 2); cout << titolo;
		
		//Mostra le opzioni del menu principale
		for (int i = 0; i < n; ++i)
		{
			gotoxy(10, 6 + i);
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
			cout << "\t" << i + 1 << ") " << opzioni[i];	
		}
		
		do
		{
			tasto = tastiera();
		} while (tasto != SOPRA && tasto != SOTTO && tasto != ENTER);
 
		switch (tasto)
		{
			case SOPRA:
				posizione--;
				
				if (posizione < 1)
					posizione = n;
			break;
			
			case SOTTO:
				posizione++;
				
				if (posizione > n)
				   posizione = 1;
			break;
			
			case ENTER:
				ripeti = false;
			break;
		}
	} while(ripeti);
	
 	return posizione;
}
