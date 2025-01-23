#pragma once
#include "option.h"
#include "underlying.h"

class BlackScholesPricer {
protected:
    double RiskFreeRate;
public:
    //Constructeur
    BlackScholesPricer(double RiskFreeRate);

    //Méthode pour pricer l'option par la formule de Black Scholes (valable uniquement pour les europennes)
    double price(const Option& option, const underlying_asset& underlying) const;


    //Destructeur
    virtual ~BlackScholesPricer();

    //Getter
    double get_riskFreeRate() const;


};

