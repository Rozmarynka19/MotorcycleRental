#include "Data.hpp"
#include <iostream>

using namespace std;

Data::Data(int d = 0, int m = 0, int r = 0)
{
	dzien = d;
	miesiac = m;
	rok = r;
}

void Data::pokaz() const
{
	cout << dzien << "/" << miesiac << "/" << rok << endl;
}