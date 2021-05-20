#pragma once

#include "matrix.hh"
#include "vector3D.hh"

/*!
    \file 
        \brief Plik zawiera definicje konkretyzacji szablonu Matrix do postaci macierzy 4x4 oraz funkcji wypelniajaca macierz4x4, by byla macierza polaczonego obrotu i translacji.
*/

/*! \brief Konkretyzacja szablonu klasy Matrix do instancji  Matrix4x4 - macierzy kwadratowej o wielkosci 4. */
typedef Matrix<4> Matrix4x4;

/*! \brief Funkcja wypelniajaca Matrix4x4 wartosciaciami polaczonej macierzy obrotu i translacji dla zadanych katow i wektora */
Matrix4x4 Fill_combined_matrix_4x4(double alpha_x, double beta_y, double gamma_z, Vector3D translation);