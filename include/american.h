#pragma once
#include "option.h"

//Classe pour les options américaines qui hérite de la classe Option
class AmericanOption : public Option {
public:
    // Constructeur
    AmericanOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying);

    //Destructeur
    virtual ~AmericanOption();

    //Méthode du payoff pour les options américaines à partir d'un chemin de prix généré aléatoirement
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle
};
