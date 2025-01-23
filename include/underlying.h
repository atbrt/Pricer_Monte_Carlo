
#pragma once


//Classe pour l'actif sous-jacent
class underlying_asset {
protected:
    //Les principales variables de l'actif sous-jacent son son prix spot, sa volatilité, et son drift. En réalité, on utilisera drift=riskfreerate dans BSM
    double Spot;
    double Volatility;
    double Drift;

public:
    //Constructeur :
    underlying_asset(double Spot, double Volatility, double Drift);

    //Destructeur:
    ~underlying_asset();

    //Getters:
    double get_spot() const;
    double get_volatility() const;
    double get_drift() const;

    //Setters :
    void set_spot(double newSpot);
};



