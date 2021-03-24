#include <ctime>
#include "tsp.h"
#include "helpFunctions.h"
//#include <iostream>


int main()
{
    srand(time(0));
    int k = -1; 
    while (k != 0 && k != 1)
    {
        std::cout << "Unesi 0 za podrazumevani primer, 1 za svoj primer:\n";
        std::cin >> k;
    }

    if (k == 1)
    {
        int brGr;
        int N;
        int brGen;

        std::cout << "Unesi broj gradova: ";
        std::cin >> brGr;

        std::vector<std::string> gradovi;
        std::vector<std::vector<int>> udaljenost(brGr);
        
        std::cout << "Unesi imena gradova\n";
        for (int i = 0; i < brGr; i++)
        {
            std::string tmp;
            std::cin >> tmp;
            gradovi.push_back(tmp);
        }
        std::cout << "Unesi udaljenosti izmedju gradova:\n";
        for (int i = 0; i < brGr; i++)
        {
            udaljenost[i] = std::vector<int>(brGr);
            for (int j = 0; j < brGr; j++)
            {
                if (i == j) udaljenost[i][j] = 0;
                else
                {
                    std::cout << gradovi[i] << " - " << gradovi[j] << std::endl;
                    std::cin >> udaljenost[i][j];
                }
            }
        }
        std::cout << "Unesi velicinu populacije: ";
        std::cin >> N;
        std::cout << "Unesi broj generacija: ";
        std::cin >> brGen;

        TSP(udaljenost, N, brGen, brGr, gradovi);

    }
    else if (k == 0)
    {
        std::vector<std::string> gradovi = { "Beograd", "Berlin", "London", "Madrid", "Moskva", "Pariz", "Rim" };

        std::vector<std::vector<int>> inic_udaljenost = {
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