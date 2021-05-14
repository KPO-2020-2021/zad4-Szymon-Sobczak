
#include "matrix3x3.hh"

/***********POPRAWIĆ
 * *******************************************************************
 |  Metoda klasy Matrix inicjalizujaca macierz rotacji wartosciami            |
 |  funkcji trygonometrycznych dla wybranego kata.                            |
 |  Argumenty:                                                                |
 |      this - macierz, ktora ma zostac zainicjowana wartosciami.             |
 |      angle - wartosc double kata o jaki ma zostac obrocony prostokat.      |
 |  Zwraca:                                                                   |
 |      Poprawnie zainizalinzowana wartoscami macierz typu Matrix.            |
 */

Matrix3x3 Fill_matrix_OX (double const angle){
    Matrix3x3 temp;
    double angle_radians = angle * M_PI / 180.0;
    temp(0,0) = 1;
    temp(0,1) = 0;
    temp(0,2) = 0;
    temp(1,0) = 0;
    temp(1,1) = cos(angle_radians);
    temp(1,2) = -sin(angle_radians);
    temp(2,0) = 0;
    temp(2,1) = sin(angle_radians);
    temp(2,2) = cos(angle_radians);
    return temp;
}

Matrix3x3 Fill_matrix_OY (double const angle){
    Matrix3x3 temp;
    double angle_radians = angle * M_PI / 180.0;
    temp(0,0) = cos(angle_radians);
    temp(0,1) = 0;
    temp(0,2) = sin(angle_radians);
    temp(1,0) = 0;
    temp(1,1) = 1;
    temp(1,2) = 0;
    temp(2,0) = -sin(angle_radians);
    temp(2,1) = 0;
    temp(2,2) = cos(angle_radians);
    return temp;
}

Matrix3x3 Fill_matrix_OZ (double const angle){
    Matrix3x3 temp;
    double angle_radians = angle * M_PI / 180.0;
    temp(0,0) = cos(angle_radians);
    temp(0,1) = -sin(angle_radians);
    temp(0,2) = 0;
    temp(1,0) = sin(angle_radians);
    temp(1,1) = cos(angle_radians);
    temp(1,2) = 0;
    temp(2,0) = 0;
    temp(2,1) = 0;
    temp(2,2) = 1;
    return temp;
}
    