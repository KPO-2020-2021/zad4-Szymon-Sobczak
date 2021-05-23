#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#include "vector3D.hh"
#include "matrix3x3.hh"
#include "matrix.hh"
#include "lacze_do_gnuplota.hh"

/*!
    \file
        \brief  Definicja klasy Cuboid.

    Prototypy funkcji i metod klasy Cuboid.
*/

/*!
    \brief Klasa modelujaca w programie pojecie prostopadloscianu, ktorego wierzcholki i centrum sa wyrazone za pomoca wektorow.

    Klasa posiada:
        - prywatne pole "Local_corners" bedace tablica wektorow, opisuje ono wektorowo pozycje wierzcholkow lokalnych prostopadloscianu.
        - prywatne pole "Global_corners" bedace tablica wektorow, opisuje ono wektorowo pozycje wierzcholkow globalnych prostopadloscianu.
        - prywatne pole "Center_of_cub" bedace wektorem, opisuje ono wektorowo pozycje globalnego srodka prostopadloscianu.
        - publiczny konstruktor domyśly oraz konstruktor pozwalajacy na inicjowanie prostopadloscianu za pomoca wektorow.
    
    Klasa posiada publiczne metody pozwalajace na:
        - Sprawdzenie, czy prostopadloscian posiada rowne przeciwlegle boki oraz wyswietlenie informacji o tym na standarowe wyjscie.
        - Przemieszczenie prostopadloscanu w ukladzie globalnym.
        - Zapis wartosci wierzcholkow globalnych do wskazanego pliku.
        - Przeciazenie operatorow indeksujacych, umozliwajacych odczytywanie i zmiane wartosci reprezentujacych wierzcholki prostopadloscianu.                                                            
*/
 
class Cuboid{
    private:  
        /*! \brief Tablica wektorow3D reprezentujacych rozklad wierzcholkow prostopadloscianu w ukladzie lokalnym */
        Vector3D Local_corners[CORNERS]; 

        /*! \brief Tablica wektorow3D reprezentujacych rozklad wierzcholkow prostopadloscianu w ukladzie globalnym */
        Vector3D Global_corners[CORNERS]; 

        /*! \brief Wektor3D reprezentujacy srodek prostopadloscianu w przestrzeni globalnej */
        Vector3D Center_of_cub;

    public:   
        /*! \brief Bezparametryczny konstuktor klasy */
        Cuboid();                     
        
        /*! \brief Wieloparametrowy konstuktor klasy */
        Cuboid(Vector3D  CornerA, Vector3D CornerB, Vector3D CornerC, Vector3D CornerD,Vector3D CornerE,Vector3D CornerF,Vector3D CornerG,Vector3D CornerH,Vector3D center_of_cuboid); 
        
        /*! \brief Przeciazenie operatora indeksujacego */
        const Vector3D & operator [] (int index) const;         
        
        /*! \brief Przeciazenie operatora indeksujacego */
        Vector3D & operator [] (int index);

        /*! \brief Metoda sluzaca do podgladania wspolrzednych lokalnych prostopadloscianu w celu testowania dzialania programu */
        const Vector3D & operator () (int index) const;
 
        /*! \brief Przmieszczenie prostopadloscianu w ukladzie globalnym */         
        void Move_cuboid(Vector3D const &vector, Matrix3x3 const & mtx);
   
        /*! \brief Sprawdzenie czy dany prostopadloscian ma rowne przeciwlegle boki */
        void Is_it_cub() const;    

        /*! \brief Zapis wartosci wspolrzendych wierzcholkow do pliku */
        void Write_cub_to_file(const char *sNazwaPliku) const;  
};

/*! \brief Funkcja pomocnicza, okresla czy podane dlugosci sa rowne. */
bool are_sides_equal(double const array[]);

/*! \brief Przeciazenie operatora << sluzace wyswietlaniu wartosci prostopadloscianu */ 
std::ostream & operator << (std::ostream & Strm, const Cuboid & Rc);    
 