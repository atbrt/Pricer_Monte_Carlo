#include <iostream>
#include <cmath>
#include "norm.h"

//Constructeur
Norm::Norm(){}

double Norm::norm_pdf(const double& x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);  // une fonction qui retourne la la valeur de la densité de la loi gaussienne
}

double Norm::normcdf(const double& x){
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));  // une fonction qui retourne la valeur de la fonction de répartition de la loi normale utile pour l 'expression du prix d'un call ou un put

    if (x >= 0.0) {
        return (1.0 - norm_pdf(x) * k_sum);
    } else {
        return 1.0 - normcdf(-x);
    }
}
