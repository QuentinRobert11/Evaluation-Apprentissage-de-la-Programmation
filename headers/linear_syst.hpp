#ifndef DEF_SYST
#define DEF_SYST

#include "../headers/matrix.hpp"
#include <math.h>
#include<iostream>

template <typename Number>
Matrix<Number> solve_grad(Matrix<Number>& A, Matrix<Number>& B, Matrix<Number> X0, const Number& epsilon);
//Une fonction qui résoud un système linéaire à l'aide de la méthode du gradient conjugué

template <typename Number>
Matrix<Number> solve_pivot(Matrix<Number> A, Matrix<Number> B);

void tests_Solver();
//Une fonction qui test le solver et print des résultats


#endif