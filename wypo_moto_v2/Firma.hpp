#pragma once

#include <string>
#include <vector>
#include <memory> //unique_ptr
#include "Klient.hpp"
#include "Motocykl.hpp"
#include "Data.hpp"

using namespace std;

class Firma final :private Klient //jak wyzej
{
	const long regon;
	string nazwa;
	vector<Motocykl> lista_wypozyczonych_moto;

	friend void wyswietl_baze_firm(vector <unique_ptr<Firma>>&);
	friend void usun_ostatnio_dodana_firme(vector <unique_ptr<Firma>>&, vector <Motocykl>&);
	friend void usun_firme_wedlug_numeru(vector <Firma>&, vector <Motocykl>&);
	friend void usuwanie_wypozyczonych_motocykli_z_firmy(vector <Firma>&, vector <Motocykl>&, int);
	friend void wypozycz_motocykl_firmie(vector <Motocykl>&, vector <unique_ptr<Firma>>&);

public:
	Firma(string naz, const long re);
	~Firma();
	void pokaz_dane() override;
	void wyswietl_info() override;
};