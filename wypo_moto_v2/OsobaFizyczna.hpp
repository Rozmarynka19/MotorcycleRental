#pragma once
#include <string>
#include <vector>
#include "Klient.hpp"
#include "Motocykl.hpp"
#include "Data.hpp"

using namespace std;
//
//struct Klient;
//class Motocykl;
//class Data;

//dziedziczenie wielopoziomowe
class OsobaFizyczna final :private Klient //po klasie Osoba_fizyczna nie mozna juz dziedziczyc
{
	string imie, nazwisko;
	Data urodzenia;
	const long pesel;
	vector<Motocykl> lista_wypozyczonych_moto;
public:
	OsobaFizyczna(Data ur, string im, string naz, const long pe);
	void pokaz_dane() override;

};

