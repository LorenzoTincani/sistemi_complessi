#include "Building.h"
#include "Link.h"
#include <iostream>
#include <array>
#include <random>
int main() //le modifiche vanno sus
{
    int const N = 1000;                              //N è numero di nodi, N^2-N il numero di link possibili
    std::array<std::array<int, N>, N> adj_matrix{0}; //matrice di adiacenza, con int come pesi
    std::array<Building, N> nodes;
    double Total_potential = 0.0;

    std::random_device rd; //   seed
    std::default_random_engine gen(rd());
    //std::discrete_distribution<int> link_dist({4, 3, 2, 1}); // parametri tra 0 e 3, per tre link più link non esistente
    //dal link inesistente a quello che collega le centrali //Se non funziona è colpa di Tinca
    std::discrete_distribution<int> nodeType_dist({10, 3, 1});
    std::normal_distribution<double> needfluct_dist(0.0, 0.33); //distribuzione guassiana di fluttuazioni nella richiesta di energia delle case
    std::uniform_real_distribution<double> link_dist(0.0, 1.0); //distribuzione uniforme per distribuzione dei link, generato come proporzioni programma arcelli

    for (int k = 0; k < N; ++k) //settaggio dei nodi
    {
        int numtype = nodeType_dist(gen); //numtype = type of node
        if (numtype == 0)
        {
            double fluct = needfluct_dist(gen);
            nodes[k].SetNeed(7.2 + fluct); //consumo medio giornaliero di una famiglia media in kW/h
            //std::cout<<"house " <<nodes[k].GetNeed()<<std::endl;
        }
        else if (numtype == 1)
        {
            nodes[k].SetType(BuildingType::S);
            //std::cout<<"sorting "<<nodes[k].GetNeed()<<std::endl;
        }

        else
        {
            double entrypotcentral = 100; //da aggiustare
            nodes[k].SetType(BuildingType::C);
            // std::cout<<"central "<<nodes[k].GetNeed()<<std::endl;
            nodes[k].SetEntryPotential(entrypotcentral); //da aggiustare
            Total_potential += entrypotcentral;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        BuildingType node_i = nodes[i].GetType();

        //DA GENERARE MATRICE DI ADIACENZA, CONTROLLANDO LA NATURA DEI VARI NODI.
        for (int j = 0; j < N; ++j)
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
                { //casa-casa
                    if (rnd <= 10)
                    {
                        adj_matrix[i][j] = 0;
                    }
                    else
                    {
                        adj_matrix[i][j] = 9;
                    }
                }
                else if (node_i == BuildingType::H && node_j == BuildingType::S)
                { //casa-smistamento
                    if (rnd <=10)
                    {
                        adj_matrix[i][j] = 0;
                    }
                    else
                    {
                        adj_matrix[i][j] = 9;
                    }
                }
                else if (node_i == BuildingType::S && node_j == BuildingType::S)
                { //smistamento-smistamento
                    if (rnd <=10)
                    {
                        adj_matrix[i][j] = 0;
                    }
                    else
                    {
                        adj_matrix[i][j] = 9;
                    }
                }
                else
                { //smistamento- centrale
                    if (rnd <=10)
                    {
                        adj_matrix[i][j] = 0;
                    }
                    else
                    {
                        adj_matrix[i][j] = 9;
                    }
                }
            }
        }
    }
}

//COMPITO: genera la natura dei nodi, inserendoli all'interno di un contenitore (array/ vec)
//in modo da indicizzarli e facilitare la caratterizzazione del link che li connette
