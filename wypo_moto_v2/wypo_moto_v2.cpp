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

#include "Motocykl.hpp"
#include "Data.hpp"
#include "Klient.hpp"
#include "OsobaFizyczna.hpp"
#include "Firma.hpp"
#include "Pracownik.hpp"
#include "funkcjeMenu.hpp"

using namespace std;

int odp;

int main()
{
	vector <Motocykl> baza_motocykli;
	//vector <Firma> baza_klientow_firma;
	vector <unique_ptr<Firma>> baza_klientow_firma;
	vector <OsobaFizyczna> baza_klientow_osoba_fizyczna;
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
