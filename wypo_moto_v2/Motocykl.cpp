#include <iostream>
#include "Motocykl.hpp"

Motocykl::Motocykl(string ma = "", string mo = "", int rok = 0, float poj = 0.0, bool rez = false, float c = 0.0) : marka(ma), model(mo), rocznik(rok), pojemnosc(poj), czy_zarezerwowany(rez)
{
	cena = c;
}

Motocykl::~Motocykl() {}

void Motocykl::wyswietl_info_o_moto() const
{
	cout << "\t" << this->marka << "\t\t" << this->model << "\t\t" << this->rocznik << "\t\t" << this->pojemnosc << "\t\t" << this->czy_zarezerwowany << "\t\t" << this->cena;
}

bool Motocykl::czy_moto_istnieje_marka_model_poj(const string& ma, const string& mo, const float& poj)
{
	if ((this->marka.compare(ma) == 0) && (this->model.compare(mo) == 0) && (this->pojemnosc == poj))
		return true;
	else
		return false;
}

void Motocykl::zmien_status()
{
	if (czy_zarezerwowany)
		czy_zarezerwowany = 0;
	else
		czy_zarezerwowany = 1;
}
