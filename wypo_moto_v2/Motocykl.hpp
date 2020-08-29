#pragma once
#include <string>
#include <vector>
using namespace std;

class Motocykl
{
	string model;
	int rocznik;
	float pojemnosc;
	mutable bool czy_zarezerwowany;
	float cena;

	friend void zapisz_baze_motocykli(vector <Motocykl>&);
	friend bool porownaj_motocykle(Motocykl&, Motocykl&);
	friend bool wyszukaj_ponizej_ceny(const Motocykl&);
	friend Motocykl& podwyzka_cen(Motocykl&);
	//friend bool ros_wedlug_marki(const Motocykl& l, const Motocykl& r);
public:
	string marka;
	Motocykl(string ma, string mo, int rok, float poj, bool rez, float c);
	~Motocykl();

	inline bool operator>(const Motocykl& moto) const //wedlug marki sortuje dla greater<>
	{
		return (marka > moto.marka);
	}
	void wyswietl_info_o_moto() const;
	bool czy_moto_istnieje_marka_model_poj(const string& ma, const string& mo, const float& poj);
	/*Motocykl& operator=(const Motocykl& arg) //to przeciazenie powoduje problemy z sortowaniem
	{
		return *this;
	}*/

	inline bool operator== (const Motocykl& m)
	{
		if ((this->marka == m.marka) && (this->model == m.model) && (this->rocznik == m.rocznik) && (this->pojemnosc == m.pojemnosc) && (this->czy_zarezerwowany == m.czy_zarezerwowany) && (this->cena == m.cena))
			return true;
		else
			return false;
	}
	struct rosnaco_wedlug_marki
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.marka < m2.marka);
		}
	};

	struct malejaco_wedlug_marki
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.marka > m2.marka);
		}
	};
	struct rosnaco_wedlug_modelu
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.model < m2.model);
		}
	};

	struct malejaco_wedlug_modelu
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.model > m2.model);
		}
	};
	struct rosnaco_wedlug_rocznika
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.rocznik < m2.rocznik);
		}
	};

	struct malejaco_wedlug_rocznika
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.rocznik > m2.rocznik);
		}
	};
	struct rosnaco_wedlug_pojemnosci
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.pojemnosc < m2.pojemnosc);
		}
	};

	struct malejaco_wedlug_pojemnosci
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.pojemnosc > m2.pojemnosc);
		}
	};
	struct rosnaco_wedlug_ceny
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.cena < m2.cena);
		}
	};

	struct malejaco_wedlug_ceny
	{
		inline bool operator() (const Motocykl& m1, const Motocykl& m2)
		{
			return (m1.cena > m2.cena);
		}
	};
	void zmien_status();
};
