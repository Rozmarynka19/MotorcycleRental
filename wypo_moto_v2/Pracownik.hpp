#pragma once

#include <string>
#include "Data.hpp"

using namespace std;

class Pracownik
{
	string imie, nazwisko;
	Data urodzenia;
	float wynagrodzenie;

public:
	Pracownik(string im, string nazw, float wy, Data uro);
	void wyswietl_info();
	bool operator<(const Pracownik& prac); //wedlug nazwiska sortuje dla less<>
};