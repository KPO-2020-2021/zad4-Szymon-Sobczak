#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <filesystem>
#include <vector>

#include "vector.hh"
#include "matrix.hh"
#include "cuboid.hh"
#include "lacze_do_gnuplota.hh"

/*!
    \file
        \brief Definicja klasy Scene.

    Plik zawiera prototypy metod klasy Scene.

*/

/*!
  \brief Klasa modelujaca w programie pojecie Sceny.   

    Klasa posiada:
        - prywatne pole "set_of_cuboids" bedace wektorem prostopadloscianow, reprezentuje zbior prostopadloscianow znajdujacych sie na scenie.
        - prywatne pole "set_of_rotation_matrixes" bedace wektorem macierzy3x3, reprezentuje ono zbior macierzy rotacji dla poszczegolnych prostopadloscianow ze sceny.
        - prywatne pole "set_of_translation_vectors" bedace wektorem wektorow3D, reprezentuje ono zbior wektorow translacji dla poszczegolnych prostopadloscianow ze sceny.
        - Publiczny destrukor czyszczacy pliki tymczasowe, w ktorych zapisywane sa wspolrzedne globalne prostopadloscianow. 

    Utworzona klasa zawiera publiczne metody pozwalajace:
        - modyfikowac macierz rotacji wskazanego prostopadloscianu na scenie.
        - modyfikowac wektor przesuniecia wskazanego prostopadloscianu na scenie.
        - przemieszanic wskazany prostopaloscian w ukladzie globlanym sceny.
        - pobrac wartosci macierzy rotacji wskazanego prostopadloscianu ze sceny.
        - sprawdzenic ile prostopadloscianow znajduje sie aktualnie na scenie.
        - dodac do sceny kolejny prostopadloscian.

    Zdefiniowane jest takze przeciazenie operatora indeksujacego, sluzy ono do uzyskiwania wspolrzednych wskazanego prostopadloscianu ze sceny.
*/

class Scene{
    private:
        /*! \brief Pole klasy reprezentujace zbior prostopadloscianow na scenie. */
        std::vector <Cuboid> set_of_cuboids;
        
        /*! \brief Pole klasy reprezentujace zbior macierzy rotacji dla poszczególnych prostopadloscianow ze scenie. */
        std::vector <Matrix3x3> set_of_rotation_matrixes;

        /*! \brief Pole klasy reprezentujace zbior wektorow przesuniecia dla poszczególnych prostopadloscianow ze scenie. */
        std::vector <Vector3D> set_of_translation_vectors;

    public:
        /*! \brief Destruktor klasy Scene. */
        ~Scene();
        
        /*! \brief Metoda pozwalajaca na przemieszczenie globalne figury na scenie. */
        void Move_figure(unsigned int index);
        
        /*! \brief Metoda pozwalajaca na skladnie kolejnych macierzy rotacji w odpowiednim polu struktury. */
        void update_matrix(Matrix3x3 const & mtx, unsigned int index);

        /*! \brief Metoda pozwalajaca na skladnie kolejnych wektorow przesuniecia w odpowiednim polu struktury. */
        void update_vector(Vector3D const & vec,unsigned int index);
        
        /*! \brief Metoda pozwalajaca odczytac wartosci macierzy rotacji dla wskazanego prostopadloscianu */
        Matrix3x3 get_matrix(unsigned int index);

        /*! \brief Metoda pozwalajaca odczytac wartosci wektora przesuniecia dla wskazanego prostopadloscianu */
        Vector3D get_vector(unsigned int index);
        
        /*! \brief Przeciazenie operatora indeksujacego, sluzace do podgladania wartosci wierzcholkow prospoadloscianow zawarych w scenie. */
        const Cuboid & operator [] (unsigned int index) const;

        /*! \brief Metoda wyznaczajaca aktualna ilosc prostopadloscianow na scenie */
        unsigned int how_many_cuboids();

        /*! \brief Metoda realizujaca dodawnie kolejnych prostopadloscianow do sceny  */
        void Add_cuboid(Vector3D const & Apx0, double const & tra_OX, double const & tra_OY, double const & tra_OZ);
};
