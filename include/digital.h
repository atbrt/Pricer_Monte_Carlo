#pragma once
#include "option.h"


//Classe pour les options digitales
class DigitalOption : public Option {
public:
    //Constructeur
    DigitalOption(double Strike, double Maturity, bool IsCall, class underlying_asset* Underlying);

    //Destructeur
    virtual ~DigitalOption();

    //Méthode pour calculer le payoff
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle
};

