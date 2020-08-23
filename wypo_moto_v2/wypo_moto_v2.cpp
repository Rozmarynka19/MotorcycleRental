// wypo_moto_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
U¯YTO:
-greater
-partition
-transform
-unique

Kontenery asocjacyjne
-map
Metody w ramach kontenera asocjacyjnego
-find
-begin
-end
-insert
-swap
-erase
-make pair - w ramach typu Pair
-frist, second - w ramach typu Pair

Inteligente wskaŸniki (move, get (L13), wskaznik na wektor, virtualny destruktor -> komunikat (wyklad))
-unique_ptr<>
-make_unique<>()
*/
/*
pliki i wyjatki - ostatnie zajecia
stworzyc jakas kolekcje
zapisujemy
odczytujemy

obsluga wyjatkow try catch
throw rzucanie wyjatkiem
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <memory> //unique_ptr<>
#include <fstream>
//#include <iterator>

using namespace std;

int odp;

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
	Motocykl(string ma = "", string mo = "", int rok = 0, float poj = 0.0, bool rez = false, float c = 0.0) : marka(ma), model(mo), rocznik(rok), pojemnosc(poj), czy_zarezerwowany(rez)
	{
		cena = c;
	}
	~Motocykl() {}
	inline bool operator>(const Motocykl& moto)const //wedlug marki sortuje dla greater<>
	{
		return (marka > moto.marka);
	}
	void wyswietl_info_o_moto() const
	{
		cout << "\t" << this->marka << "\t\t" << this->model << "\t\t" << this->rocznik << "\t\t" << this->pojemnosc << "\t\t" << this->czy_zarezerwowany << "\t\t" << this->cena;
	}
	bool czy_moto_istnieje_marka_model_poj(const string &ma, const string &mo, const float &poj)
	{
		if((this->marka.compare(ma)==0)&&(this->model.compare(mo)==0)&&(this->pojemnosc==poj))
			return true;
		else
			return false;
	}
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
	void zmien_status()
	{
		if (czy_zarezerwowany)
			czy_zarezerwowany = 0;
		else
			czy_zarezerwowany = 1;
	}


};

void zapisz_baze_motocykli(vector <Motocykl>& baza_motocykli)
{
	ofstream plik;
	string nazwa;

	cout << "\nPodaj nazwe zapisywanego pliku: ";
	cin >> nazwa;

	plik.open(nazwa);

	if (plik.good())
	{
		//wykonujemy zapis

		for (int i = 0; i < baza_motocykli.size(); i++)
		{
			plik << baza_motocykli[i].marka << endl;
			plik << baza_motocykli[i].model << endl;
			plik << baza_motocykli[i].rocznik << endl;
			plik << baza_motocykli[i].pojemnosc << endl;
			plik << baza_motocykli[i].czy_zarezerwowany << endl;
			if (i == baza_motocykli.size() - 1)	plik << baza_motocykli[i].cena; //nie moze byc pustej linii jak ostatniej, bo pozniej przy odczycie jest problem i dodaje smieciowe rzeczy
			else plik << baza_motocykli[i].cena << endl;
		}
		cout << "\nBaza motocykli zostala zapisana." << endl;
	}
	else
	{
		//wyjatek cos poszlo nie tak
		cout << "\nNie mozna otworzyc pliku!" << endl;
	}
}

void wczytaj_baze_motocykli(vector <Motocykl>& baza_motocykli)
{
	ifstream plik;
	string nazwa;

	cout << "\nPodaj nazwe pliku do odczytania: ";
	cin >> nazwa;

	plik.open(nazwa);

	if (plik.good())
	{
		//kod do wykonywania gdy poprawnie plik sie otworzy
		while (!plik.eof())//wczytywanie po kolei zmiennych i na koncu tworzenie z nich obiektu typu Motocykl i dodanie go na koniec do vectora
		{
			string ma,mo; //marka, model
			int rok; //rocznik
			float poj; //pojemnosc
			bool rez; //czy zarezerwowany
			float c; //cena

			string linia;

			getline(plik, ma);
			getline(plik, mo);
			getline(plik, linia);
			rok = atoi(linia.c_str()); //konwersja stringa na int
			getline(plik, linia);
			poj = stof(linia); //konwersja stringa na float
			getline(plik, linia);
			rez = linia.compare("1")? true: false;//konwersja stringa na bool
			getline(plik, linia);
			c = stof(linia);//konwersja stringa na float

			baza_motocykli.push_back(Motocykl(ma, mo, rok, poj, rez, c));
		}

		cout << "\nBaza motocykli zostala wczytana." << endl;
	}
	else
	{
		//kod do wykonania gdy np pliku o podanej nazwie nie ma na dysku
		//tutaj wygenerujemy wyjatek, zlapiemy go, itd..
		//cout << "\nPlik nie zostal odczytany!" << endl;

		try
		{
			throw logic_error("Plik nie zostal odczytany!");
		}
		catch (logic_error & error)
		{
			cout << "Logic error: " << error.what() << " Upewnij sie, ze podales dobra sciezke dostepu do pliku." << endl;
			//terminate();
		}
	}
}

bool wyszukaj_ponizej_ceny(const Motocykl& moto)
{
	return (moto.cena < 100);
}

Motocykl& podwyzka_cen( Motocykl& moto)
{
	moto.cena = moto.cena + 50;
	return moto;
}

void main_menu()
{
	//system("cls");
	cout << "\t\tWypozyczalnia Motocykli MotoRent\n\n1.Baza motocykli.\n2.Baza klientow.\n3.Baza pracownikow\n*4.Oczekujace zlecenia.\n5.Wczytaj baze.\n6.Zapisz baze\n0.Zakoncz.\n";
	cin >> odp;
}

void moto_base_menu()
{
	//system("cls");
	cout << "\t\tCo chcesz zrobic z baza motocykli?\n1.Wyswietl baze.\n2.Dodaj motocykl.\n3.Usun motocykl.\n4.Sortuj baze.\n5.Zmien rekord w bazie\n6.Wyszukaj motocykl.\n7.Wyszukaj motocykle ponizej 100zl.\n8.Podwyz ceny motocykli o 50zl.\n9.Usun duplikaty w bazie.\n0.Wroc do poprzedniego menu.\n";
	cin >> odp;
}

void delete_moto_menu()
{
	//system("cls");
	cout << "\n1.Usun ostatnio dodany.\n2.Usun wedlug podanego numeru.\n0.Wroc do poprzedniego menu.\n";
	cin >> odp;
}

void wyswietl_info_o_moto(const string &marka, const string &model, const int & rocznik, const float & pojemnosc, const bool & czy_zarezerwowany, const float & cena)
{
	cout << "\t" << marka << "\t\t" << model << "\t\t" << rocznik << "\t\t" << pojemnosc << "\t\t" << czy_zarezerwowany << "\t\t" << cena;
}

void wyswietl_baze_motocykli(vector <Motocykl>& baza_motocykli)
{
	//system("cls");
	if (baza_motocykli.empty())
	{
		cout << "Baza motocykli jest pusta! Brak informacji do wypisania." << endl;
	}
	else
	{
		for (int i = 0; i < baza_motocykli.size(); i++)
		{
			cout << i + 1 << "\t";
			baza_motocykli[i].wyswietl_info_o_moto();
			cout << endl;
		}
	}/*
	getchar();
	getchar();*/
}


