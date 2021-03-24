#include "tsp.h"


//Resavanje problema trgovackog putnika
void TSP(std::vector<std::vector<int>> udaljenost, int N, int brGen, int brGr, std::vector<std::string> gradovi)
{

    // Broj generacije
    int gen = 1;
    // Broj generacija do zavrsetka 
    int brojGeneracija = brGen;

    std::vector<struct Jedinka> populacija; //Vektor populacije
    struct Jedinka temp;

    struct Jedinka najlosija; //Najlosija jedinka

    // Kreiranje inicijalne populacije
    for (int i = 0; i < N; i++) {
        temp.genotip = kreirajGenotip(brGr);
        temp.prilagodjenost = prilagodjenost(temp.genotip, udaljenost);
        populacija.push_back(temp);
    }

    std::cout << "\nInicijalna populacija: " << std::endl
        << "GENOTIP    PRILAGODJENOST\n";
    for (int i = 0; i < N; i++)
        std::cout << populacija[i].genotip << "   "
        << populacija[i].prilagodjenost << std::endl;
    std::cout << "\n";

    struct Jedinka najJedinka = populacija[0]; //Najbolja jedinka

     // Selekcija i mutacija
    while (gen <= brojGeneracija) {
        sort(populacija.begin(), populacija.end(), manjaPrilagodjenost); // Sortiranje po prilagodjenosti

        if (najJedinka.prilagodjenost > populacija[0].prilagodjenost)
            najJedinka = populacija[0]; //Izbor najbolje jedinke u trenutnoj populaciji

        if (najlosija.prilagodjenost < populacija[populacija.size() - 1].prilagodjenost)
            najlosija = populacija[populacija.size() - 1]; //Izbor najlosije jedinke

        // Kreiranje nove populacije
        std::vector<struct Jedinka> novaPopulacija;

        //Elitizam
        novaPopulacija.push_back(populacija[0]);

        for (int i = 1; i < N; i++) {
            struct Jedinka j1 = populacija[i];

            while (true) {

                std::string novi_g = mutiraniGenotip(j1.genotip, brGr); //Mutacija jedinke
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
            << populacija[i].prilagodjenost << std::endl;
        gen++;
    }

    // Ispis rezultata
    std::cout << "\n------------------------\n";
    std::cout << "\n \nNAJBOLJA JEDINKA\n";
    std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najJedinka.genotip << "   "
        << najJedinka.prilagodjenost << std::endl;
    std::cout << "NAJBOLJI PUT\n";
    for (int i = 0; i <= brGr; i++)
    {
        std::cout << ((i == 0) ? "" : " - ");
        std::cout << gradovi[najJedinka.genotip[i] - 48];
    }
    std::cout << "\n \nNAJLOSIJA JEDINKA\n";
    std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najlosija.genotip << "   "
        << najlosija.prilagodjenost << std::endl;

}