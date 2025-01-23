
#include "digital.h"

#include "european.h"
#include <vector>

//Constructeur
DigitalOption::DigitalOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying): Option(Strike, Maturity, IsCall, Underlying, "Digital") {}

//Destructeur :
DigitalOption::~DigitalOption(){};



//Méthode de calcul du payoff pour une option digitale, càd la Heavyside de sa moneyness
double DigitalOption::get_payoff(const std::vector<double>& path) const {
    double S_T = path.back();

    if (IsCall) {
        if (S_T > Strike) {
            return 1.0;
        }
        return 0.0;
    } else {
        if (S_T < Strike) {
            return 1.0;
        }
        return 0.0;
    }
};