void usun_ostatnio_dodany_motocykl(vector <Motocykl>& baza_motocykli)
{
	int iterator = baza_motocykli.size() - 1;
	cout << "Zostanie usuniety motocykl o nastepujacych danych:\n";
	baza_motocykli[iterator].wyswietl_info_o_moto();
	cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
	cin >> odp;

	if (odp == 1)
	{
		baza_motocykli.pop_back();
		cout << "\nMotocykl zostal usuniety z bazy.\n";
	}
	else if (odp == 0)
	{
		cout << "Usuwanie zostalo anulowane.";
	}
}

void usun_motocykl_wedlug_numeru(vector <Motocykl>& baza_motocykli)
{
	cout << "Podaj numer motocykla, ktory chcesz usunac: ";
	int numer;
	cin >> numer;

	cout << "\nZostanie usuniety motocykl o nastepujacych danych:\n";
	baza_motocykli[numer-1].wyswietl_info_o_moto();
	cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
	cin >> odp;

	if (odp == 1)
	{
		baza_motocykli.erase(baza_motocykli.begin() + numer - 1);
		cout << "\nMotocykl zostal usuniety z bazy.\n";
	}
	else if (odp == 0)
	{
		cout << "Usuwanie zostalo anulowane.";
	}
}

void dodaj_motocykl_do_bazy(vector <Motocykl>& baza_motocykli)
{
	//system("cls");
	cout << "\nIle motocykli chcesz dodac?\n";
	int ile;
	cin >> ile;

	string marka, model;
	int rocznik;
	float pojemnosc;
	bool czy_zarezerwowany;
	float cena;

	for (int i = 0; i < ile; i++)
	{
		getchar();
		cout << "\nPodaj marke motocykla: ";
		getline(cin, marka);
		cout << "\nPodaj model motocykla: ";
		getline(cin, model);
		cout << "\nPodaj rocznik motocykla: ";
		cin >> rocznik;
		cout << "\nPodaj pojemnosc motocykla [w litrach]: ";
		cin >> pojemnosc;
		cout << "\nCzy motocykl jest zarezerwowany?(0-nie,1-tak): ";
		cin >> czy_zarezerwowany;
		cout << "\nPodaj cene rezerwacji za godzine [w PLN]: ";
		cin >> cena;

		baza_motocykli.push_back(Motocykl(marka, model, rocznik, pojemnosc, czy_zarezerwowany, cena));
	}
}

