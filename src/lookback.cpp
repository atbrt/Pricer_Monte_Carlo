#include "lookback.h"
#include <numeric>


//Constructeur
LookbackOption::LookbackOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying): Option(Strike, Maturity, IsCall, Underlying, "Lookback") {}

//Destructeur :
LookbackOption::~LookbackOption(){};

//Méthode du calcul du payoff pour une option Lookback (ici à strike fixe)
double LookbackOption::get_payoff(const std::vector<double>& path) const {
    if (IsCall) {
        //Pour une option call Lookback, on cherche le prix le plus haut
        double prix_maximum = path[0]; //On initialise le max à la première valeur
        //On parcourt tous les prix pour trouver le maximum
        for (int i = 1; i < path.size(); i++) {
            if (path[i] > prix_maximum) {
                prix_maximum = path[i];
            }
        }

        //Le payoff est la différence entre le prix maximum et le prix strike
        double payoff = prix_maximum - Strike;
        return std::max(0.0, payoff);
    }
    else {
        //Pour une option Put Lookback, on cherche le prix le plus bas
        double prix_minimum = path[0];
        for (int i = 1; i < path.size(); i++) {
            if (path[i] < prix_minimum) {
                prix_minimum = path[i];
            }
        }

        //Le payoff est la différence entre le strike et le prix minimum
        double payoff = Strike - prix_minimum;
        return std::max(0.0, payoff);
    }
}