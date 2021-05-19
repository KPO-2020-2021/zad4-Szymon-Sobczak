#pragma once

#include "size.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <cmath>

/*!
  Klasa modelujaca w programie pojecie wektora.                                        
  Klasa posiada prywatne pole "size" bedace tablica- zbiorem wspolrzednych wekotra.    
  Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie, zmiane i odczytywanie 
    danych o wspolrzednych wektora.                                                    
  Klasa zawiera publiczne przeciazenia operatorow indeksujacych opowiedzialnych za     
    wprowadzanie i odczytywanie wspolrzendych wektora oraz przeciazenie operatora      
    dodawania, odejmowania dwoch wektorow i mnozenia, dzielenia wektora razy skalar.   
*/

template <unsigned int Size>
class Vector{
private:
    double size[Size];     /* Tablica wartosci wektora */
public:
    Vector();              /* Bezparametryczny konstruktor klasy */
    Vector(double [Size]); /* Konstruktor klasy z parametrem */
    Vector operator + (const Vector &v);    /* Operator dodawania dwoch wektorow */
    Vector operator - (const Vector &v);    /* Operator odejmowania dwoch wektorow */
    Vector operator * (const double &tmp);  /* Operator mnozenia wektora i liczby typu double */
    Vector operator / (const double &tmp);  /* Operator dzielenia wektora i liczby typu double */
    const double & operator [] (unsigned int index) const; /* Przeciazenia operatora indeksujacego */
    double & operator [] (unsigned int index);
};

template <unsigned int Size>
std::ostream & operator << (std::ostream &out, Vector<Size> const &tmp); /* Przeciazenie operatora << sluzace do wyswietlana wektora */ 

template <unsigned int Size>
std::istream & operator >> (std::istream &in, Vector<Size> &tmp); /* Przeciazenie operatora >> sluzace do wczytywania wartosci do wektora */



 /*!
   Konstruktor klasy Vector.                                                 
   Argumenty:                                                                
       Brak argumentow.                                                      
   Zwraca:                                                                   
       Tablice wypelniona wartoscia 0.                                       
 */

template <unsigned int Size>
Vector<Size>::Vector(){
    for (unsigned int i = 0; i < Size; ++i){
        size[i] = 0;
    }
}

/*!
   Konstruktor klasy Vector.                                                 
   Argumenty:                                                                
       tmp - Jednowymiarowa tablica typu double.                             
   Zwraca:                                                                   
       Tablice wypelniona wartosciami podanymi w argumencie.                 
 */
template <unsigned int Size>
Vector<Size>::Vector(double tmp[Size]){
    for (unsigned int i = 0; i < Size; ++i){
        size[i] = tmp[i];
    }
}

/*!
   Realizuje dodawanie dwoch wektorow.                                       
   Argumenty:                                                                
       this - pierwszy skladnik dodawania,                                   
       v - drugi skladnik dodawania.                                         
   Zwraca:                                                                   
       Sume dwoch skladnikow przekazanych jako wskaznik                      
       na parametr.                                                          
*/

template <unsigned int Size>
Vector<Size>  Vector<Size>::operator + (const Vector<Size> &v){
    Vector result;
    for (unsigned int i = 0; i < Size; ++i){
        result[i] = size[i] + v[i];
    }
    return result;
}

/*!
   Realizuje odejmowanie dwoch wektorow.                                     
   Argumenty:                                                                
       this - pierwszy skladnik odejmowania,                                 
       v - drugi skladnik odejmowania.                                       
   Zwraca:                                                                   
       Roznice dwoch skladnikow przekazanych jako wskaznik                   
       na parametr.                                                          
 */

template <unsigned int Size>
Vector<Size> Vector<Size>::operator - (const Vector<Size> &v){
    Vector result;
    for (unsigned int i = 0; i < Size; ++i){
        result[i] = size[i] - v[i];
    }
    return result; 
}

/*!
   Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.               
   Argumenty:                                                                
       this - pierwszy skladnik mnozenia (wektor),                           
       v - drugi skladnik mnozenia (liczba typu double).                     
   Zwraca:                                                                   
       Iloczyn dwoch skladnikow przekazanych jako wskaznik                   
       na parametr.                                                          
 */

template <unsigned int Size>
Vector<Size> Vector<Size>::operator * (const double &tmp){
    Vector result;
    for (unsigned int i = 0; i < Size; ++i){
        result[i] = size[i] * tmp;
    }
    return result;
}

/*!
   Realizuje dzielenie dwoch wektorow.                                       
   Argumenty:                                                                
       this - licznik dzielenia,                                             
       v - mianownik dzielenia.                                              
   Zwraca:                                                                   
       Iloraz dwoch skladnikow przekazanych jako wskaznik                    
       na parametr.                                                          
*/

template <unsigned int Size>
Vector<Size> Vector<Size>::operator / (const double &tmp){
    Vector result;
    if (tmp == 0)
        throw std::runtime_error("Wykonano dzielenie przez 0");
    for (unsigned int i = 0; i < Size; ++i){
        result[i] = size[i] / tmp;
    }
    return result;
}

/*!
   Funktor wektora.                                                          
   Argumenty:                                                                
       index - index wektora.                                                
   Zwraca:                                                                   
       Wartosc wektora w danym miejscu tablicy jako stala.                   
*/

template <unsigned int Size>
const double & Vector<Size>::operator [] (unsigned int index) const{
    if (index >= Size)
        throw std::runtime_error("Bledna wartosc indeksu wektora");
    return size[index];
}

/*!
   Funktor wektora.                                                          
   Argumenty:                                                                
       index - index wektora.                                                
   Zwraca:                                                                   
       Wartosc wektora w danym miejscu tablicy.                              
 */
template <unsigned int Size>
double & Vector<Size>::operator[](unsigned int index){
    if (index >= Size)
        throw std::runtime_error("Bledna wartosc indeksu wektora");
    return const_cast <double &> (const_cast <const Vector *> (this)->operator[](index));
}

/*!
   Przeciazenie operatora <<                                                 
   Argumenty:                                                                
       out - strumien wejsciowy,                                             
       tmp - wektor.                                                         
 */
template <unsigned int Size>
std::ostream & operator << (std::ostream &out, Vector<Size> const &tmp){
    for (unsigned int i = 0; i < Size; ++i) {
        out << std::fixed << std::setprecision(10) << tmp[i]<< "\t";
    }
    return out;
}

/*!
   Przeciazenie operatora >>                                                 
   Argumenty:                                                                
       in - strumien wyjsciowy,                                              
       tmp - wektor.                                                         
 */

template <unsigned int Size>
std::istream & operator >> (std::istream &in, Vector<Size> &tmp){
    for (unsigned int i = 0; i < Size; ++i){
        in >> tmp[i];
    }
    if (in.fail())
        throw std::runtime_error("Podano wartosc nie bedaca typu double ");
    std::cout << std::endl;
    return in;
}

template <unsigned int Size>
double vector_length(Vector<Size> const & vec1, Vector<Size> const & vec2){
    double temp=0;
    for (unsigned int i = 0; i < Size; ++i)
        temp += pow(vec2[i] - vec1[i],2);
    return sqrt(temp);
}