class Data
{
	int dzien, miesiac, rok;
public:
	Data(int d = 0, int m = 0, int r = 0)
	{
		dzien = d;
		miesiac = m;
		rok = r;
	}
	void pokaz() const
	{
		cout << dzien << "/" << miesiac << "/" << rok << endl;
	}
};

struct Klient //ta klasa ma byc abstrakcyjna
{
	virtual void pokaz_dane() = 0;
	//virtual void wypozycz_motocykl(Motocykl &moto) = 0;
	virtual void wyswietl_info() = 0;
	//virtual void dodaj_do_listy() = 0;
	//virtual void usun_z_listy() = 0;

	
};

//dziedziczenie wielopoziomowe
class Osoba_fizyczna final :private Klient //po klasie Osoba_fizyczna nie mozna juz dziedziczyc
{
	string imie, nazwisko;
	Data urodzenia;
	const long pesel;
	vector<Motocykl> lista_wypozyczonych_moto;
public:
	Osoba_fizyczna(Data ur,string im = "", string naz="", const long pe = 0) : pesel(pe), urodzenia(ur)
	{
		imie = im;
		nazwisko = naz;
	}
	void pokaz_dane() override
	{
		cout << "Dane klienta:\nImie: " << imie << "\nNazwisko: " << nazwisko << "Data urodzenia: ";
		urodzenia.pokaz();
		cout << "PESEL: " << pesel;
		cout << "\nLista wypozyczonych motocykli:\n";
		for (int i = 0; i < lista_wypozyczonych_moto.size();i++)
		{
			lista_wypozyczonych_moto[i].wyswietl_info_o_moto();
		}
	}

};

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
	Firma(string naz = "", const long re = 0) : regon(re), nazwa(naz) {}
	~Firma() { cout << "Jestem desktruktorem i zniszcze Wasz wszystkich! MUHAHAHA!"; }
	void pokaz_dane() override
	{
		cout << "Dane klienta:\nNazwa firmy: " << nazwa << endl;
		cout << "REGON: " << regon;
		cout << "\nLista wypozyczonych motocykli:\n";
		for (int i = 0; i < lista_wypozyczonych_moto.size(); i++)
		{
			lista_wypozyczonych_moto[i].wyswietl_info_o_moto();
		}
	}
	void wyswietl_info() override
	{
		cout << "\t" << nazwa << "\t" << regon << endl;
	}
};

class Pracownik
{
	string imie, nazwisko;
	Data urodzenia;
	float wynagrodzenie;
	
public:
	Pracownik(string im, string nazw, float wy, Data uro) :urodzenia(uro)
	{
		imie = im;
		nazwisko = nazw;
		wynagrodzenie = wy;
	}
	void wyswietl_info()
	{
		cout << imie << "\t" << nazwisko << "\t";
		urodzenia.pokaz();
		cout << "\t" << wynagrodzenie << endl;
	}
	bool operator<(const Pracownik& prac) //wedlug nazwiska sortuje dla less<>
	{
		return (nazwisko < prac.nazwisko);
	}
	
};

