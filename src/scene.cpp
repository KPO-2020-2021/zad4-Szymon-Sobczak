#include "scene.hh"

/*!
    \file
        \brief Definicje metod klasy Scene.

    Plik zawiera definicje metod klasy Scene.
*/

/*!
    Publiczny destrukor czyszczacy pliki tymczasowe, w ktorych zapisywane sa wspolrzedne globalne prostopadloscianow. 
*/

Scene::~Scene(){
    std::string datasets_path = "../datasets";
    for (const auto& entry : std::filesystem::directory_iterator(datasets_path)) 
        std::filesystem::remove_all(entry.path());
}

/*!
    Przeciazenie operatora indeksujacego, sluzy ono do uzyskiwania wspolrzednych wskazanego prostopadloscianu ze sceny.

    \param [in] index - Indeks wskazanego prostopadloscianu.

    \return Wskazany prsotopadloscian - obiekt typu Cuboid.
*/

const Cuboid & Scene::operator [] (unsigned int index) const{
    if (index>=set_of_cuboids.size())
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return set_of_cuboids.at(index);
}

/*!
    Metoda pozwalajaca pobrac wartosci macierzy rotacji wskazanego prostopadloscianu ze sceny.

    \param [in] index - Indeks wskazanego prostopadloscianu.

    \return Wskazana macierz rotacji - obiekt typu Matrix3x3.
*/

Matrix3x3 Scene::get_matrix(unsigned int index){
    return set_of_rotation_matrixes.at(index);
}

/*!
    Metoda pozwalajaca pobrac wartosci wektora translacji wskazanego prostopadloscianu ze sceny.

    \param [in] index - Indeks wskazanego prostopadloscianu.

    \return Wskazany wektor translacji - obiekt typu Vector3D.
*/

Vector3D Scene::get_vector(unsigned int index){
    return set_of_translation_vectors.at(index);
} 

/*!
    Metoda pozwaljaca modyfikowac macierz rotacji wskazanego prostopadloscianu na scenie.
    
    \param [in] mtx - macierz o jaka macierz rotacji wewnatrz sceny ma zostac pomnozona.
    \param [in] index - Indeks wskazanego prostopadloscianu.

*/

void Scene::update_matrix(Matrix3x3 const & mtx, unsigned int index){
    Matrix3x3 temp_matrix = mtx;
    set_of_rotation_matrixes.at(index) = temp_matrix * set_of_rotation_matrixes.at(index);
}

/*!
    Metoda pozwaljaca modyfikowac wektor przesuniecia wskazanego prostopadloscianu na scenie.
    
    \param [in] mtx - wektor dodawany do wekrora przesuniecia wewnatrz sceny.
    \param [in] index - Indeks wskazanego prostopadloscianu.

*/

void Scene::update_vector(Vector3D const & vec, unsigned int index){
    Vector3D temp_vector = vec;
    set_of_translation_vectors.at(index) = set_of_translation_vectors.at(index) + temp_vector;
}

/*!
    Metoda pozwalajaca na przemieszanie prostopaloscianu globalnie na scenie.
    
    \param [in] index - Indeks wskazanego prostopadloscianu.
*/

void Scene::Move_figure(unsigned int index){
    set_of_cuboids.at(index).Move_cuboid(set_of_translation_vectors.at(index), set_of_rotation_matrixes.at(index));
}

/*!
    Metoda sprawdzajaca ile prostopadloscianow znajduje sie aktualnie na scenie.

    \return aktualna liczba prostopadloscianow na scenie - unsigned int.
*/

unsigned int Scene::how_many_cuboids(){
    return set_of_cuboids.size();
}

/*!
    Metoda pozwalajaca dodac do sceny kolejny prostopadloscian.

    \param [in] center - Wektor reprezentujacy wspolrzedne globalne srodka nowego prostopadloscianu.
    \param [in] tra_OX - Dlugosc boku prostopadloscianu w osi OX. 
    \param [in] tra_OY - Dlugosc boku prostopadloscianu w osi OY. 
    \param [in] tra_OZ - Dlugosc boku prostopadloscianu w osi OZ. 
*/

void Scene::Add_cuboid(Vector3D const & center, double const & tra_OX, double const & tra_OY, double const & tra_OZ){
    Vector3D cub_apx[8], VecOX, VecOY, VecOZ;
  
    VecOX[0] = tra_OX/2; 
    VecOY[1] = tra_OY/2; 
    VecOZ[2] = tra_OZ/2;

    cub_apx[0] = cub_apx[0] - VecOX - VecOY - VecOZ;
    cub_apx[1] = cub_apx[1] + VecOX - VecOY - VecOZ;
    cub_apx[2] = cub_apx[2] - VecOX + VecOY - VecOZ;
    cub_apx[3] = cub_apx[3] + VecOX + VecOY - VecOZ;
    cub_apx[4] = cub_apx[4] - VecOX + VecOY + VecOZ;
    cub_apx[5] = cub_apx[5] + VecOX + VecOY + VecOZ;
    cub_apx[6] = cub_apx[6] - VecOX - VecOY + VecOZ;
    cub_apx[7] = cub_apx[7] + VecOX - VecOY + VecOZ;

    Cuboid cuboid_dummy(cub_apx[0], cub_apx[1], cub_apx[2], cub_apx[3], cub_apx[4], cub_apx[5], cub_apx[6], cub_apx[7], center);

    set_of_cuboids.push_back(cuboid_dummy); 
    set_of_rotation_matrixes.push_back(Matrix3x3());
    set_of_translation_vectors.push_back(Vector3D());   
}