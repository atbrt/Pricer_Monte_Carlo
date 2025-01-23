#pragma once
#include "option.h"


//Classe pour les options européennes
class EuropeanOption : public Option {
public:
    //Constructeur
    EuropeanOption(double Strike, double Maturity, bool IsCall, class underlying_asset* Underlying);

    //Destructeur
    virtual ~EuropeanOption();

    //Méthode pour calculer le payoff
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle
};