void wyswietl_baze_firm(vector <unique_ptr<Firma>>& baza_klientow_firma)
{
	//system("cls");
	if (baza_klientow_firma.empty())
	{
		cout << "Baza motocykli jest pusta! Brak informacji do wypisania." << endl;
	}
	else
	{
		for (int i = 0; i < baza_klientow_firma.size(); i++)
		{
			cout << i + 1 << "\t";
			baza_klientow_firma[i]->wyswietl_info();
			if (baza_klientow_firma[i]->lista_wypozyczonych_moto.empty())
				cout << "\t\tBrak wypozyczonych motocykli.\n";
			else
				for (int j = 0; j < baza_klientow_firma[i]->lista_wypozyczonych_moto.size(); j++)
				{
					cout << j + 1 << "\t" << endl;
					baza_klientow_firma[i]->lista_wypozyczonych_moto[j].wyswietl_info_o_moto();
					cout << endl;
				}
			cout << endl;
		}
	}
	//getchar();
	//getchar();
}

bool porownaj_motocykle(Motocykl& a,Motocykl& b)
{
	if (((a.marka).compare(b.marka) == 0) && ((a.model).compare(b.model) == 0) && (a.pojemnosc == b.pojemnosc) && (a.rocznik==b.rocznik) && (a.czy_zarezerwowany==b.czy_zarezerwowany) && (a.cena==b.cena))
		return true;
	else
		return false;
}

void usuwanie_wypozyczonych_motocykli_z_firmy(vector <Motocykl>& lista_wypozyczonych_moto, vector <Motocykl>& baza_motocykli)
{
	//znajdz w glownej bazie moto te motocykle ktore zostaly wypozyczone i ustaw ich wypozyczenie na false
	for (int i = 0; i < lista_wypozyczonych_moto.size(); i++)
	{
		for (int j = 0; j < baza_motocykli.size(); j++)
		{
			if (porownaj_motocykle(lista_wypozyczonych_moto[i], baza_motocykli[j]))
				baza_motocykli[j].zmien_status(); //ustaw w bazie motocykli, ze ten motocykl jest wolny
		}
		lista_wypozyczonych_moto.erase(lista_wypozyczonych_moto.begin() + i - 1); //usuwanie znalezionego motocykla z listy wypozyczonych moto w danej firmie
	}
	//czyszczenie wypozyczonych moto w danej firmie
	/*baza_klientow_firma[iterator].lista_wypozyczonych_moto.erase(baza_klientow_firma[iterator].lista_wypozyczonych_moto.begin(), baza_klientow_firma[iterator].lista_wypozyczonych_moto.end()); */
}

void usun_ostatnio_dodana_firme(vector <unique_ptr<Firma>>& baza_klientow_firma, vector <Motocykl>& baza_motocykli)
{
	int iterator = baza_klientow_firma.size() - 1;
	cout << "Zostanie usunieta firma o nastepujacych danych:\n";
	baza_klientow_firma[iterator].get()->pokaz_dane();
	/*Firma *ptr = baza_klientow_firma[iterator].get();

	ptr->wyswietl_info();*/

	cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
	cin >> odp;

	if (odp == 1)
	{
		usuwanie_wypozyczonych_motocykli_z_firmy(baza_klientow_firma[iterator]->lista_wypozyczonych_moto, baza_motocykli);
		
		baza_klientow_firma.pop_back();
		cout << "\Firma zostala usunieta z bazy.\n";
	}
	else if (odp == 0)
	{
		cout << "Usuwanie zostalo anulowane.";
	}
}

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

void wypozycz_motocykl_firmie(vector <Motocykl>& baza_motocykli, vector <unique_ptr<Firma>>& baza_klientow_firma)
{
	wyswietl_baze_firm(baza_klientow_firma);

	int numer_firmy;
	cout << "Podaj numer firmy, ktorej chcesz wypozyczyc moto: ";
	cin >> numer_firmy;

	wyswietl_baze_motocykli(baza_motocykli);

	int numer_moto;
	cout << "Podaj numer motocykla, ktory chcesz wypozyczyc: ";
	cin >> numer_moto;

	cout << "\nZostanie wypozyczony motocykl o nastepujacych danych:\n";
	baza_motocykli[numer_moto - 1].wyswietl_info_o_moto();

	cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
	cin >> odp;

	if (odp == 1)
	{
		//zmien status motocykla w bazie motocykli
		baza_motocykli[numer_moto - 1].zmien_status();
		//dodaj motocykl z bazy motocykli do listy wypozyczonych moto w danej firmie
		baza_klientow_firma[numer_firmy - 1]->lista_wypozyczonych_moto.push_back(baza_motocykli[numer_moto - 1]);
	}
	else
	{
		cout << "Wypozyczanie zostalo anulowane.";
	}
}

