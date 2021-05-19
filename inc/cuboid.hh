
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
  \brief Klasa modelujaca w programie pojecie prostokata, ktorego wierzcholki sa wyrazone za pomoca wektorow.

  Klasa posiada prywatne pole "Corners" bedace tablica wektorow, opisuje ono wektorowo pozycje wierzcholkow prosotkata.
  Klasa posiada publiczny konstruktor domyśly oraz konstruktor pozwalajacy na inicjowanie prostokata za pomoca wektorow.
  Klasa posiada publiczne metody pozwalajace na:                                                                        
    - sprawdzenie czy prostokat posiada rowne przeciwlegle boki i wyswietlenie  informacji o tym na standarowe wyjscie, 
    - translacje prostokata o zadany wektor,                                                                            
    - obrot prostokata wokol srodka ukladu wspolrzednych o zadany kat, wybrana ilosc razy.                              
  
  Klasa zawiera publiczne przeciazenia operatora indeksujacego opowiedzialnych za wprowadzanie i odczytywanie wartosci  
    z wektorow.                                                                                                         
  
  Klasa posiada metode pozwalajaca zbadac kolizyjnosc dwoch prostokatow.                                                
*/
 
class Cuboid{
    private:  
        /*! \brief Wartosci wektorow reprezentujace poczatkowe wierzcholki prostokata */
        Vector3D Origin_Corners[CORNERS]; 

        /*! \brief Wartosci wektorow reprezentujace poczatkowe wierzcholki prostokata */
        Vector3D Corners[CORNERS]; 

        /*! \brief Wartosci wektorow reprezentujace tymaczasowe wierzcholki prostokata */
        Vector3D center_of_cub;

    public:   
        /*! \brief Bezparametryczny konstuktor klasy */
        Cuboid();                     
        
        /*! \brief Wieloparametrowy konstuktor klasy */
        Cuboid(Vector3D  CornerA, Vector3D CornerB, Vector3D CornerC, Vector3D CornerD,Vector3D CornerE,Vector3D CornerF,Vector3D CornerG,Vector3D CornerH,Vector3D center_of_cuboid); 
        
        /*! \brief Przeciazenie operatora indeksujacego */
        const Vector3D & operator [] (int index) const;         
        
        /*! \brief Przeciazenie operatora indeksujacego */
        Vector3D & operator [] (int index);

        /*! \brief Translacja prostokata prostokata o zadany wektor */
        Cuboid Translate_cub(Vector3D const &vector);      

        /*! \brief Obrot prostokata o zadany kat, zadana ilosc razy */
        Cuboid Rotate_cub (Matrix3x3 const & mtx);    

        /*! \brief Sprawdzenie czy dany prostokat ma rowne przeciwlegle boki */
        void Is_it_cub() const;    

        /*! \brief Zapis wartosci wspolrzendych wierzcholkow do pliku */
        void Write_cub_to_file(const char *sNazwaPliku) const;  

        /*! \brief Przmieszczenie prostopadloscianu w ukladzie globalnym */         
        Cuboid Move_cuboid(Vector3D const &vector, Matrix3x3 const & mtx);
};

bool are_sides_equal(double const array[]);

/*! \brief Przeciazenie operatora << sluzace wyswietlaniu wartosci prostokata */ 
std::ostream & operator << (std::ostream & Strm, const Cuboid & Rc);    
 
/*! \brief Przeciazenie operatora >> sluzace wczytywaniu wartosci do prostokata */         
std::istream & operator >> (std::ostream & Strm, Cuboid & Rc);        
