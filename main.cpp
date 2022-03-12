#include <iostream>
#include <array>
#include <random>
enum class BuildingType : char //underlying type int: 0 per H, 1 per S, 2 per C
{
    H, //houses
    S, //sorting
    C  //central
};     //Struttura gerarchica edifici

enum class LinkType : char //underling type int : 0 per null, 1 per small, etc
{

    N, //null
    S, //small
    M, //medium
    B  //big

};  //Struttura gerarchica collegamenti

class Building
{
private:
    BuildingType type_ = BuildingType::H;
    double need_ = 0.0;
    double entry_potential_ = 0.0; //settato a zero, perchè definito dalla dinamica

public:
    Building(BuildingType type, double need, double entry_potential) : type_{type}, need_{need}, entry_potential_{entry_potential}
    {
    }
    Building() = default; //costruttore di default insieme alle condizioni uguali nel private
    BuildingType GetType() const
    {
        return type_;
    };
    double GetNeed() const
    {
        return need_;
    };
    double GetEntryPotential() const
    {

        return entry_potential_;
    };
    void SetEntryPotential(double entry_potential)
    {
        entry_potential_ = entry_potential;
    }
    void SetNeed(double need)
    {
        need_ = need;
    }
    void SetType(BuildingType type)
    {
        type_ = type;
    }
};

class Link
{
private:
    LinkType type_;
    static const int basic_load = 3; //carico massimo del link più piccolo
    int max_load_ = basic_load * static_cast<int>(type_);
    int load_;

public:
    Link(LinkType type, int max_load, int load) : type_{type}, max_load_{max_load}, load_{load} {}

    LinkType GetType() const
    {
        return type_;
    };
    int GetMaxLoad() const
    {
        return max_load_;
    };
    int GetLoad() const
    {

        return load_;
    };

    void SetLoad(int newload)
    {
        load_ = newload;
    };
};

int main()
{
    int const N = 100;                               //N è numero di nodi, N^2-N il numero di link possibili
    std::array<std::array<int, N>, N> adj_matrix{0}; //matrice di adiacenza, con int come pesi
    std::array<Building, N> nodes;
    double Total_potential=0.0;

    std::random_device rd; //   seed
    std::default_random_engine gen(rd());
    //std::discrete_distribution<int> link_dist({4, 3, 2, 1}); // parametri tra 0 e 3, per tre link più link non esistente
    //dal link inesistente a quello che collega le centrali //Se non funziona è colpa di Tinca
    std::discrete_distribution<int> nodeType_dist({10, 3, 1});
    std::normal_distribution<double> needfluct_dist(0.0, 0.33); //distribuzione guassiana di fluttuazioni nella richiesta di energia delle case

    for (int k = 0; k < N; ++k) //settaggio dei nodi
    {
        int numtype = nodeType_dist(gen);
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
            nodes[k].SetEntryPotential(entrypotcentral) ;  //da aggiustare
            Total_potential+= entrypotcentral;
        }
    }

    for (int i = 0; i < N; ++i)
    {

//DA GENERARE MATRICE DI ADIACENZA, CONTROLLANDO LA NATURA DEI VARI NODI. 
        /*for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                adj_matrix[i][j] = 0;
            }
            else
            {
                if (nodes[i].GetType()==)
                { //casa-casa
                    adj_matrix[i][j] = 
                }
                else if ()
                { //casa-smistamento
                    adj_matrix[i][j] = 
                }
                else if ()
                { //smistamento-smistamento
                }
                else
                { //smistamento- centrale
                    adj_matrix[i][j] = 
                }
            }
        }*/
    }
}

//COMPITO: genera la natura dei nodi, inserendoli all'interno di un contenitore (array/ vec)
//in modo da indicizzarli e facilitare la caratterizzazione del link che li connette




