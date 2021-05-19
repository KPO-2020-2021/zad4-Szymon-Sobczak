#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <cmath>

/*!
    \file Definicja metod klasy Cuboid
    \brief Prototyp i definicja szablonu kalsy Matrix<Size>.

    Prototypy i definicja metod szablonu kalsy Matrix<Size>.
 */


/*!
  \brief Szablon Klasy modelujacej w programie pojecie macierzy.   

  Klasa posiada prywatne pole "value", stanowi ono zbior wartosci macierzy rotacji. Jest to tablica dwuwymiarowa dla warosci typu double.                            
  Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie, zmiane i odczytywanie danych z macierzy rotacji.                                 
  Klasa zawiera publiczne przeciazenia operatorow funkcyjnych opowiedzialnych za wprowadzanie i odczytywanie wartosci z macierzy rotacji, oraz przeciazenie    
  operatora mnozenia macierzy razy wetkor i przeciazenia operatora dodawania dwoch macierzy.                                                                   
  Klasa posiada metode inicjujaca macierz wartosciami funkcji trygonometrycznych dla zadanego konta obrotu.                                                       
  W roli modyfikacji zadania, dodano metode wyznaczajaca wyznacznik macierzy.       
*/

template <unsigned int Size>
class Matrix{
private:
    /*! \brief Wartosci macierzy */
    double value[Size][Size];  

public:
    /*! \brief Bezparametryczny konstruktor klasy */  
    Matrix();                 

    /*! \brief Konstruktor klasy z parametrem */                
    Matrix(double [Size][Size]);         

    /*! \brief Operator mnożenia macierzy przez wektor */
    Vector<Size> operator * (Vector<Size> const &tmp);

    /*! \brief Operator mnożenia macierzy przez inna macierz */    
    Matrix<Size> operator * (Matrix<Size> const &tmp);

    /*! \brief Operator dzielenia macierzy przez skalar*/  
    Matrix<Size>  operator / (const double &tmp);

    /*! \brief Operator dodwania dwoch macierzy */
    Matrix operator + (Matrix const &tmp);    

    /*! \brief Metoda czyszczaca macierz- zprzywracajaca postac macierzy jedynkowej */
    Matrix reset_matrix();

    /*! \brief Operator porownania dwoch macierzy */
    bool operator == (Matrix const &tmp);  

    /*! \brief Przeciazenie operatora funkcyjnego */
    double & operator () (unsigned int row, unsigned int column); 

    /*! \brief Przeciazenie operatora funkcyjnego */
    const double & operator () (unsigned int row, unsigned int column) const;
};

/*! \brief Przeciazenie operatora << sluzace wyswietlaniu macierzy */

template <unsigned int Size>
std::ostream & operator << (std::ostream &out, Matrix<Size> const &mat);  

/*! \brief Przeciazenie operatora >> sluzace wczytywaniu wartosci do macierzy */
template <unsigned int Size>
std::istream & operator >> (std::istream &in, Matrix<Size> &mat);        

/*!
    \brief Konstruktor klasy Matrix.                                                 
                                                                                                
    \return  Macierz wypelnione wartoscia 0.                                       
*/

template <unsigned int Size>
Matrix<Size>::Matrix(){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            i == j ? value[i][j] = 1 : value[i][j] = 0;
        }
    }
}

/*!
    Konstruktor parametryczny klasy Matrix.                                                                                                   
    
    \param[in] tmp - dwuwymiarowa tablica z elementami typu double.                  
                                                                  
    \return  Macierz wypelniona wartosciami podanymi w argumencie.                 
*/

template <unsigned int Size>
Matrix<Size>::Matrix(double tmp[Size][Size]){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            value[i][j] = tmp[i][j];
        }
    }
}

