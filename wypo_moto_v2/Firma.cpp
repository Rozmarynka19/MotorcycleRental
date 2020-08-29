#include "Firma.hpp"

#include <iostream>

Firma::Firma(string naz = "", const long re = 0) : regon(re), nazwa(naz) {}
Firma::~Firma() 
{ 
	cout << "Jestem desktruktorem i zniszcze Wasz wszystkich! MUHAHAHA!";
}

void Firma::pokaz_dane()
{
	cout << "Dane klienta:\nNazwa firmy: " << nazwa << endl;
	cout << "REGON: " << regon;
	cout << "\nLista wypozyczonych motocykli:\n";
	for (int i = 0; i < lista_wypozyczonych_moto.size(); i++)
	{
		lista_wypozyczonych_moto[i].wyswietl_info_o_moto();
	}
}
void Firma::wyswietl_info()
{
	cout << "\t" << nazwa << "\t" << regon << endl;
}