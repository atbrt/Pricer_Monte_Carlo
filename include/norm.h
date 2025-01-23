#pragma once




class Norm
{
public:
    Norm();
    double norm_pdf(const double& x); //Densité d'une loi normale centrée réduite
    double normcdf(const double& x);  //Cette focntion permet d'estimer la distribution d'une loi normale centrée réduite grâce à une fonction récursive

};

