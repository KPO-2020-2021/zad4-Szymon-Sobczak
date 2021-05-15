#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <cmath>

/*************************************************************************************
 | Klasa modelujaca w programie pojecie macierzy.                                    |
 | Klasa posiada prywatne pole "value", stanowi ono zbior wartosci macierzy rotacji. |
 |  Jest to tablica dwuwymiarowa dla warosci typu double.                            |
 | Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie,                    |
 |  zmiane i odczytywanie danych z macierzy rotacji.                                 |
 | Klasa zawiera publiczne przeciazenia operatorow funkcyjnych opowiedzialnych       |
 |  za wprowadzanie i odczytywanie wartosci z macierzy rotacji, oraz przeciazenie    |
 |  operatora mnozenia macierzy razy wetkor i przeciazenia operatora dodawania       |
 |  dwoch macierzy.                                                                  | 
 | Klasa posiada metode inicjujaca macierz wartosciami funkcji trygonometrycznych    |
 |  dla zadanego konta obrotu.                                                       |
 | W roli modyfikacji zadania, dodano metode wyznaczajaca wyznacznik macierzy.       |
 */

template <unsigned int Size>
class Matrix{
private:
    double value[Size][Size];            /* Wartosci macierzy */
public:
    Matrix();                            /* Bezparametryczny konstruktor klasy */       
    Matrix(double [Size][Size]);         /* Konstruktor klasy z parametrem */

    Vector<Size> operator * (Vector<Size> const &tmp);    /* Operator mnożenia przez wektor */
    Matrix<Size> operator * (Matrix<Size> const &tmp);
    Matrix<Size>  operator / (const double &tmp);
    Matrix operator + (Matrix const &tmp);    /* Operator dodwania dwoch macierzy */

    Matrix<Size> reset_matrix();

    double determinant_of_the_matrix() const; /* Obliczenie wyznacznika macierzy */
    
    double & operator () (unsigned int row, unsigned int column); /* Przeciazenia operatora funkcyjnego */
    const double & operator () (unsigned int row, unsigned int column) const;
};

template <unsigned int Size>
std::ostream & operator << (std::ostream &out, Matrix<Size> const &mat); /* Przeciazenie operatora << sluzace wyswietlaniu macierzy */ 

template <unsigned int Size>
std::istream & operator >> (std::istream &in, Matrix<Size> &mat);        /* Przeciazenie operatora >> sluzace wczytywaniu wartosci do macierzy */ 

/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
template <unsigned int Size>
Matrix<Size>::Matrix(){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            i == j ? value[i][j] = 1 : value[i][j] = 0;
        }
    }
}

/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
template <unsigned int Size>
Matrix<Size>::Matrix(double tmp[Size][Size]){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            value[i][j] = tmp[i][j];
        }
    }
}

/******************************************************************************
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */
template <unsigned int Size>
Vector<Size> Matrix<Size>::operator * (Vector<Size> const &tmp){
    Vector<Size> result;
    for (unsigned int i = 0; i < Size; ++i){ 
        for (unsigned int j = 0; j < Size; ++j){
            result[i] += value[i][j] * tmp[j];
            }
    }
    return result; 
}





template <unsigned int Size>
Matrix<Size> Matrix<Size>::operator * (Matrix<Size> const &tmp){
    Matrix<Size> result;
    for(unsigned int i = 0; i < Size; ++i){
        for(unsigned int j = 0; j < Size; ++j){    
            result(i,j) = 0;
            for(unsigned int k = 0; k < Size; ++k){
                result(i,j) +=  value[i][k] * tmp(k,j);
            }
        }
    }
    return result; 
}







template <unsigned int Size>
Matrix<Size> Matrix<Size>::operator / (const double &tmp){
    Matrix<Size> result;
    if (tmp == 0)
        throw std::runtime_error("Wykonano dzielenie przez 0");

    for (unsigned int i = 0; i < Size; ++i)
        for (unsigned int j = 0; j < Size; ++j)
            result(i,j) = value[i][j] / tmp;  
    return result;
}

template <unsigned int Size>
Matrix<Size> Matrix<Size>::reset_matrix(){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            i == j ? value[i][j] = 1 : value[i][j] = 0;
        }
    }
    return *this;
}




/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
template <unsigned int Size>
double & Matrix<Size>::operator()(unsigned int row, unsigned int column){
    if (row >= Size) 
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    if (column >= Size)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return value[row][column];
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
template <unsigned int Size>
const double & Matrix<Size>::operator ()(unsigned int row, unsigned int column) const{
    if (row >= Size)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    if (column >= Size) 
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return value[row][column];
}

/******************************************************************************
 |  Przeciążenie dodawania macierzy                                           |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik dodawania,                    |
 |      v - wektor, czyli drugi skladnik dodawania.                           |
 |  Zwraca:                                                                   |
 |      Macierz - iloczyn dwóch podanych macierzy.                            |
 */
template <unsigned int Size>
Matrix<Size> Matrix<Size>::operator + (Matrix<Size> const &tmp){
    Matrix result;
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                        |
 */
template <unsigned int Size>
std::istream & operator>>(std::istream &in, Matrix<Size> &mat){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            in >> mat(i, j);
        }
    }
    if (in.fail())
        throw std::runtime_error(":/ Podano wartosc nie bedaca typu double ");
    return in;
}

/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */
template <unsigned int Size>
std::ostream & operator<<(std::ostream &out, const Matrix<Size> &mat){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

/********************************************************************************************
 |  Metoda klasy Matrix obliczajaca wyznacznik macierzy z uzyciem metody eliminacji Gaussa  |
 |  Argumenty:                                                                              |
 |      this - macierz, ktorej wyznacznik bedzie obliczany.                                 |
 |  Zwraca:                                                                                 |
 |      Wartosc wyznacznika macierzy typu double                                            |
 */
template <unsigned int Size>
double Matrix<Size>::determinant_of_the_matrix() const{
    double ratio;
    Matrix temp_matrix = *this; /* Stworzenie nowej tymczasowej macierzy sluzacej do obliczen */
    for(unsigned int i = 0; i < Size; i++){
        if(temp_matrix(i,i) == 0.0)
            throw std::runtime_error(":/ Podczas wyznaczania wyznacznika, napotkano 0 w macierzy ");
        for(unsigned int j = i + 1; j < Size; j++){
            ratio = temp_matrix(j,i) / temp_matrix(i,i);
            for(unsigned int k = 0; k < Size; k++){
                temp_matrix(j,k) -=  ratio * value[i][k];
            }
        }
    }
    return temp_matrix(0,0) * temp_matrix(1,1);
}
