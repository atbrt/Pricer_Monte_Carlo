#include <Eigen/Dense> //librairie pour effectuer de l'algèbre linéaire
#include "montecarlopricer.h"
#include <cmath>
#include <gaussian.h>
#include <vector>

//Constructeur
MonteCarloPricer::MonteCarloPricer(int NumPaths, int NumSteps, double RiskFreeRate)
{
    this->NumPaths=NumPaths;
    this->NumSteps=NumSteps;
    this->RiskFreeRate=RiskFreeRate;
}

//Destructeur
MonteCarloPricer::~MonteCarloPricer(){};

//méthode pour générer des chemins de prix
std::vector<std::vector<double>> MonteCarloPricer::GeneratePricePaths (const underlying_asset& underlying, const Option& option) const {
    //initialisation d'une matrice pour stocker les chemins de prix sous forme de lignes dans la matrice
    std::vector<std::vector<double>> paths(NumPaths, std::vector<double>(NumSteps, 0.0));

    //On récupère les paramètres du modèle pour générer les prix sous BSM
    double spot = underlying.get_spot();
    double volatility = underlying.get_volatility();
    double drift = RiskFreeRate; //Le drift est le taux sans risque dans le modèle de BSM
    double maturity = option.get_maturity();
    double deltaT = maturity / NumSteps; //Pas de temps entre chaque prix

    //Initialisation du générateur de nombres aléatoires sous loi centrée réduite
    GenerateGaussian rng(12345); //Utilisation d'une valeur de seed fixe pour générer les mêmes chemins aléatoires

    for (int i = 0; i < NumPaths; ++i) {
        paths[i][0] = spot;
        for (int j = 1; j < NumSteps; ++j) {
            double Z = rng.generate(); //On génère la variable aléatoire centrée réduite
            //On utilise le modèle de BSM pour calculer le prix suivant :
            paths[i][j] = paths[i][j - 1] * std::exp((drift - 0.5 * volatility * volatility) * deltaT +volatility * std::sqrt(deltaT) * Z);
        }
    }
    return paths;
}

//Méthode pour le pricing d'une option
double MonteCarloPricer::Price(const Option& option, const underlying_asset& underlying) const {
    //On distingue selon si l'option est américaine ou non car ces dernières peuvent être exercées avant maturité
    if (option.get_name() == "American") {
        //On génère les chemins de prix et on initialise une colonne de payoffs pour chaque chemin généré
        std::vector<std::vector<double>> paths = GeneratePricePaths(underlying, option);
        std::vector<double> payoffs(NumPaths, 0.0);

        //Calcul des payoffs à maturité pour chaque chemin
        for (int i = 0; i < NumPaths; ++i) {
            payoffs[i] = option.get_payoff(paths[i]);
        }

        //On va utiliser la méthode de Longstaff-Schwartz, en remontant le temps pour voir s'il est optimal ou non d'exercer l'option avant maturité à chaque période
        for (int t = NumSteps - 2; t >= 0; --t) {

            //On regarde les indices des chemins ITM et les prix correspondants :
            std::vector<int> in_the_money_indices;
            std::vector<double> S_t;
            for (int i = 0; i < NumPaths; ++i) {
                double St = paths[i][t];
                double intrinsic_value = option.get_intrinsicValue(St);
                if (intrinsic_value > 0.0 && payoffs[i] > 0.0) {
                    in_the_money_indices.push_back(i);
                    S_t.push_back(St);
                }
            }

            //S'il existe des chemins ITM, on fait la régression linéaire pour estimer la valeur de continuation et comparer
            if (!in_the_money_indices.empty()) {
                //Préparation des vecteurs pour la régression linéaire
                Eigen::VectorXd X(S_t.size());  //Vecteur des prix
                Eigen::VectorXd Y(S_t.size());  //Vecteur des payoffs actualisés

                for (size_t i = 0; i < S_t.size(); ++i) {
                    X(i) = S_t[i]; //Ajout du prix
                    double time = t * (option.get_maturity()/NumSteps);
                    Y(i) = payoffs[in_the_money_indices[i]] * std::exp(-RiskFreeRate*(option.get_maturity()-time)); //Actualisation
                }

                //Régression linéaire pour estimer la valeur de continuation
                Eigen::MatrixXd A(S_t.size(), 2);
                A.col(0) = Eigen::VectorXd::Ones(S_t.size()); //Terme constant dans la RL
                A.col(1) = X; //Colonne des prix sous jacents
                Eigen::VectorXd coefficients = (A.transpose() * A).ldlt().solve(A.transpose() * Y); //On fait la RL, en résolvant tAAx=tAY
                Eigen::VectorXd continuation_values = A * coefficients; //Permet de calculer la valeur estimée de la continuation grâce à la RL

                //Décision d'exercice ou non en comparant la valeur intrinsèque et la valeur estimée de continuation
                for (size_t i = 0; i < in_the_money_indices.size(); ++i) {
                    int path_index = in_the_money_indices[i];
                    double St = S_t[i];
                    double intrinsic_value = option.get_intrinsicValue(St);
                    double continuation = continuation_values(i);

                    if (intrinsic_value > continuation) {
                        payoffs[path_index] = intrinsic_value;
                    }
                }
            }
        }

        //Pricing par actualisation de la moyenne des payoffs
        double somme = 0.0;
        for (int i = 0; i < NumPaths; ++i) {
            somme += payoffs[i];
        }
        return (somme / NumPaths) * std::exp(-RiskFreeRate*option.get_maturity());

    } else {  //Pour tous les autres types d'options, on utilise simplement leur fonction de payoff qu'on a codée pour chacune de leur classe
        std::vector<std::vector<double>> paths = GeneratePricePaths(underlying, option);
        double somme = 0.0;
        for (int i = 0; i < NumPaths; ++i) {
            double payoff = option.get_payoff(paths[i]);
            somme += payoff;
        }
        //On actualise la moyenne des payoffs
        return (somme / NumPaths) * std::exp(-RiskFreeRate * option.get_maturity());
    }
}

//Getters :
int MonteCarloPricer::get_numPaths() const{return NumPaths;};
int MonteCarloPricer::get_numSteps() const{return NumSteps;};
double MonteCarloPricer::get_riskFreeRate() const{return RiskFreeRate;};

