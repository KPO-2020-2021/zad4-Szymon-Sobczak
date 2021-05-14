#pragma once

#include "matrix.hh"

typedef Matrix<3> Matrix3x3;

Matrix3x3 Fill_matrix_OX (double const angle);  /* Wypenienie macierzy wartosciami funkcji tryg. dla zadanego kąta obrotu */
Matrix3x3 Fill_matrix_OY (double const angle);  
Matrix3x3 Fill_matrix_OZ (double const angle);  
    