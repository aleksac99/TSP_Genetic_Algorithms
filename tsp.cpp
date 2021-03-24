#include "tsp.h"


//Resavanje problema trgovackog putnika
void TSP(std::vector<std::vector<int>> udaljenost, int N, int brGen, int brGr, std::vector<std::string> gradovi)
{
    // Ispis medjurezultata
    int flag;
    std::cout << "Unesi 1 za ispisivanje medjurezultata: ";
    std::cin >> flag;

    // Broj generacije
    int gen = 1;
    // Broj generacija do zavrsetka 
    int brojGeneracija = brGen;

    std::vector<struct Jedinka> populacija; //Vektor populacije
    struct Jedinka temp;

    struct Jedinka najlosija; //Najlosija jedinka

    // Kreiranje inicijalne populacije
    for (int i = 0; i < N; i++) {
        temp.setGenotip(kreirajGenotip(brGr));
        temp.setPrilagodjenost(prilagodjenost(temp.getGenotip(), udaljenost));
        populacija.push_back(temp);
    }

    std::cout << "\nInicijalna populacija: " << std::endl
        << "GENOTIP    PRILAGODJENOST\n";
    for (int i = 0; i < N; i++)
        std::cout << populacija[i].getGenotip() << "   "
        << populacija[i].getPrilagodjenost() << std::endl;
    std::cout << "\n";

    struct Jedinka najJedinka = populacija[0]; //Najbolja jedinka

     // Selekcija i mutacija
    while (gen <= brojGeneracija) {
        sort(populacija.begin(), populacija.end(), manjaPrilagodjenost); // Sortiranje po prilagodjenosti

        if (najJedinka.getPrilagodjenost() > populacija[0].getPrilagodjenost())
            najJedinka = populacija[0]; //Izbor najbolje jedinke u trenutnoj populaciji

        if (najlosija.getPrilagodjenost() < populacija[populacija.size() - 1].getPrilagodjenost())
            najlosija = populacija[populacija.size() - 1]; //Izbor najlosije jedinke

        // Kreiranje nove populacije
        std::vector<struct Jedinka> novaPopulacija;

        //Elitizam
        novaPopulacija.push_back(populacija[0]);

        for (int i = 1; i < N; i++) {
            struct Jedinka j1 = populacija[i];

            while (true) {

                std::string novi_g = mutiraniGenotip(j1.getGenotip(), brGr); //Mutacija jedinke
                struct Jedinka novi_genotip;
                novi_genotip.setGenotip(novi_g);
                novi_genotip.setPrilagodjenost(prilagodjenost(novi_genotip.getGenotip(), udaljenost));

                if (novi_genotip.getPrilagodjenost() <= populacija[i].getPrilagodjenost()) {
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

        if (flag == 1)
        {
            // Ispis generacije
            std::cout << "\nGeneracija " << gen << " \n";
            std::cout << "GENOTIP    PRILAGODJENOST\n";

            for (int i = 0; i < N; i++)
                std::cout << populacija[i].getGenotip() << "   "
                << populacija[i].getPrilagodjenost() << std::endl;
        }
        gen++;
    }

    // Ispis rezultata
    std::cout << "\n------------------------\n";
    std::cout << "\n \nNAJBOLJA JEDINKA\n";
    std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najJedinka.getGenotip() << "   "
        << najJedinka.getPrilagodjenost() << std::endl;
    std::cout << "NAJBOLJI PUT\n";
    for (int i = 0; i <= brGr; i++)
    {
        std::cout << ((i == 0) ? "" : " - ");
        std::cout << gradovi[najJedinka.getGenotip()[i] - 48];
    }
    std::cout << "\n \nNAJLOSIJA JEDINKA\n";
    std::cout << "GENOTIP    PRILAGODJENOST\n"; std::cout << najlosija.getGenotip() << "   "
        << najlosija.getPrilagodjenost() << std::endl;

}