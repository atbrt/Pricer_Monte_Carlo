#include "BlackScholesPricer.h"
#include <norm.h>
#include "option.h"
#include <fstream>
#include <cmath>

//Constructeur
BlackScholesPricer::BlackScholesPricer(double RiskFreeRate)
{
    this->RiskFreeRate=RiskFreeRate;
}

//Destructeur
BlackScholesPricer::~BlackScholesPricer(){};

//getter:
double BlackScholesPricer::get_riskFreeRate() const{return RiskFreeRate;};

//Pricer par la formule de Black-Scholes
double BlackScholesPricer::price(const Option& option, const underlying_asset& underlying) const {
    double S = underlying.get_spot();
    double K = option.get_strike();
    double sigma = underlying.get_volatility();
    double r = RiskFreeRate;
    double T=option.get_maturity();
    double numerator = log(S / K) + (r + sigma * sigma * 0.5) * T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator / denominator;
    double d2 = d1 - denominator;
    Norm normale;

    if (option.get_isCall()) {
        return S * normale.normcdf(d1) - exp(-r * T) * K * normale.normcdf(d2); // Pricing Call
    } else {
        return exp(-r * T) * K * normale.normcdf(-d2) - S * normale.normcdf(-d1); // Pricing Put
    }
}



