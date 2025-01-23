#pragma once
#include "option.h"
#include "Underlying.h"
#include <vector>

class MonteCarloPricer {
protected:
    //Les variables pour le pricer par Monte carlo sont le nombre de chemins générés, le nombre de steps, et le taux sans risque par lequel on actualisera
    int NumPaths;
    int NumSteps;
    double RiskFreeRate;

public:

    //Constructeur:
    MonteCarloPricer(int NumPaths, int NumSteps, double RiskFreeRate);

    // Destructeur
    virtual ~MonteCarloPricer();

    //Getters :
    int get_numPaths() const;
    int get_numSteps() const;
    double get_riskFreeRate() const;

    //Méthodes pour générer des chemins et de prix et pour pricer, en fonction de l'option et su sous jacent considéré
    std::vector<std::vector<double>> GeneratePricePaths(const underlying_asset& underlying, const Option& option) const;
    double Price(const Option& option, const underlying_asset& underlying) const;
};



