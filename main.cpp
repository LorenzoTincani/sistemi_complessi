#include "Building.h"
#include "Link.h"
#include <iostream>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
int main() //le modifiche vanno sus
{
    std::cout << "riga 9 \n";
    int const N = 30;                                //N è numero di nodi, N^2-N il numero di link possibili
    std::array<std::array<int, N>, N> adj_matrix{0}; //matrice di adiacenza, con int come pesi
    std::array<Building, N> nodes;
    double Total_potential = 0.0;
    int nofSorting = 0;
    int nofCentral = 0;
    int nofHouse = 0;
    std::random_device rd; //   seed
    std::default_random_engine gen(rd());
    //std::discrete_distribution<int> link_dist({4, 3, 2, 1}); // parametri tra 0 e 3, per tre link più link non esistente
    //dal link inesistente a quello che collega le centrali //Se non funziona è colpa di Tinca
    std::discrete_distribution<int> nodeType_dist({10, 3, 1});
    std::normal_distribution<double> needfluct_dist(0.0, 0.33); //distribuzione guassiana di fluttuazioni nella richiesta di energia delle case
    std::uniform_real_distribution<double> link_dist(0.0, 1.0); //distribuzione uniforme per distribuzione dei link, generato come proporzioni programma arcelli
    std::cout << "riga 24 \n";
    for (int k = 0; k < N; ++k) //settaggio dei nodi
    {
        int numtype = nodeType_dist(gen); //numtype = type of node
        if (numtype == 0)
        {
            double fluct = needfluct_dist(gen);
            nodes[k].SetNeed(7.2 + fluct); //consumo medio giornaliero di una famiglia media in kW/h
            //std::cout<<"house " <<nodes[k].GetNeed()<<std::endl;
            nofHouse++;
        }
        else if (numtype == 1)
        {
            nodes[k].SetType(BuildingType::S);
            nofSorting++;

            //std::cout<<"sorting "<<nodes[k].GetNeed()<<std::endl;
        }

        else
        {
            double entrypotcentral = 100; //da aggiustare
            nodes[k].SetType(BuildingType::C);
            // std::cout<<"central "<<nodes[k].GetNeed()<<std::endl;
            nodes[k].SetEntryPotential(entrypotcentral); //da aggiustare
            Total_potential += entrypotcentral;
            nofCentral++;
        }
    }
    std::cout << "riga 59 \n";
    int j = 0; //j è fuori per poter calcolare solo il triangolo superiore della matrice dato che è simmetrica
    std::cout<<"nofcentral: "<<nofCentral<<std::endl;
    std::cout<<"nofHouse: "<<nofHouse<<std::endl;
    std::cout<<"nofSorting: "<<nofSorting<<std::endl;
    for (int i = 0; i < N; ++i)
    {
        BuildingType node_i = nodes[i].GetType();

        //DA GENERARE MATRICE DI ADIACENZA, CONTROLLANDO LA NATURA DEI VARI NODI.
        for (j; j < N; ++j)
        {
            double rnd = link_dist(gen); //generazione variabile uniforme della probabilità che avvenga link
            BuildingType node_j = nodes[j].GetType();
            if (i == j)
            {
                adj_matrix[i][j] = 0;
            }
            else
            {
                if (node_i == BuildingType::H && node_j == BuildingType::H)
                {                    //casa-casa
                    if (rnd <= 0.05) //si suppone che, su 100 case, una casa sia collegata con altre 5.
                    {
                        adj_matrix[i][j] = 1; //link small
                    }
                
                }
                else if (node_i == BuildingType::H && node_j == BuildingType::S)
                {                                //casa-smistamento
                    if (rnd <= (1 / nofSorting)) //si suppone che la probabilità di avere questo link sia 1/# smistamento
                    {
                        adj_matrix[i][j] = 1; //Sempre 1 perchè l'energia che confluisce è sempre la medesima
                    } //link medium
                
                }
                else if (node_i == BuildingType::S && node_j == BuildingType::S)
                { //smistamento-smistamento
                    if (rnd <= 0.01)
                    {
                        adj_matrix[i][j] = 2;
                    }
                
                }
                else
                { //smistamento- centrale
                    bool p = false;
                     float probCentral = 1 / nofCentral;
                    double z=1;
                   while(p==false){

                        double rn= link_dist(gen);
                        if (z<= probCentral)
                       {
                            adj_matrix[i][j] = 3;
                            p = true;
                        }
                        z=z-rn;
                    
                 }
                }
            }
        }
        j = j - N;
        j++;
    }
    std::cout << "riga 124 \n";
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            if (adj_matrix[i][k] == 0)
            {
                printf("\033[33m0");
            }
            else if (adj_matrix[i][k] == 1)
            {
                //std::cout << "       ";
                printf("\033[31m1");
            }
            else if (adj_matrix[i][k] == 2)
            {
                //std::cout << "       ";
                printf("\033[32m2");
            }
            else if (adj_matrix[i][k] == 3)
            {
                // std::cout << "       ";
                printf("\033[36m3");
            }
        }
        std::cout << std::endl;
    }
}
