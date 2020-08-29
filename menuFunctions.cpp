#include "menuFunctions.h"
#include <iostream>
using namespace std;

extern int odp;

void main_menu()
{
	//system("cls");
	cout << "\t\tWypozyczalnia Motocykli MotoRent\n\n1.Baza motocykli.\n2.Baza klientow.\n3.Baza pracownikow\n*4.Oczekujace zlecenia.\n5.Wczytaj baze.\n6.Zapisz baze\n0.Zakoncz.\n";
	cin >> odp;
}

void moto_base_menu()
{
	//system("cls");
	cout << "\t\tCo chcesz zrobic z baza motocykli?\n1.Wyswietl baze.\n2.Dodaj motocykl.\n3.Usun motocykl.\n4.Sortuj baze.\n5.Zmien rekord w bazie\n6.Wyszukaj motocykl.\n7.Wyszukaj motocykle ponizej 100zl.\n8.Podwyz ceny motocykli o 50zl.\n9.Usun duplikaty w bazie.\n0.Wroc do poprzedniego menu.\n";
	cin >> odp;
}

void delete_moto_menu()
{
	//system("cls");
	cout << "\n1.Usun ostatnio dodany.\n2.Usun wedlug podanego numeru.\n0.Wroc do poprzedniego menu.\n";
	cin >> odp;
}