#include "OsobaFizyczna.hpp"
#include <iostream>


OsobaFizyczna::OsobaFizyczna(Data ur, string im = "", string naz = "", const long pe = 0) : pesel(pe), urodzenia(ur)
{
	imie = im;
	nazwisko = naz;
}

void OsobaFizyczna::pokaz_dane()
{
	cout << "Dane klienta:\nImie: " << imie << "\nNazwisko: " << nazwisko << "Data urodzenia: ";
	urodzenia.pokaz();
	cout << "PESEL: " << pesel;
	cout << "\nLista wypozyczonych motocykli:\n";
	for (int i = 0; i < lista_wypozyczonych_moto.size(); i++)
	{
		lista_wypozyczonych_moto[i].wyswietl_info_o_moto();
	}
}