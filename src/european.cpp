
#include "european.h"
#include <vector>

//Constructeur
EuropeanOption::EuropeanOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying): Option(Strike, Maturity, IsCall, Underlying, "Asian") {}

//Destructeur :
EuropeanOption::~EuropeanOption(){};



//Méthode de calcul du payoff pour une option européenne, càd sa valeur intrinsèque à maturité
double EuropeanOption::get_payoff(const std::vector<double>& path) const
{
    double S_T = path.back();
    return this->get_intrinsicValue(S_T);
}