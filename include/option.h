#pragma once
#include "underlying.h"
#include <string>

class Option {
protected: //On met en protected les données qui concernent l'option
  double Strike;
  double Maturity;
  bool IsCall;
  std::string Name;
  underlying_asset* Underlying;


public:
  // Constructeur
  Option(double Strike, double Maturity, bool IsCall, underlying_asset* Underlying, const std::string& Name);


  //Destructeur virtuel, car on va faire des classes dérivées pour chaque type d'option
  virtual ~Option();

  //Getters
  double get_strike() const;
  double get_maturity() const;
  bool get_isCall() const;
  std::string get_name() const;
  underlying_asset* get_underlying() const;

  //Getters virtuels, car on va implémenter ces fonctions pour les classes dérivées
  virtual double get_payoff(const std::vector<double>& path) const=0;
  virtual double get_intrinsicValue(double spot) const;

  //Setters
  void set_maturity(double Maturity);
  void set_spot(double Spot);


};
