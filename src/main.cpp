#include <iostream>
#include <string>
#include <BlackScholesPricer.h>
#include "american.h"
#include "barrier.h"
#include "lookback.h"
#include "MonteCarloPricer.h"
#include "european.h"
#include "underlying.h"
#include "replication.h"
#include "asian.h"
#include "digital.h"

int main() {
    //Demande en premier lieu si l'option est un call ou un put
    int isCallInt;
    std::cout<<"Est-ce un Call (1) ou Put (0) ? ";
    std::cin>>isCallInt;
    bool isCall = (isCallInt == 1); //On convertit en booléen le chiffre 0 ou 1 renvoyé par l'utilisateur

    //Demande à l'utilisateur les paramètres de l'option
    double strike, maturity;
    std::cout<<"Strike de l'option (ex : 110) ? ";
    std::cin>>strike;
    std::cout<<"Maturité de l'option en années (ex: 1.0 pour 1 an) ? ";
    std::cin>>maturity;

    //Demande à l'utilisateur des paramètres du sous-jacent
    double spot, vol, drift;
    std::cout<<"Spot (ex : 100) ? ";
    std::cin>>spot;
    std::cout<<"Volatilite (ex : 0.2) ? ";
    std::cin>>vol;
    std::cout<<"Taux sans risque (ex : 0.05) ? ";
    std::cin>>drift;
    underlying_asset underlying(spot, vol, drift);




    //Choix du type d'option
    std::string type;
    std::cout<<"Type d'option (rentrer la lettre correspondante parmi E=Europeenne, A=Americaine, B=Barriere, L=Lookback, S=Asiatique D=Digitale) ? ";
    std::cin>>type;


    Option* option = nullptr; //On initialise par un pointeur nul
    //On utilise le constructeur de l'objet
    if (type == "E" || type == "e") {
        option = new EuropeanOption(strike, maturity, isCall, &underlying);
    } else if (type == "A" || type == "a") {
        option = new AmericanOption(strike, maturity, isCall, &underlying);
    } else if (type == "B" || type == "b") {
        std::string BarrierType;
        double barrier;
        std::cout<<"Entrez le type de barrière en recopiant in extenso le nom parmi : UpAndOut, UpAndIn, DownAndOut, et DownAndIn : ";
        std::cin>>BarrierType;
        std::cout<<"Entrez le niveau de la barrière : ";
        std::cin>>barrier;
        option = new BarrierOption(strike, maturity, isCall, &underlying, BarrierType, barrier);
    } else if (type == "L" || type == "l") {
        option = new LookbackOption(strike, maturity, isCall, &underlying);
    } else if (type == "S" || type == "s") {
        option = new AsianOption(strike, maturity, isCall, &underlying);
    } else if (type == "D" || type == "d") {
        option = new DigitalOption(strike, maturity, isCall, &underlying);
    } else {
        std::cout<<"Type non reconnu, création d'une option européenne par défaut.";
        option = new EuropeanOption(strike, maturity, isCall, &underlying);
    }

    //Paramètres pour Monte Carlo pour les simulations
    int NumPaths, NumSteps;
    std::cout<<"Nombre de paths (Monte Carlo) ? ";
    std::cin>>NumPaths;
    std::cout<<"Nombre de pas (Monte Carlo) ? ";
    std::cin>>NumSteps;
    MonteCarloPricer pricer(NumPaths, NumSteps, drift);

    //Prix par méthode de Monte Carlo
    double prixMC = pricer.Price(*option, underlying);
    std::cout<< "Prix par méthode de Monte Carlo : "<< prixMC << std::endl;

    //Modèle de BlackScholes et stratégie de réplication pour les européennes
    if (type == "E" || type == "e") {
        BlackScholesPricer black_scholes_pricer(drift);
        double prix = black_scholes_pricer.price(*option, underlying);
        std::cout<<"Prix par méthode de Black-Scholes : " <<prix<<std::endl;

            //Paramètres pour la stratégie de répliction pour les simulations
        int NumSteps;
        int NumPaths=1; //Un seul chemin qu'on va générer pour faire notre réplication sur ce chemin
        std::cout<<"Nombre d'actualisations dans la stratégie de réplication ? ";
        std::cin>>NumSteps;

        //Stratégie de réplication
        std::cout<<"\nDebut strategie de replication\n";
        ReplicationStrategy replication(*option);
        replication.strategy(NumPaths, NumSteps, drift);

    }


    delete option; //On libère la mémoire
}

