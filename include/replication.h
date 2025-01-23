#pragma once
#include "option.h"


//Classe pour impléementer la stratégie de réplication grâce au portefeuille de réplication
class ReplicationStrategy {
public:
    double UnderlyingAmount{}; //Proportion de sous jacents dans le portefeuille sans risque
    double BondAmount{}; //Proportion en actifs sans risque (ici des bonds à taux sans risque)
    double PortfolioValue{};
    Option& option;

    //Constructeur:
    ReplicationStrategy(Option& option);

    //Méthodes pour calculer à chaque instant le delta, la position en bonds à ajuster et le temps qu'il reste avant maturité
    double delta(double SpotPrice, double RiskFreeRate, double CurrentTime);
    double calculateBondPosition(double OptionPrice, double SpotPrice, double RiskFreeRate, double CurrentTime);
    double get_timeToMaturity(double CurrentTime);

    //Méthode pour implémenter la stratégie de réplication
    void strategy(int NumPaths, int NumSteps, double RiskFreeRate);
};