//auto ros_wedlug_marki = [](const Motocykl & l, const Motocykl & r)  { return (l.marka < r.marka); } ->bool;

int main()
{
	vector <Motocykl> baza_motocykli;
	//vector <Firma> baza_klientow_firma;
	vector <unique_ptr<Firma>> baza_klientow_firma;
	vector <Osoba_fizyczna> baza_klientow_osoba_fizyczna;
	map<int, string> baza_pracownikow;
	//map<unique_ptr<int>, unique_ptr<string>> baza_pracownikow;

	//zanim zrobie obsluge bazy danych....
	//baza_motocykli.push_back(Motocykl("Honda", "CBR", 2005, 0.125, 0, 70.0));
	//baza_motocykli.push_back(Motocykl("Kawasaki", "Ninja", 2012, 0.3, 0, 100.0));
	//baza_motocykli.push_back(Motocykl("Ducati", "Panigale 959", 2018, 0.955, 0, 200.0));
	//...to pojdziemy na latwizne :D
	//baza_klientow_firma.push_back(Firma("PizzaHut",123123123));
	baza_klientow_firma.push_back(make_unique<Firma>("PizzaHut", 123123123));
	//baza_klientow_firma.push_back(Firma("Dominos",777777777));
	baza_klientow_firma.push_back(make_unique<Firma>("Dominos", 777777777));
	//baza_klientow_firma.push_back(Firma("RominaAndAlbano",444555444));
	baza_klientow_firma.push_back(make_unique<Firma>("RominaAndAlbano", 444555444));
	//baza_klientow_firma[1].wypozycz_motocykl(Motocykl("")
	//
	//auto Pair = baza_pracownikow.insert(make_pair(25,("Kasia","Kowalska", 3.500,(19,12,1999))));
	//pair<const int, Pracownik> item(25, ("Kasia", "Kowalska", 3.500, (19, 12, 1999)));
	baza_pracownikow.insert(make_pair(25, "Kowalska"));
	baza_pracownikow[53] = "Danielski";
	//baza_pracownikow.insert(make_pair(53, "Danielski"));
	baza_pracownikow.insert(make_pair(44, "Bogdaniec"));



	do
	{
		main_menu();

		switch (odp)
		{
		case 1: //operacje na bazie motocykli
		{
			
			do
			{		
				moto_base_menu();
				switch (odp)
				{
				case 1://wyœwietlanie bazy
				{
					wyswietl_baze_motocykli(baza_motocykli);
					//for_each(baza_motocykli.begin(), baza_motocykli.end(), wyswietl_baze_motocykli);
					
					odp = -1;
					break;
				}

				case 2://dodawanie motocykla
				{
					dodaj_motocykl_do_bazy(baza_motocykli);
					
					odp = -1;
					break;
				}

				case 3://usuwanie motocykla
				{
					do
					{
						delete_moto_menu();

						if (odp == 1) //usuwanie motocykla ostatnio dodanego
						{
							usun_ostatnio_dodany_motocykl(baza_motocykli);
								
							odp = -1;
						}
						else if (odp == 2) //usuwanie motocykla wedlug numeru
						{
							wyswietl_baze_motocykli(baza_motocykli);

							usun_motocykl_wedlug_numeru(baza_motocykli);

							odp = -1;
							
						}
						else if (odp == 0) //wroc do poprzedniego menu
						{
							break;
						}
						else //niepoprawny kod
						{
							cout << "Wpisales niepoprawny kod polecenia. Sprobuj jeszcze raz.\n";
							odp = -1;
						}
					} while (odp != 0);
					odp = -1;
					break;
				}
				case 4: //sortowanie bazy
				{
					cout << "1.Wedlug marki.\n2.Wedlug modelu.\n3.Wedlug rocznika.\n4.Wedlug pojemnosci.\n5.Wedlug ceny.\n";
					cin >> odp;

					if (odp == 1)//wedlug marki
					{
						cout << "1.Rosnaco.\n2.Malejaco.\n";
						cin >> odp;

						if (odp == 1)//rosnaco
						{
							sort(baza_motocykli.begin(), baza_motocykli.end(), [](const Motocykl & l, const Motocykl & r) { return (l.marka < r.marka); }); //uzyto wyrazenie lambda
							cout << "\nBaza zostala posortowana.\n";
						}
						else if (odp == 2)//malejaco
						{
							//sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_marki());
							sort(baza_motocykli.begin(), baza_motocykli.end(), greater<Motocykl>()); //sortuje malejaco
							cout << "\nBaza zostala posortowana.\n";
						}


						odp = -1;
					}
					else if (odp == 2)//wedlug modelu
					{
						cout << "1.Rosnaco.\n2.Malejaco.\n";
						cin >> odp;

						if (odp == 1)//rosnaco
						{
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::rosnaco_wedlug_modelu());
							cout << "\nBaza zostala posortowana.\n";
						}
						else if (odp == 2)//malejaco
						{
							//sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_marki());
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_modelu()); //sortuje malejaco
							cout << "\nBaza zostala posortowana.\n";
						}


						odp = -1;
					}
					else if (odp == 3)//wedlug rocznika
					{
						cout << "1.Rosnaco.\n2.Malejaco.\n";
						cin >> odp;

						if (odp == 1)//rosnaco
						{
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::rosnaco_wedlug_rocznika());
							cout << "\nBaza zostala posortowana.\n";
						}
						else if (odp == 2)//malejaco
						{
							//sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_marki());
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_rocznika()); //sortuje malejaco
							cout << "\nBaza zostala posortowana.\n";
						}


						odp = -1;
					}
					else if (odp == 4)//wedlug pojemnosci
					{
						cout << "1.Rosnaco.\n2.Malejaco.\n";
						cin >> odp;

						if (odp == 1)//rosnaco
						{
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::rosnaco_wedlug_pojemnosci());
							cout << "\nBaza zostala posortowana.\n";
						}
						else if (odp == 2)//malejaco
						{
							//sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_marki());
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_pojemnosci()); //sortuje malejaco
							cout << "\nBaza zostala posortowana.\n";
						}


						odp = -1;
					}
					else if (odp == 5)//wedlug ceny
					{
						cout << "1.Rosnaco.\n2.Malejaco.\n";
						cin >> odp;

						if (odp == 1)//rosnaco
						{
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::rosnaco_wedlug_ceny());
							cout << "\nBaza zostala posortowana.\n";
						}
						else if (odp == 2)//malejaco
						{
							//sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_marki());
							sort(baza_motocykli.begin(), baza_motocykli.end(), Motocykl::malejaco_wedlug_ceny()); //sortuje malejaco
							cout << "\nBaza zostala posortowana.\n";
						}


						odp = -1;
					}

					odp = -1;
					break;
				}
				case 5://zmien rekord w bazie
				{
					wyswietl_baze_motocykli(baza_motocykli);

					cout << "\nKtory rekord ma zostac zmieniony? Podaj numer porzadkowy: ";
					int numer;
					cin >> numer;

					string marka, model;
					int rocznik;
					float pojemnosc;
					bool czy_zarezerwowany;
					float cena;

					getchar();
					cout << "\nPodaj marke nowego motocykla: ";
					getline(cin, marka);
					cout << "\nPodaj model nowego motocykla: ";
					getline(cin, model);
					cout << "\nPodaj rocznik nowego motocykla: ";
					cin >> rocznik;
					cout << "\nPodaj pojemnosc nowego motocykla [w litrach]: ";
					cin >> pojemnosc;
					cout << "\nCzy nowy motocykl jest zarezerwowany?(0-nie,1-tak): ";
					cin >> czy_zarezerwowany;
					cout << "\nPodaj nowa cene rezerwacji za godzine [w PLN]: ";
					cin >> cena;

					cout << "\nZostanie zmieniony motocykl o nastepujacych danych:\n";
					baza_motocykli[numer - 1].wyswietl_info_o_moto();
					cout << "\nna nastepujace dane:\n";
					wyswietl_info_o_moto(marka, model, rocznik, pojemnosc, czy_zarezerwowany, cena);
					cout << "\nCzy kontynuowac? (0-nie,1-tak): ";
					cin >> odp;

					if (odp == 0)
					{
						cout << "\nZmienianie rekordu w bazie zostalo anulowane.\n";
					}
					else if (odp == 1)
					{
						replace(baza_motocykli.begin(), baza_motocykli.end(), baza_motocykli[numer - 1], Motocykl(marka, model, rocznik, pojemnosc, czy_zarezerwowany, cena));
						cout << "\nRekord w bazie zostal pomyslnie zmieniony.\n";
					}

					odp = -1;
					break;
				}
				case 6: //znajdz motocykl o podanych danych 
				{
					cout << "1.Wedlug marki, modelu i pojemnosci.\n*2.Wedlug marki i modelu.\n*3.Wedlug marki.\n*4.Wedlug marki, modelu, rocznika i pojemnosci.\n*5.Wedlug marki, modelu i ceny.\n*6.Wedlug marki, modelu, pojemnosci, rocznika i ceny.\n*7.Wedlug dostepnosci.\n*0.Wroc do poprzedniego menu.\n";
					cin >> odp;

					if (odp == 1)//wedlug marki, modelu i pojemnosci
					{
						string marka, model;
						float pojemnosc;

						getchar();
						cout << "Podaj marke motocykla: ";
						getline(cin, marka);
						cout << "Podaj model motocykla: ";
						getline(cin, model);
						cout << "Podaj pojemnosc motocykla: ";
						cin >> pojemnosc;

						int licznik = 0;

						for (int i = 0; i < baza_motocykli.size(); i++)
						{
							if (baza_motocykli[i].czy_moto_istnieje_marka_model_poj(marka, model, pojemnosc))
							{
								cout <<endl<< i + 1 << "\t";
								baza_motocykli[i].wyswietl_info_o_moto();
								cout << endl;

								licznik++;
							}
						}

						if (licznik == 0)
							cout << "\nNie ma w bazie motocykla o podanych danych.\n";
					}

					odp = -1;
					break;

				}
				case 7: //wyszukiwanie motocykli ponizej 100zl
				{
					vector<Motocykl>::iterator kraniec;
					kraniec = partition(baza_motocykli.begin(), baza_motocykli.end(), wyszukaj_ponizej_ceny); //dzieli na motocykle, dla ktorych warunek wyszukaj_ponizej_ceny jest true i na te, ktore dostaly false

					for (vector<Motocykl>::iterator it=baza_motocykli.begin(); it != kraniec; it++)
					{
						it->wyswietl_info_o_moto();
						cout << endl;
					}

					odp = -1;
					break;
				}
				case 8://podwyzsza wszystkie ceny motocykli o 50 zl
				{
					transform(baza_motocykli.begin(), baza_motocykli.end(), baza_motocykli.begin(), podwyzka_cen); //podwyzsza wyszstkie ceny o 50zl

					cout << "\nDuplikaty w bazie zostaly pomyslnie usuniete.\n";

					odp = -1;
					break;
				}
				case 9: //usuwa duplikaty
				{
					//1.sortowanie rosnace wedlug marki
					sort(baza_motocykli.begin(), baza_motocykli.end(), [](const Motocykl& l, const Motocykl& r) { return (l.marka < r.marka); });
					//2.unique
					auto last = unique(baza_motocykli.begin(), baza_motocykli.end()); //wyszukuje duplikaty i ustawia je na koniec wektora
					//3.usuwanie duplikatow
					baza_motocykli.erase(last, baza_motocykli.end());

					odp = -1;
					break;
				}

				}
			} while (odp != 0);
			odp = -1;
			break;
		}
		case 2: //operacje na bazie klientow
		{
			cout << "*1.Baza osob fizycznych.\n2.Baza firm.\n";
			cin >> odp;
			if (odp == 1) // baza osob fizycznych
			{

			}
			else if (odp == 2)//baza firm
			{
				do
				{
					cout << "\t\tCo chcesz zrobic z baza firm?\n1.Wyswietl baze.\n2.Dodaj firme.\n3.Usun firme.\n*4.Sortuj baze.\n*5.Zmien rekord w bazie\n*6.Wyszukaj firme.\n*7.Wypozycz motocykl firmie.\n*8.Zwroc motocykl.\n0.Wroc do poprzedniego menu.\n";
					cin >> odp;
					switch (odp)
					{
					case 1://wyswietl baze firm
					{
						wyswietl_baze_firm(baza_klientow_firma);
						odp = -1;
						break;
					}
					case 2: //dodaj firme
					{
						long regon;
						string nazwa;
						getchar();
						cout << "\nPodaj nazwe firmy: ";
						getline(cin, nazwa);
						cout << "Podaj REGON firmy: ";
						cin >> regon;

						baza_klientow_firma.push_back(make_unique<Firma>(nazwa, regon));

						odp = -1;
						break;
					}
					case 3://usuwanie firmy
					{
						do
						{
							cout << "\n1.Usun ostatnio dodana.\n2.Usun wedlug podanego numeru.\n0.Wroc do poprzedniego menu.\n";
							cin >> odp;

							if (odp == 1) //usuwanie firmy ostatnio dodanej
							{
								usun_ostatnio_dodana_firme(baza_klientow_firma,baza_motocykli);
								
								odp = -1;
							}
							else if (odp == 2) //usuwanie firmy wedlug numeru
							{
								wyswietl_baze_firm(baza_klientow_firma);

								//usun_firme_wedlug_numeru(baza_klientow_firma, baza_motocykli);

								odp = -1;
							}
							else if (odp == 0) //wroc do poprzedniego menu
							{
								break;
							}
							else //niepoprawny kod
							{
								cout << "Wpisales niepoprawny kod polecenia. Sprobuj jeszcze raz.\n";
								odp = -1;
							}
						} while (odp != 0);
						odp = -1;
						break;
					}
					case 7://wypozycz motocykl firmie
					{
						wypozycz_motocykl_firmie(baza_motocykli,baza_klientow_firma);

						odp = -1;
						break;
					}

					}

				} while (odp != 0);
					odp = -1;
			}
			break;
		}
		case 3: //operacje na bazie pracownikow
		{
			
			do
			{
				cout << "1.Wyswietl baze.\n2.Znajdz pracownika o podanym kluczu\n3.Zmien identyfikator pracownika.\n0.Wroc do poprzedniego menu.\n";
				cin >> odp;

				if(odp==1)//wyswietla baze pracownikow
				{
					for (auto it = baza_pracownikow.begin(); it!=baza_pracownikow.end();it++)
					{
						cout << (*it).first << "\t" << (*it).second << endl;
					}

					odp = -1;
				}
				else if (odp == 2)//znajduje pracownika o podanym id
				{
					int id;
					cout << "Podaj identyfikator pracownika: ";
					cin >> id;

					if (baza_pracownikow.find(id) != baza_pracownikow.end()) cout << "\nTo ID nalezy do pracowniku o nazwisku " << baza_pracownikow[id]<<endl<<endl;
					else cout << "\nNie ma pracownika o podanym ID."<<endl<<endl;

					odp = -1;
				}
				else if (odp == 3)//zmiana ID
				{
					//wyswietlanie bazy pracownikow
					for (auto it = baza_pracownikow.begin(); it != baza_pracownikow.end(); it++)
					{
						cout << (*it).first << "\t" << (*it).second << endl;
					}

					int old_id, new_id;
					cout << "Podaj identfikator do zmiany: ";
					cin >> old_id;
					cout << "Podaj nowy identyfikator: ";
					cin >> new_id;

					baza_pracownikow[old_id].swap(baza_pracownikow[new_id]);
					baza_pracownikow.erase(old_id);

					cout << "\nIdentyfikator pracownika zostal zmieniony.\n";

					odp = -1;
				}
				else if (odp == 0) //wroc do poprzedniego menu
				{
					break;
				}
				else //niepoprawny kod
				{
					cout << "Wpisales niepoprawny kod polecenia. Sprobuj jeszcze raz.\n";
					odp = -1;
				}

			} while (odp != 0);



			odp = -1;
			break;
		}
		case 5: //odczyt baz z pliku
		{
			cout << "\n1.Baze motocykli.\n*2.Baze klientow.\n*3.Baze pracownikow.\n";
			cin >> odp;

			switch (odp)
			{
				case 1:
				{
					//wywolanie funkcji ktora bedzie wczytywac dane z pliku
					wczytaj_baze_motocykli(baza_motocykli);

					odp = -1;
					break;
				}
			}
			odp = -1;
			break;
		}
		case 6: //zapis baz do pliku
		{
			cout << "\n1.Baze motocykli.\n*2.Baze klientow.\n*3.Baze pracownikow.\n";
			cin >> odp;

			switch (odp)
			{
			case 1:
			{
				//wywolanie funkcji ktora bedzie zapisywac dane do pliku
				zapisz_baze_motocykli(baza_motocykli);

				odp = -1;
				break;
			}
			}
			odp = -1;
			break;
		}
		}
	} while (odp != 0);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
