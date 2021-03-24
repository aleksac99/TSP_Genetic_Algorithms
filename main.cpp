#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include<ctime>

using namespace std;

#define brGradova 7 // Broj gradova u test primeru
#define VELPOP 20 // Velicina populacije u test primeru
#define brGeneracija 15 // Broj generacija u test primeru

// Model jedinke
struct Jedinka
{
	string genotip;
	int prilagodjenost;
};

// Generator slucajnih brojeva u zeljenom opsegu
int rng(int a, int b)
{
	int rez = a + rand() % (b - a);
	return rez;
}

// Provera da li je neki grad ponovljen
bool ponovljen(string s, char c)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == c) return true;
	}
	return false;
}

// Mutacija
string mutiraniGenotip(string genotip, int brGr)
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
string kreirajGenotip(int brGr)
{
	string genotip = "0";
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
int prilagodjenost(string genotip, vector<vector<int>> udaljenost)
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

//Resavanje problema trgovackog putnika
void TSP(vector<vector<int>> udaljenost, int N, int brGen, int brGr, vector<string> gradovi)
{

        // Broj generacije
        int gen = 1;
        // Broj generacija do zavrsetka 
        int brojGeneracija = brGen;

        vector<struct Jedinka> populacija; //Vektor populacije
        struct Jedinka temp;

        struct Jedinka najlosija; //Najlosija jedinka

        // Kreiranje inicijalne populacije
        for (int i = 0; i < N; i++) {
            temp.genotip = kreirajGenotip(brGr);
            temp.prilagodjenost = prilagodjenost(temp.genotip, udaljenost);
            populacija.push_back(temp);
        }

        std::cout << "\nInicijalna populacija: " << endl
            << "GENOTIP    PRILAGODJENOST\n";
        for (int i = 0; i < N; i++)
            std::cout << populacija[i].genotip << "   "
            << populacija[i].prilagodjenost << endl;
       std::cout << "\n";

       struct Jedinka najJedinka = populacija[0]; //Najbolja jedinka

        // Selekcija i mutacija
        while (gen <= brojGeneracija) {
            sort(populacija.begin(), populacija.end(), manjaPrilagodjenost); // Sortiranje po prilagodjenosti

            if (najJedinka.prilagodjenost > populacija[0].prilagodjenost)
                najJedinka = populacija[0]; //Izbor najbolje jedinke u trenutnoj populaciji

            if(najlosija.prilagodjenost< populacija[populacija.size() - 1].prilagodjenost)
                najlosija = populacija[populacija.size()-1]; //Izbor najlosije jedinke

            // Kreiranje nove populacije
            vector<struct Jedinka> novaPopulacija;

            //Elitizam
            novaPopulacija.push_back(populacija[0]);

            for (int i = 1; i < N; i++) {
                struct Jedinka j1 = populacija[i];

                while (true) {

                    string novi_g = mutiraniGenotip(j1.genotip, brGr); //Mutacija jedinke
                    struct Jedinka novi_genotip;
                    novi_genotip.genotip = novi_g;
                    novi_genotip.prilagodjenost = prilagodjenost(novi_genotip.genotip, udaljenost);

                    if (novi_genotip.prilagodjenost <= populacija[i].prilagodjenost) {
                        novaPopulacija.push_back(novi_genotip);
                        break;
                    }
                    else {

                        // Ubacivanje mutirane jedinke u populaciju iako je losija od nemutirane 
                        double verovatnoca = ((double)rand()) / RAND_MAX;
                        if (verovatnoca < 0.1) {
                            novaPopulacija.push_back(novi_genotip);
                            break;
                        }
                    }
                }
            }
            populacija = novaPopulacija;

            // Ispis generacije
            std::cout << "\nGeneracija " << gen << " \n";
            std::cout << "GENOTIP    PRILAGODJENOST\n";

            for (int i = 0; i < N; i++)
                std::cout << populacija[i].genotip << "   "
                << populacija[i].prilagodjenost << endl;
            gen++;
        }

        // Ispis rezultata
        std::cout << "\n------------------------\n";
        std::cout << "\n \nNAJBOLJA JEDINKA\n";
        std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najJedinka.genotip << "   "
            << najJedinka.prilagodjenost << endl;
        std::cout << "NAJBOLJI PUT\n";
        for (int i = 0; i <= brGr; i++)
        {
            std::cout << ((i == 0) ? "" : " - ");
            std::cout << gradovi[najJedinka.genotip[i] - 48];
        }
        std::cout << "\n \nNAJLOSIJA JEDINKA\n";
        std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najlosija.genotip << "   "
            << najlosija.prilagodjenost << endl;
        
}

int main()
{
    srand(time(0));
    int k = -1; 
    while (k != 0 && k != 1)
    {
        std::cout << "Unesi 0 za podrazumevani primer, 1 za svoj primer:\n";
        cin >> k;
    }

    if (k == 1)
    {
        int brGr;
        int N;
        int brGen;

        std::cout << "Unesi broj gradova: ";
        cin >> brGr;

        vector<string> gradovi;
        vector<vector<int>> udaljenost(brGr);
        
        std::cout << "Unesi imena gradova\n";
        for (int i = 0; i < brGr; i++)
        {
            string tmp;
            cin >> tmp;
            gradovi.push_back(tmp);
        }
        std::cout << "Unesi udaljenosti izmedju gradova:\n";
        for (int i = 0; i < brGr; i++)
        {
            udaljenost[i] = vector<int>(brGr);
            for (int j = 0; j < brGr; j++)
            {
                if (i == j) udaljenost[i][j] = 0;
                else
                {
                    std::cout << gradovi[i] << " - " << gradovi[j] << endl;
                    cin >> udaljenost[i][j];
                }
            }
        }
        std::cout << "Unesi velicinu populacije: ";
        cin >> N;
        std::cout << "Unesi broj generacija: ";
        cin >> brGen;

        TSP(udaljenost, N, brGen, brGr, gradovi);

    }
    else if (k == 0)
    {
        vector<string> gradovi = { "Beograd", "Berlin", "London", "Madrid", "Moskva", "Pariz", "Rim" };

        vector<vector<int>> inic_udaljenost = {
                         { 0,1000, 1689, 2027, 1711, 1446, 722 },
                         { 1000, 0, 930, 1868, 1608, 877, 1182 },
                         { 1689, 930, 0, 1263, 2498, 340, 1431 },
                         { 2027, 1868, 1263, 0, 3438, 1053, 1361 },
                         { 1711, 1608, 2498, 3438, 0, 2485, 2374 },
                         { 1446, 877, 340, 1053, 2485, 0, 1106 },
                         { 722, 1182, 1431, 1361, 2374, 1106, 0 } };
        TSP(inic_udaljenost, VELPOP, brGeneracija, brGradova, gradovi);
    }
	return 0;
}