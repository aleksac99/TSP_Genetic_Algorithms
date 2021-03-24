#ifndef HELP
#define HELP

#define brGradova 7 // Broj gradova u test primeru
#define VELPOP 20 // Velicina populacije u test primeru
#define brGeneracija 15 // Broj generacija u test primeru
#include <string>
#include <vector>

// Model jedinke
struct Jedinka
{
	std::string genotip;
	int prilagodjenost;
};

int rng(int a, int b);

// Provera da li je neki grad ponovljen
bool ponovljen(std::string s, char c);

// Mutacija
std::string mutiraniGenotip(std::string genotip, int brGr);

// Kreiranje validnog genotipa jedinke
std::string kreirajGenotip(int brGr);

// Racunanje vrednosti funkcije prilagodjenosti
int prilagodjenost(std::string genotip, std::vector<std::vector<int>> udaljenost);

//Poredjenje prilagodjenosti dve jedinke
bool manjaPrilagodjenost(struct Jedinka j1, struct Jedinka j2);

#endif