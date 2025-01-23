#pragma once
#include "option.h"
#include <vector>

//Classe pour les options asiatiques
class AsianOption : public Option {
public:
    //Constructeur
    AsianOption(double Strike, double Maturity, bool IsCall, class underlying_asset* Underlying);

    //Destructeur
    virtual ~AsianOption();

    //Méthode pour calculer le payoff
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle
};