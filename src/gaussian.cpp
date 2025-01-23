#include <cmath>
#include "gaussian.h"

//Constructeur :
GenerateGaussian::GenerateGaussian(unsigned int seed) :
    generator(seed),          //Initialise le générateur avec la graine
    uniformDist(0.0, 1.0) // Configure la distribution uniforme entre 0 et 1
{}

//Implémentation de la méthode de Box-Muller pour générer des nombres selon la loi normale centrée réduite
double GenerateGaussian::generate() {
    //On génère deux nombres aléatoires uniformes entre 0 et 1 pour la méthode de Box Muller
    double nombre_uniforme1 = uniformDist(generator);
    double nombre_uniforme2 = uniformDist(generator);

    //On applique la formule de Box Muller qui génère le nombre aléatoire gaussien
    double nombre_gaussien = std::sqrt(-2.0*std::log(nombre_uniforme1))*std::cos(2* M_PI*nombre_uniforme2);

    return nombre_gaussien;
}