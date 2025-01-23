#pragma once
#include "option.h"
#include <vector>

//Classe pour les options lookback
class LookbackOption : public Option {
public:
    // Constructeur
    LookbackOption(double Strike, double Maturity, bool IsCall, class underlying_asset* Underlying);

    // Destructeur
    virtual ~LookbackOption();

    //Méthode pour calculer le payoff
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle
};