#include "underlying.h"
#include "option.h"

//Constructeur
Option::Option(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying, const std::string& Name)
    {
        this->Strike=Strike;
        this->Maturity=Maturity;
        this->IsCall=IsCall;
        this->Underlying=Underlying;
        this->Name=Name;
    }


//Destructeur
Option::~Option(){};

//Calcul de la valeur intrinsèque, càd la valeur que l'option aurait si elle était exercée aujourd'hui
double Option::get_intrinsicValue(double spot) const {
    if (IsCall) {
        return std::max(spot - Strike, 0.0);
    } else {
        return std::max(Strike - spot, 0.0);
    }
};

//Getters:
double Option::get_strike() const{return Strike;};
double Option::get_maturity() const{return Maturity;};
bool Option::get_isCall() const{return IsCall;};
std::string Option::get_name() const{return Name;};
underlying_asset* Option::get_underlying() const{return Underlying;};


//Setters pour la maturité et le prix spot qui servent pour la stratégie de réplication lors de l'actualisation du portefeuille
void Option::set_maturity(double newMaturity) {this->Maturity=newMaturity;};
void Option::set_spot(double newSpot) {Underlying->set_spot(newSpot);};