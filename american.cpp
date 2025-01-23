#include "american.h"
#include <vector>

// Constructeur :
AmericanOption::AmericanOption (double Strike, double Maturity, bool IsCall, underlying_asset* Underlying): Option(Strike, Maturity, IsCall, Underlying, "American") {}

//Destructeur :
AmericanOption::~AmericanOption(){};

//Payoff d'une option américaine : on prend la valeur intrinsèque à maturité
double AmericanOption::get_payoff(const std::vector<double>& path) const
    {
        double S_T = path.back(); //On prend la dernière valeur du pricepath (donc la valeur à maturité )
        return get_intrinsicValue(S_T); //On prend sa valeur intrinsèque
    }