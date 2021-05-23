#include "cuboid.hh"

/*!
    \file
        \brief Definicja metod klasy Cuboid

    Zawiera definicje funkcji i metod klasy Cuboid.
 */

/*!
    Domyślny konstruktor obiektu typu Cuboid.               
                                                                                                                                              
    \return Prostopaloscian o wszyskich wierzcholakach w (0, 0, 0).        
 */
Cuboid::Cuboid(){
    for (int i=0;i<CORNERS;i++)
        Global_corners[i] = Vector3D();    
    Center_of_cub =  Vector3D();
}
 
/*!
    Alternatywny konstruktor obiektu typu Cuboid. Konstruktor pozwala na inicjalizacje prostopadloscianu z uzyciem wektorow.                                          
                                                                                          
    \param[in] CornerA - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W1.                                                          
    \param[in] CornerB - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W2.                                                         
    \param[in] CornerC - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W3.                                                         
    \param[in] CornerD - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W4. 
    \param[in] CornerE - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W5.                                                            
    \param[in] CornerF - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W6.    
    \param[in] CornerG - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W7.    
    \param[in] CornerH - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W8.      
    \param[in] CornerH - wektor opisujacy polozenie w ukladzie lokalnym wierzcholka W8. 
    \param[in] center_of_cuboid - wektor opisujacy polozenie srodka prostopadloscianu. 

    \return Prostopadloscian o srodku i wierzcholakach zainicjownaych wartosciami wektorow.                                            
 */

 Cuboid::Cuboid(Vector3D  CornerA, Vector3D  CornerB, Vector3D CornerC, Vector3D CornerD, Vector3D  CornerE,Vector3D  CornerF,Vector3D  CornerG,Vector3D  CornerH, Vector3D center_of_cuboid){
    Center_of_cub = center_of_cuboid;

    Local_corners[0] = CornerA; 
    Local_corners[1] = CornerB;
    Local_corners[2] = CornerC; 
    Local_corners[3] = CornerD;
    Local_corners[4] = CornerE;
    Local_corners[5] = CornerF;
    Local_corners[6] = CornerG;
    Local_corners[7] = CornerH;

    for(int i = 0; i < CORNERS; ++i)   
        Global_corners[i] = Local_corners[i] + center_of_cuboid; 
}

/*!                                                                                                         
    \param[in] index - index wierzcholka globalnego prostopadloscianu.                                             
                                                                   
    \return Wartosc wierzcholka globalnego prostopadloscianu w danym miejscu tablicy jako stala.                
 */

const Vector3D & Cuboid::operator [] (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka prostopadloscianu");
    } 
    return Global_corners[index];
}

/*!                                                                                                 
    \param[in]  index - index wierzcholka globalnego prostopadloscianu.                                             
                                                                  
    \return Wartosc wierzcholka globalnego prostopadloscianu w danym miejscu tablicy.                           
*/

 Vector3D & Cuboid::operator[](int index) {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka prostopadloscianu");
    } 
    return const_cast <Vector3D &> (const_cast <const Cuboid *> (this)->operator[](index));
}

/*!          
    Metoda klasy prostopadloscian sluzaca do sprawdzania wartosci wspolrzednych wierzcholkow lokalnych.
    Metoda stworzona do testow progamu.

    \param[in] index - index wierzcholka lokalnego prostopadloscianu.                                             
                                                                   
    \return Wartosc lokalna wierzcholka prostopadloscianu w danym miejscu tablicy jako stala.                
 */

const Vector3D & Cuboid::operator () (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka prostopadloscianu");
    } 
    return Local_corners[index];
}

/*!  
    Metoda realizjaca proces transformacji miedzy lokalnym ukladem wspolrzednych prostopadloscianu do ukladu globalnego.

    \param [in] vector - Wektor przesuniecia srodka prostopadloscianu.
    \param [in] mtx - Macierz rotacji. 
*/ 

void Cuboid::Move_cuboid(Vector3D const & vector, Matrix3x3 const & mtx){
    Matrix3x3 temp = mtx; 
    for(int i = 0; i < CORNERS; ++i)
        Global_corners[i] = (temp * Local_corners[i]) + Center_of_cub + vector;  
}

/*!
    Funkcja wykonujaca operacje przeciazenia operatora <<. Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych wierzcholka prostopadloscianu.       
                                                                                                   
    \param[in]  Strm - Referencja do strumienia typu ostream, na ktory maja zostac wypisane wspolrzedne wektora.              
    \param[in]  Rc - Referencja do prostopadloscianu, ktorego wspolrzedne wierzcholkow maja zostac wpisane na wskazany strumien.     
                                                                                                          
    \return Wypisane wspolrzende wskazanego prostopadloscianu, w odpowiedniej formie na wskazane wyjscie.                          
 */
std::ostream & operator << (std::ostream & Out, const Cuboid & Rc){
    for (int i = 0; i < CORNERS; i++){
        Out << Rc[i] << std::endl;
        if(i%2==1)
            Out << std::endl;
    }
    return Out;
}

