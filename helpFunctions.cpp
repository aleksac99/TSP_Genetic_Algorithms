#include "helpFunctions.h"


// Generator slucajnih brojeva u zeljenom opsegu
int rng(int a, int b)
{
	int rez = a + rand() % (b - a);
	return rez;
}

// Provera da li je neki grad ponovljen
bool ponovljen(std::string s, char c)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == c) return true;
	}
	return false;
}

// Mutacija
std::string mutiraniGenotip(std::string genotip, int brGr)
{
	while (true)
	{
		int g1 = rng(1, brGr);
		int g2 = rng(1, brGr);
		if (g1 != g2)
		{
			char temp = genotip[g1];
			genotip[g1] = genotip[g2];
			genotip[g2] = temp;
			break;
		}
	}
	return genotip;
}

// Kreiranje validnog genotipa jedinke
std::string kreirajGenotip(int brGr)
{
	std::string genotip = "0";
	while (true)
	{
		if (genotip.size() == brGr)
		{
			genotip += genotip[0];
			break;
		}
		int temp = rng(1, brGr);
		if (!ponovljen(genotip, (char)(temp + 48)))
		{
			genotip += (char)(temp + 48);
		}
	}
	return genotip;
}

// Racunanje vrednosti funkcije prilagodjenosti
int prilagodjenost(std::string genotip, std::vector<std::vector<int>> udaljenost)
{
	int f = 0;
	for (unsigned int i = 0; i < genotip.size() - 1; i++)
	{
		// -1 Ukoliko put iz jednog u drugi grad ne postoji
		if (udaljenost[genotip[i] - 48][genotip[i + 1] - 48] == -1)
			return INT_MAX;
		f += udaljenost[genotip[i] - 48][genotip[i + 1] - 48];
	}
	return f;
}

//Poredjenje prilagodjenosti dve jedinke
bool manjaPrilagodjenost(struct Jedinka j1, struct Jedinka j2)
{
	return j1.prilagodjenost < j2.prilagodjenost;
}