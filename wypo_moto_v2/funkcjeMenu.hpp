#pragma once

#include <vector>
#include <memory> //unique_ptr

#include "Motocykl.hpp"
#include "Firma.hpp"

using namespace std;



extern int odp;

void zapisz_baze_motocykli(vector <Motocykl>& baza_motocykli);

void wczytaj_baze_motocykli(vector <Motocykl>& baza_motocykli);

bool wyszukaj_ponizej_ceny(const Motocykl& moto);

Motocykl& podwyzka_cen(Motocykl& moto);

void main_menu();

void moto_base_menu();

void delete_moto_menu();

void wyswietl_info_o_moto(const string& marka, const string& model, const int& rocznik, const float& pojemnosc, const bool& czy_zarezerwowany, const float& cena);

void wyswietl_baze_motocykli(vector <Motocykl>& baza_motocykli);


void usun_ostatnio_dodany_motocykl(vector <Motocykl>& baza_motocykli);

void usun_motocykl_wedlug_numeru(vector <Motocykl>& baza_motocykli);

void dodaj_motocykl_do_bazy(vector <Motocykl>& baza_motocykli);


void wyswietl_baze_firm(vector <unique_ptr<Firma>>& baza_klientow_firma);

bool porownaj_motocykle(Motocykl& a, Motocykl& b);

void usuwanie_wypozyczonych_motocykli_z_firmy(vector <Motocykl>& lista_wypozyczonych_moto, vector <Motocykl>& baza_motocykli);

void usun_ostatnio_dodana_firme(vector <unique_ptr<Firma>>& baza_klientow_firma, vector <Motocykl>& baza_motocykli);

////wywala blad
//void usun_firme_wedlug_numeru(vector <Firma>& baza_klientow_firma, vector <Motocykl>& baza_motocykli)
//{
//	cout << "Podaj numer firmy, ktora chcesz usunac: ";
//	int numer;
//	cin >> numer;
//
//	cout << "\nZostanie usunieta firma o nastepujacych danych:\n";
//	baza_klientow_firma[numer-1].pokaz_dane();
//	cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
//	cin >> odp;
//
//	if (odp == 1)
//	{
//		usuwanie_wypozyczonych_motocykli_z_firmy(baza_klientow_firma[numer - 1].lista_wypozyczonych_moto, baza_motocykli);
//
//		baza_klientow_firma.erase(baza_klientow_firma.begin() + numer - 1);
//		cout << "\Firma zostala usunieta z bazy.\n";
//	}
//	else if (odp == 0)
//	{
//		cout << "Usuwanie zostalo anulowane.";
//	}
//}

void wypozycz_motocykl_firmie(vector <Motocykl>& baza_motocykli, vector <unique_ptr<Firma>>& baza_klientow_firma);

//auto ros_wedlug_marki = [](const Motocykl & l, const Motocykl & r)  { return (l.marka < r.marka); } ->bool;