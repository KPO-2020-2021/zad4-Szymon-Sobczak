
#include "matrix2x2.hh"

/*!
    \file  
        \brief plik zawiera definicje funkcji wypelniajacej Matrix2x2 wartosciaciami macierzy obrotu w 2D dla zadanego kata.
*/

/*! 
    Funkcja wypelnia macierz o wielkosci 2 wartosciaciami pozwalajacymi obrot w 2D dla zadanego kata. 
    
    \param[in] angle - Kat obrotu.

    \return rotation_matrix - macierz2x2 uzupelniona warosciami rotacji dla zadanego kata.
*/
Matrix2x2 Rotation_matrix_2x2 (double const angle){
    Matrix2x2 rotation_matrix;
    double angle_radians = angle * M_PI / 180.0;
    rotation_matrix(0,0) = cos(angle_radians);
    rotation_matrix(0,1) = -sin(angle_radians);
    rotation_matrix(1,0) = sin(angle_radians);
    rotation_matrix(1,1) = cos(angle_radians);
    return rotation_matrix;
}
 