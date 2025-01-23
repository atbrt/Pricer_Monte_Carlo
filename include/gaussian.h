
#pragma once
#include <random>

//cette classe permet de générer des nombres aléatoires suivant la loi normale centrée réduite en utilisant la formule de Box Muller

class GenerateGaussian {
public:
    //Constructeur: initialise le générateur avec une graine :
    GenerateGaussian(unsigned int seed);

    std::mt19937 generator; //Le générateur de nombres aléatoires Mersenne Twister
    std::uniform_real_distribution<double> uniformDist; //Générateur de nombres aléatoires uniformes entre 0 et 1

    //méthode qui génère et renvoie un nombre aléatoire suivant une loi normale N(0,1) :
    double generate();
};