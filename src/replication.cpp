#include "replication.h"

#include <BlackScholesPricer.h>
#include <european.h>
#include <iostream>
#include <iomanip>

#include <cmath>
#include "option.h"
#include "underlying.h"
#include "MonteCarloPricer.h"
#include <vector>
#include "norm.h"

//Constructeur:
ReplicationStrategy::ReplicationStrategy(Option& option): option(option) {}

//Méthode pour calculer le temps qu'il reste avant la maturité de l'option
double ReplicationStrategy::get_timeToMaturity(double currentTime) {
    return option.get_maturity() - currentTime;
}

//Méthode pour calculer le delta, en utlisant la formule N(d1) pour les calls et N(d1)-1 pour les puts, en utilisant le code de norm pour la fonction de répartition de la loi N(0, 1)
double ReplicationStrategy::delta(double spotprice, double riskfreerate, double currentTime) {
    double sigma=option.get_underlying()->get_volatility();
    double T=get_timeToMaturity(currentTime);
    if (T <= 0) return 0.0; //On renvoie 0 si l'option est déjà à maturité
    double numerator=log(spotprice/option.get_strike())+(riskfreerate+sigma*sigma*0.5)*T;
    double denominator=sigma*sqrt(T);
    double d1=numerator/denominator;
    Norm normal;
    if (option.get_isCall()) {
        return normal.normcdf(d1);}
    else {return normal.normcdf(d1)-1;
    }
}


//Méthode pour calculer la position en actifs sans risque dans le portefeuille pour les européennes (par la formule de BSM)
double ReplicationStrategy::calculateBondPosition(double optionprice, double spotprice, double riskfreerate, double currentTime) {
    double delta = this->delta(spotprice, riskfreerate, currentTime);
    return  optionprice-delta*spotprice; //On retourne à ajuster en bonds à partir du delta calculé
}

//Méthode pour implémenter la stratégie de réplication pour les européennes
void ReplicationStrategy::strategy(int NumPaths, int NumSteps, double RiskFreeRate) {

    double Maturity = option.get_maturity();
    double DeltaT = Maturity/ NumSteps; //Calculer le pas de temps pour chaque étape
    double CurrentTime = 0.0; //on initialise le temps initial à t=0

    //On va garder l'historique des prix de l'option et de la valeur du portefeuille pour comparer et vérifier qu'il y a réplication
    std::vector<double> historiqueprixoption(NumSteps, 0.0);
    std::vector<double> historiqueportfolio(NumSteps, 0.0);

    //On initialise le pricer pour pricer l'option à chaque étape
    MonteCarloPricer pricer(NumPaths, NumSteps, RiskFreeRate);
    BlackScholesPricer black_scholes_pricer(RiskFreeRate);

    //On génère des chemins de prix, et on garde ici (arbitrairement) le premier chemin, pour tester notre stratégie sur un chemin de prix
    std::vector<std::vector<double>> paths = pricer.GeneratePricePaths(*option.get_underlying(), option);
    std::vector<double> path=paths[0];


    //On initialise la valeur du portefeuille à 0
    double PortfolioValue = 0.0;

    for (int i=0; i<NumSteps-1; i++) {
        CurrentTime = i * DeltaT; //on regarde le temps auquel on est actuellement

        //La classe Option étant abstraite, on crée dynamiquement une nouvelle EuropeanOption en copiant 'option' et la stocke dans 'subOption'
        Option* subOption=new EuropeanOption(dynamic_cast<EuropeanOption&>(option));


        //On utilise les setters pour mettre à jour la valeur de la maturité et du prix spot
        subOption->set_maturity(get_timeToMaturity(CurrentTime));
        subOption->set_spot(path[i]);

        //On price l'option, puis calcule le delta et la position en actifs sans risques
        double optionPrice = black_scholes_pricer.price(*subOption, *option.get_underlying());
        double deltaValue = this->delta(path[i], RiskFreeRate, CurrentTime);
        double bondPosition = calculateBondPosition(optionPrice, path[i], RiskFreeRate, CurrentTime);

        //On calcule la valeur du portefeuille, en actualisant dans le futur la valeur de l'actif sans risque pour refléter son rendement
        PortfolioValue = deltaValue * path[i] + bondPosition * std::exp(RiskFreeRate * (Maturity - CurrentTime));

        //Enregistrement dans l'historique
        historiqueprixoption[i] = optionPrice;
        historiqueportfolio[i] = PortfolioValue;

    //On print au fur et à mesure les informations de la stratégie de réplication pour l'utilisateur
        std::cout <<std::fixed << std::setprecision(2); //On affiche uniquement 2 chiffres après la virgule pour des raisons de lisibilité
        std::cout<<"\nPériode "<<i<<" :"<< "\nPrix action : " << path[i]<< "\nPrix option : "<< optionPrice<<"\nDelta : "<<deltaValue<<"\nObligations : "<<bondPosition<<"\nValeur totale du portefeuille : "<<PortfolioValue<<std::endl;
    }

    //On print également les historiques sous formes de listes Python, pour pouvoir les copier coller dans un programme python et utiliser matplotlib.pyplot pour tracer
    std::cout << "Périodes : [";
    for (int i = 0; i < NumSteps - 1; i++) {
        std::cout << i;
        if (i < NumSteps - 1) std::cout << ", "; // Ajout de virgules entre les éléments
    }
    std::cout << "]\n";

    std::cout << "Prix Option : [";
    for (int i = 0; i < NumSteps - 1; i++) {
        std::cout << historiqueprixoption[i];
        if (i < NumSteps - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    std::cout << "Valeur Portefeuille : [";
    for (int i = 0; i < NumSteps - 1; i++) {
        std::cout << historiqueportfolio[i];
        if (i < NumSteps - 1) std::cout << ", ";
    }
    std::cout << "]\n";

}


