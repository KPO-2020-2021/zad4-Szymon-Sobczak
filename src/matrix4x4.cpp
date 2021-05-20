#include "matrix4x4.hh"

/*!
    \file  
        \brief plik zawiera definicje funkcji wypelniajacej Matrix4x4 wartosciaciami macierzy polaczonego obrotu i translacji.
*/

/*! 
    Funkcja wypelnia macierz o wielkosci 4 wartosciaciami pozwalajacymi obrot wielu osiach i translacje o wektor w 3D, dla zadanch katow i wektora przesuniecia. 
    
    \param[in] alpha - Kat obrotu wokol osi OX.
    \param[in] beta - Kat obrotu wokol osi OY.
    \param[in] gamma - Kat obrotu wokol osi OZ.
    \param[in] translation - Wektor przesuniecia.

    \return rotation_matrix - macierz2x2 uzupelniona warosciami rotacji dla zadanego kata.
*/
Matrix4x4 Fill_combined_matrix_4x4(double alpha, double beta, double gamma, Vector3D translation){
    Matrix4x4 temp;

    for (unsigned int i = 0; i < 4; ++i)
        temp(i,i) = 0; 
        
    double alpha_rad = alpha * M_PI / 180.0, beta_rad = beta * M_PI / 180.0,gamma_rad = gamma * M_PI / 180.0;;

    temp(0,0) = cos(alpha_rad)*cos(beta_rad); 
    temp(0,1) = cos(alpha_rad)*sin(beta_rad)*sin(gamma_rad)-sin(alpha_rad)*cos(gamma_rad); 
    temp(0,2) = cos(alpha_rad)*sin(beta_rad)*cos(gamma_rad)+sin(alpha_rad)*sin(gamma_rad); 
    temp(0,3) = translation[0];
  
    temp(1,0) = sin(alpha_rad)*cos(beta_rad); 
    temp(1,1) = sin(alpha_rad)*sin(beta_rad)*sin(gamma_rad)+cos(alpha_rad)*cos(gamma_rad); 
    temp(1,2) = sin(alpha_rad)*sin(beta_rad)*cos(gamma_rad)-cos(alpha_rad)*sin(gamma_rad); 
    temp(1,3) = translation[1];

    temp(2,0) = -sin(beta_rad);
    temp(2,1) = cos(beta_rad)*sin(gamma_rad);
    temp(2,2) = cos(beta_rad)*cos(gamma_rad);
    temp(2,3) = translation[2];
  
    temp(3,3) = 1;

    return temp;
}