/*!
    Metoda klasy Cuboid realizujaca zapis wartosci wspolrzednych wierzcholkow globalnych prostopadloscianu do pliku.                    
                                                                                                                                                                                                                                                       
    \param[in] this - prostopadloscian do zapisu.                                                                           
    \param[in] sNazwaPliku - wskaznik na napis stanowiacy nazwe pliku wyjsciowego.                                                                                                                                     
 */

void Cuboid::Write_cub_to_file(const char *sNazwaPliku) const{
    std::ofstream  FileStrm;
    Vector3D P1,P2, temp_vec[]={Global_corners[0],Global_corners[7],Global_corners[2],Global_corners[5]};
    
    FileStrm.open(sNazwaPliku);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }
    
    P1 = (temp_vec[0] + temp_vec[1])/2;
    P2 = (temp_vec[2] + temp_vec[3])/2;

    FileStrm << P1 << std::endl
             << Global_corners[6] << std::endl
             << Global_corners[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    FileStrm << P1 << std::endl
             << Global_corners[7] << std::endl
             << Global_corners[5] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Global_corners[1] << std::endl
             << Global_corners[3] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Global_corners[0] << std::endl
             << Global_corners[2] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Global_corners[6] << std::endl
             << Global_corners[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm.close();
}

/*!
    Metoda klasy Cuboid wykonujaca operacje sprawdzenia, czy podane w parametrze dlugosci bokow sa sobie rowne.
                                                                                                                                                                      
    \param[in] array - tablica dlugosci zestawu bokow prostopadloscianu.                                        
                                                                                        
    \return true - jesli boki sa rowne.   
    \return false - jesli boki nie sa rowne.                                    
 */

bool are_sides_equal(double const array[]){
    for (unsigned int i = 0; i < 4 ; ++i)
        for (unsigned int j = i + 1; j < 4; ++j){
            if (array[i] - array[j] < -MAX_VALUE_DIFF || array[i] - array[j] > MAX_VALUE_DIFF )
              return false;
        }
    return true;
}

/*!
    Metoda klasy Cuboid wykonujaca operacje sprawdzenia dlugosci i zgodnosci bokow prostopadloscianu i wyswietleniu informacji o tym na standardowe wyscie.     
    Wypisuje na standardowe wyjscie dane o bokach prostopadloscianu. 

    \param[in] this - prostopadloscian, ktory ma zostac poddany sprawdzeniu.                                               
 */

void Cuboid::Is_it_cub() const{
 
    double  A[4] = {vector_length(Global_corners[0],Global_corners[1]), vector_length(Global_corners[2],Global_corners[3]), vector_length(Global_corners[4],Global_corners[5]), vector_length(Global_corners[6],Global_corners[7])},
            B[4] = {vector_length(Global_corners[0],Global_corners[2]), vector_length(Global_corners[1],Global_corners[3]), vector_length(Global_corners[4],Global_corners[6]), vector_length(Global_corners[5],Global_corners[7])},
            C[4] = {vector_length(Global_corners[0],Global_corners[6]), vector_length(Global_corners[1],Global_corners[7]), vector_length(Global_corners[2],Global_corners[4]), vector_length(Global_corners[3],Global_corners[5])};
            
    if (are_sides_equal(A)){
        if (A[0] == B[0])
            std::cout << ":) Przeciwlegle boki sa sobie rowne." << std::endl;
        else if (A[0] > B[0])
            std::cout << ":) Przeciwlegle, dluzsze boki prostopadloscianu sa sobie rowne." << std::endl;
        else 
            std::cout << ":) Przeciwlegle, krotsze boki prostopadloscianu sa sobie rowne." << std::endl;
    }   
    else {
        if (A[0] == B[0]){
            std::cout << ":( Przeciwlegle boki nie sa sobie rowne." << std::endl;
        }
        else if (A[0] > B[0])
            std::cout << ":( Przeciwlegle, dluzsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
        else 
            std::cout << ":( Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
    }
    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << A[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << A[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << A[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << A[3] << std::endl << std::endl;

    if (are_sides_equal(B)){
        if (A[0] == B[0])
            std::cout << ":) Przeciwlegle boki sa sobie rowne." << std::endl;
        else if (B[0] > A[0])
            std::cout << ":) Przeciwlegle, dluzsze boki prostopadloscianu sa sobie rowne." << std::endl;
        else 
            std::cout << ":) Przeciwlegle, krotsze boki prostopadloscianu sa sobie rowne." << std::endl;
    }   
    else{
        if (A[0] == B[0]){
            std::cout << ":( Przeciwlegle boki nie sa sobie rowne." << std::endl;
        }
        else if (B[0] > A[0])
            std::cout << ":( Przeciwlegle, dluzsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
        else 
            std::cout << ":( Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;  
    }
    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << B[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << B[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << B[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << B[3] << std::endl << std::endl;

    if (are_sides_equal(C))
        std::cout << ":) Poprzeczne boki prostopadloscianu sa sobie rowne." << std::endl;
    else 
        std::cout << ":( Poprzeczne boki prostopadloscianu nie sa sobie rowne." << std::endl;       

    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << C[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << C[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << C[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << C[3] << std::endl << std::endl;
 }