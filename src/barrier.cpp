#include "barrier.h"
#include <iostream>
#include "option.h"

//Constructeur :
BarrierOption::BarrierOption(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying, const std::string& BarrierType, double Barrier): Option(Strike, Maturity, IsCall, Underlying, "Barrier"){this->BarrierType=BarrierType; this->Barrier=Barrier;};

//Destructeur :
BarrierOption::~BarrierOption(){};

//Méthode pour vérifier si la barrière a été atteinte dans le chemin de prix :
bool BarrierOption::IsBarrierBreached(const std::vector<double>& path) const {
    //Disjonction de cas selon le type de barrière pour voir si la barrière est dépassée (par le haut ou par le bas)
    if (BarrierType == "UpAndOut" || BarrierType == "UpAndIn") {
        //Vérifie si le prix a atteint ou dépassé la barrière supérieure
        for (int i = 0; i < path.size(); i++) {
            double price = path[i];
            if (price >= Barrier) {
                return true;
            }
        }
    }
    else if (BarrierType == "DownAndOut" || BarrierType == "DownAndIn") {
        //Vérifie si le prix a atteint ou descendu en dessous de la barrière inférieure
        for (int i = 0; i < path.size(); i++) {
            double price = path[i];
            if (price <= Barrier) {
                return true;
            }
        }
    }
    //Sinon, c'est que le type de barrière entré par l'utilisateur n'est pas reconnu donc  :
    else {
        std::cout << "Type de barrière non reconnu." << std::endl;
    }
    return false;
}

//Méthode pour calcule le payoff pour une barrier option
double BarrierOption::get_payoff(const std::vector<double>& path) const {
    if (path.empty()) {
        std::cerr << "Chemin de prix vide. Payoff nul." << std::endl;
        return 0.0;
    }

    bool breached = IsBarrierBreached(path);
    double finalPrice = path.back(); //Prix final à maturité
    double payoff = 0.0; //On initialise le payoff à 0

    //Disjonction de cas pour le calcul du payoff, comme on a fait pour IsBarrierBreached
    if (BarrierType == "UpAndOut" || BarrierType == "DownAndOut") {
        if (!breached) {
            // Si la barrière n'est pas atteinte, payoff standard (valeur intrinsèque)
            payoff=this->get_intrinsicValue(finalPrice);
        }
        //Sinon, le payoff reste à 0
    }
    else if (BarrierType == "UpAndIn" || BarrierType == "DownAndIn")  {
        if (breached) {
            // Si la barrière est atteinte, payoff standard (valeur intrinsèque)
            payoff=this->get_intrinsicValue(finalPrice);
        }
        //Sinon, le payoff reste à 0
    }
    else {
        std::cerr << "Type de barrière non reconnu. Payoff nul." << std::endl; //Si le type de barrière n'est pas reconnu, on renvoie un payoff nul
    }
    return payoff;
}

//Getters :
std::string BarrierOption::get_barrierType() const{return BarrierType;};
double BarrierOption::get_barrier() const{return Barrier;};