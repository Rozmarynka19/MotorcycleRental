#include "funkcjeMenu.hpp"
#include <iostream>
#include <fstream>

using namespace std;


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
			string ma, mo; //marka, model
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
			rez = linia.compare("1") ? true : false;//konwersja stringa na bool
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
		catch (logic_error& error)
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

Motocykl& podwyzka_cen(Motocykl& moto)
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

void wyswietl_info_o_moto(const string& marka, const string& model, const int& rocznik, const float& pojemnosc, const bool& czy_zarezerwowany, const float& cena)
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
	baza_motocykli[numer - 1].wyswietl_info_o_moto();
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

bool porownaj_motocykle(Motocykl& a, Motocykl& b)
{
	if (((a.marka).compare(b.marka) == 0) && ((a.model).compare(b.model) == 0) && (a.pojemnosc == b.pojemnosc) && (a.rocznik == b.rocznik) && (a.czy_zarezerwowany == b.czy_zarezerwowany) && (a.cena == b.cena))
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