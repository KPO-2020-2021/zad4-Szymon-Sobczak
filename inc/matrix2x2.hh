#pragma once

#include "matrix.hh"

/*!
    \file  
        \brief Plik zawierajacy definicje konkretyzacji szablonu klasy Matrix do instancji Matrix2x2 - macierzy kwadratowej o wielkosci 2. Oraz prototyp funkcji wypelniajacej Matrix2x2 wartosciaciami macierzy obrotu w 2D dla zadanego kata.
*/

/*! \brief Konkretyzacja szablonu klasy Matrix do instancji  Matrix2x2 - macierzy kwadratowej o wielkosci 2. */
typedef Matrix<2> Matrix2x2;

/*! \brief Funkcja wypelniajaca Matrix2x2 wartosciaciami macierzy obrotu w 2D dla zadanego kata. */
Matrix2x2 Rotation_matrix_2x2 (double const angle);