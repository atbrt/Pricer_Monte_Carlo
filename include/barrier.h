#pragma once
#include "option.h"
#include <vector>

class BarrierOption : public Option {

protected: //On rajoute des variables pour les barrier options, qui ont des caractéristiques selon le type de barrier et son niveau
    std::string BarrierType;
    double Barrier;
public:
    //Constructeur
    BarrierOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying, const std::string& BarrierType, double Barrier);


    //Destructeur
    virtual ~BarrierOption();

    //Methode pour calculer le payoff
    double get_payoff(const std::vector<double>& path) const override; //On surcharge la méthode virtuelle


    //Méthode pour vérifier si la barrière a été atteinte
    bool IsBarrierBreached(const std::vector<double>& path) const;

    //Getters
    std::string get_barrierType() const;
    double get_barrier() const;
};