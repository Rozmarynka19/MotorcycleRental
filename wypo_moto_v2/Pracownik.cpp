#include "Pracownik.hpp"

#include <iostream>

Pracownik::Pracownik(string im, string nazw, float wy, Data uro) :urodzenia(uro)
{
	imie = im;
	nazwisko = nazw;
	wynagrodzenie = wy;
}
void Pracownik::wyswietl_info()
{
	cout << imie << "\t" << nazwisko << "\t";
	urodzenia.pokaz();
	cout << "\t" << wynagrodzenie << endl;
}
bool Pracownik::operator<(const Pracownik& prac) //wedlug nazwiska sortuje dla less<>
{
	return (nazwisko < prac.nazwisko);
}