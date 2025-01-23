#include "asian.h"
#include <numeric>

//Constructeur
AsianOption::AsianOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying): Option(Strike, Maturity, IsCall, Underlying, "Asian") {}

//Destructeur :
AsianOption::~AsianOption(){};

//Méthode du payoff pour les options asiatiques
double AsianOption::get_payoff(const std::vector<double>& path) const
    {
        //On calcule la moyenne arithmétique du chemin de prix :
        double sum = 0.0;  //On initialise la somme à 0 puis on va sommer les prix du chemins par une boucle for
        for (int i = 0; i < path.size(); i++) {
            sum = sum + path[i];
        }
        double average = sum / path.size();  //On calcule la moyenne

        //On calcule le payoff à partir de la moyenne
        if (IsCall) {
            return std::max(average - Strike, 0.0);
        } else {
            return std::max(Strike - average, 0.0);
        }
    }
