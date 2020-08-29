#pragma once

struct Klient //ta klasa ma byc abstrakcyjna
{
	virtual void pokaz_dane() = 0;
	//virtual void wypozycz_motocykl(Motocykl &moto) = 0;
	virtual void wyswietl_info() = 0;
	//virtual void dodaj_do_listy() = 0;
	//virtual void usun_z_listy() = 0;
};