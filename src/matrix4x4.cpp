#include "matrix4x4.hh"

/*!
    \file  
        \brief plik zawiera definicje funkcji wypelniajacej Matrix4x4 wartosciaciami macierzy polaczonego obrotu i translacji.
*/

/*! 
    Funkcja wypelnia macierz o wielkosci 4 wartosciaciami pozwalajacymi na obrot wielu osiach i translacje o wektor w 3D, dla zadanch katow i wektora przesuniecia. 
    
    \param[in] alpha - Kat obrotu wokol osi OX - roll.
    \param[in] beta - Kat obrotu wokol osi OY - pitch.
    \param[in] gamma - Kat obrotu wokol osi OZ - yaw.
    \param[in] translation - Wektor przesuniecia.

    \return rotation_matrix - macierz4x4 uzupelniona warosciami rotacji dla zadanych katow i wektorem przesuniecia.
*/

Matrix4x4 Fill_combined_matrix_4x4(double alpha_x, double beta_y, double gamma_z, Vector3D translation){
    Matrix4x4 combined_matrix;

    for (unsigned int i = 0; i < 4; ++i)
        combined_matrix(i,i) = 0; 
        
    double X_angle = alpha_x * M_PI / 180.0, Y_angle = beta_y * M_PI / 180.0, Z_angle = gamma_z * M_PI / 180.0;

    combined_matrix(0,0) = cos(Z_angle) * cos(Y_angle); 
    combined_matrix(0,1) = cos(Z_angle) * sin(Y_angle) * sin(X_angle) - sin(Z_angle) * cos(X_angle); 
    combined_matrix(0,2) = cos(Z_angle) * sin(Y_angle) * cos(X_angle) + sin(Z_angle) * sin(X_angle); 
    combined_matrix(0,3) = translation[0];
  
    combined_matrix(1,0) = sin(Z_angle) * cos(Y_angle); 
    combined_matrix(1,1) = sin(Z_angle) * sin(Y_angle) * sin(X_angle) + cos(Z_angle) * cos(X_angle); 
    combined_matrix(1,2) = sin(Z_angle) * sin(Y_angle) * cos(X_angle) - cos(Z_angle) * sin(X_angle); 
    combined_matrix(1,3) = translation[1];

    combined_matrix(2,0) = -sin(Y_angle);
    combined_matrix(2,1) = cos(Y_angle) * sin(X_angle);
    combined_matrix(2,2) = cos(Y_angle) * cos(X_angle);
    combined_matrix(2,3) = translation[2];
  
    combined_matrix(3,3) = 1;

    return combined_matrix;
}