/*!
    Realizuje mnozenie macierzy przez wektor.                                 
                                                                   
    \param[in]    this - macierz, czyli pierwszy skladnik mnozenia,                     
    \param[in]    v - wektor, czyli drugi skladnik mnozenia.                            
                                                                   
    \return  Iloczyn dwoch skladnikow przekazanych jako wektor.                    
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

/*!
    Realizuje mnozenie macierzy przez macierz.                                 
                                                                   
    \param[in]    this - macierz, czyli pierwszy skladnik mnozenia,                     
    \param[in]   tmp - macierz, czyli drugi skladnik mnozenia.                            
                                                                   
    \return  result - Iloczyn dwoch skladnikow przekazanych jako macierz.                    
*/

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

/*!
    Realizuje dzielenie macierzy przez wartosc typu double.                                 
                                                                   
    \param[in] this - macierz, czyli pierwszy skladnik mnozenia,                     
    \param[in] tmp - double, czyli dzielnik macierzy.                            
                                                                   
    \return  result - Iloraz macierzy i skalara przekazanych jako macierz.                    
*/

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

/*!
    Realizuje czyszczenie macierzy, przywracajac ja do stanu macierzy jednykowej.                                 
                                                                       
    \return  Macierz jedynkowa.                    
*/

template <unsigned int Size>
Matrix<Size> Matrix<Size>::reset_matrix(){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            i == j ? value[i][j] = 1 : value[i][j] = 0;
        }
    }
    return *this;
}

/*!
    Realizuje porownywanie wartosci w dwoch macierzach.                                 
                                                                   
    \param[in]   this - macierz, czyli pierwszy skladnik porownania,                     
    \param[in]   tmp - macierz, czyli drugi skladnik porownania.                            
                                                                   
    \return  true - jesli macierze sa rowne.          
    \return  false - jesli macierze nie sa rowne.           
*/

template <unsigned int Size>
bool Matrix<Size>::operator == (Matrix const &tmp){
    for (unsigned int i = 0; i < Size ; ++i)
        for (unsigned int j = 0; j < Size ; ++j) 
            if(value[i][j]-tmp(i,j) < -MAX_VALUE_DIFF || value[i][j]-tmp(i,j) > MAX_VALUE_DIFF)   
                return false;   
    return true;    
}


/*!                                                                                                     
    \param[in] row - numer wiersza.                                                  
    \param[in] column - numer kolumny.                                               

    \return Wartosc macierzy w danym miejscu tablicy.                             
*/

template <unsigned int Size>
double & Matrix<Size>::operator ()(unsigned int row, unsigned int column){
    if (row >= Size) 
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    if (column >= Size)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return value[row][column];
}


/*!                                  
    \param[in] row - numer wiersza.                                                  
    \param[in] column - numer kolumny.                                               
                                                                     
    \return Wartosc macierzy w danym miejscu tablicy jako stala.                  
*/

template <unsigned int Size>
const double & Matrix<Size>::operator ()(unsigned int row, unsigned int column) const{
    if (row >= Size)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    if (column >= Size) 
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return value[row][column];
}

/*!
    Przeciążenie dodawania macierzy  
                                                             
    \param[in] this - macierz, czyli pierwszy skladnik dodawania,                    
    \param[in] v - wektor, czyli drugi skladnik dodawania.                           
                                                                   
    \return  Macierz - suma dwóch podanych macierzy.                            
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

/*!
    Przeciazenie operatora >>                                                                                                                 
    
    \param[in]    in - strumien wyjsciowy,                                              
    \param[in]    mat - macierz.                                                        
*/

template <unsigned int Size>
std::istream & operator >> (std::istream &in, Matrix<Size> &mat){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            in >> mat(i, j);
        }
    }
    if (in.fail())
        throw std::runtime_error(":/ Podano wartosc nie bedaca typu double ");
    return in;
}

/*!
    Przeciazenie operatora <<                                                 

    \param[in] out - strumien wejsciowy,                                             
    \param[in] mat - macierz.                                                        
 */

template <unsigned int Size>
std::ostream & operator << (std::ostream &out, const Matrix<Size> &mat){
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size; ++j){
            out << " " << mat(i, j) << "  "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}