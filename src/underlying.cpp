#include "underlying.h"


//Constructeur
underlying_asset::underlying_asset(double Spot, double Volatility, double Drift)
{
    this->Spot=Spot;
    this->Volatility=Volatility;
    this->Drift=Drift;
}

//Destructeur
underlying_asset::~underlying_asset(){}

// Getters :
double underlying_asset::get_spot() const{return Spot;};
double underlying_asset::get_volatility() const{return Volatility;};
double underlying_asset::get_drift() const{return Drift;};

//Setter
void underlying_asset::set_spot(double newSpot) {
    Spot = newSpot;
}