#include "cuboid.hh"

/*!
    \file
    \brief Definicja metod klasy Cuboid

    Zawiera definicje metod kalsy Cuboid.
 */


/*!
    Domyślny konstruktor obiektu typu Rectangle. Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.               
                                                                                                                                              
    \return Prostokat o wierzcholakach zainicjowanych wartosciami wektorow zerowych.        
 */
Cuboid::Cuboid(){
    for (int i=0;i<CORNERS;i++)
        Corners[i] = Vector3D();    
}
 
/*!
    Alternatywny konstruktor obiektu typu Rectangle. Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.                                          
                                                                                          
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

    \return Prostokat o wierzcholakach zainicjowanych wartosciami wektorow.                                            
 */

 Cuboid::Cuboid(Vector3D  CornerA, Vector3D  CornerB, Vector3D CornerC, Vector3D CornerD,Vector3D  CornerE,Vector3D  CornerF,Vector3D  CornerG,Vector3D  CornerH, Vector3D center_of_cuboid){
    center_of_cub = center_of_cuboid;

    Origin_Corners[0] = CornerA; 
    Origin_Corners[1] = CornerB;
    Origin_Corners[2] = CornerC; 
    Origin_Corners[3] = CornerD;
    Origin_Corners[4] = CornerE;
    Origin_Corners[5] = CornerF;
    Origin_Corners[6] = CornerG;
    Origin_Corners[7] = CornerH;

    for(int i = 0; i < CORNERS; ++i)   
        Corners[i] = Origin_Corners[i] + center_of_cuboid; 
}

/*!                                                                                                         
    \param[in] index - index prostokata.                                             
                                                                   
    \return    Wartosc prostokata w danym miejscu tablicy jako stala.                
 */

const Vector3D & Cuboid::operator [] (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu prostokata");
    } 
    return Corners[index];
}

/*!                                                                                                 
    \param[in]  index - index prostokata.                                             
                                                                  
    \return Wartosc prostokata w danym miejscu tablicy.                           
*/

 Vector3D & Cuboid::operator[](int index) {
    return const_cast <Vector3D &> (const_cast <const Cuboid *> (this)->operator[](index));
}



Cuboid Cuboid::Move_cuboid(Vector3D const & vector, Matrix3x3 const & mtx){
    Matrix3x3 temp = mtx; 
    for(int i = 0; i < CORNERS; ++i)
        Corners[i] = (temp * Origin_Corners[i]) + center_of_cub + vector;  
    return *this;
}

/*!
    Metoda klasy Rectangle realizaujca dzialanie translacji prostokata o wybrany wektor.                        
                                                                                                                                                                                 
    \param[in] vector - wektor translacji.                                                                               
                                                                                                     
    \return Prostokat o zmienionym polozeniu za sprawa operacji translacji o wektor.                                   
*/

Cuboid Cuboid::Translate_cub(Vector3D const &vector){
    for (int i=0; i < CORNERS; ++i){
       Corners[i] = Origin_Corners[i] + vector;
    }
    return *this;
}

/*!
   Metoda klasy Rectangle realizaujca dzialanie obrotu prostokata o wybrany kat, wybrana ilosc razy.    
                                                                                                                                              
   \param[in] multiplier - ile razy ma zostac wykonany obrot.                                                 
   \param[in] angle - kat o jaki ma zostac obrocony prostokat.                                                

   \return Prostokat o zmienionym polozeniu za sprawa operacji obrotu.                                      
 */

Cuboid Cuboid::Rotate_cub (Matrix3x3 const & mtx){
    Matrix3x3 temp = mtx;
    for(int i = 0; i < CORNERS; ++i)
        Corners[i] = temp * Origin_Corners[i];
    return *this;
}

/*!
  Funkcja wykonujaca operacje przeciazenia operatora <<. Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych wierzcholka prostokata.       
                                                                                                   
    \param[in]  Strm - Referencja do strumienia typu ostream, na ktory maja zostac wypisane wspolrzedne wektora.              
    \param[in]  Rc - Referencja do prostokata, ktorego wspolrzedne wierzcholkow maja zostac wpisane na wskazany strumien.     
                                                                                                          
    \return Wypisane wspolrzende wksazanego prostokata, w odpowiedniej formie na wskazane wyjscie.                          
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
    Funkcja wykonujaca operacje przeciazenia operatora >>. Funkcja sluzy do wprowadzania wartosci wspolrzednych wierzcholkow prostokata ze wskazanego strumienia wejsciowego.   
                                                                                                  
    \param[in] Strm - Referencja do strumienia typu istream, z ktorego maja zostac wczytane wspolrzedne wierzcholkow prostokata. 
    \param[in] Vec - Referencja do prostokata, do ktorego maja zostac wpisane podane wspolrzedne weirzcholkow.                   

    \return Wczytany obiekt- prostokat.                                                                                        
 */

std::istream & operator >> (std::istream & In,Cuboid & Rc){
    for (int i=0; i<CORNERS;i++){
        In >> Rc[i];
    }
    return In;
}


/*!
    Metoda klasy Cuboid realizujaca zapis wartosci wspolrzednych wierzcholkow globalnych prostopadloscianu do pliku.                    
                                                                                                                                                                                                                                                       
    \param[in] this - prostopadloscian do zapisu.                                                                           
    \param[in] sNazwaPliku - wskaznik na napis stanowiacy nazwe pliku wyjsciowego.                                                                                                                                     
 */

void Cuboid::Write_cub_to_file(const char *sNazwaPliku) const{
    std::ofstream  FileStrm;
    Vector3D P1,P2, temp_vec[]={Corners[0],Corners[7],Corners[2],Corners[5]};
    
    FileStrm.open(sNazwaPliku);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }
    
    P1 = (temp_vec[0] + temp_vec[1])/2;
    P2 = (temp_vec[2] + temp_vec[3])/2;

    FileStrm << P1 << std::endl
             << Corners[6] << std::endl
             << Corners[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    FileStrm << P1 << std::endl
             << Corners[7] << std::endl
             << Corners[5] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Corners[1] << std::endl
             << Corners[3] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Corners[0] << std::endl
             << Corners[2] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << Corners[6] << std::endl
             << Corners[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm.close();
}


/*!
    Metoda klasy Rectangle wykonujaca operacje wyznaczenia dlugosic bokow prostokata i sprawdzenia, czy przeciwlegle boki sa sobie rowne.
                                                                                                                                                                      
    \param[in] this - prostokat, ktory ma zostac poddany sprawdzeniu.                                        
                                                                                        
    \return Wypisuje na standardowe wyjscie dane o bokach prostokata.                                     
 */

bool are_sides_equal(double const array[]){
    for (unsigned int i = 0; i < 4 ; ++i)
        for (unsigned int j = i + 1; j < 4; ++j){
            if (array[i] - array[j] < -MAX_VALUE_DIFF || array[i] + array[j] > MAX_VALUE_DIFF )
              return false;
        }
    return true;
}

/*!
    Metoda klasy Rectangle wykonujaca operacje wyznaczenia dlugosic bokow prostokata i sprawdzenia, czy przeciwlegle boki sa sobie rowne.
                                                                                                                                                          
    \param[in] this - prostokat, ktory ma zostac poddany sprawdzeniu.                                        
                                                                                         
    \return    Wypisuje na standardowe wyjscie dane o bokach prostokata.                                     
 */

void Cuboid::Is_it_cub() const{
 
    double  A[4] = {vector_length(Corners[0],Corners[1]), vector_length(Corners[2],Corners[3]), vector_length(Corners[4],Corners[5]), vector_length(Corners[6],Corners[7])},
            B[4] = {vector_length(Corners[0],Corners[2]), vector_length(Corners[1],Corners[3]), vector_length(Corners[4],Corners[6]), vector_length(Corners[5],Corners[7])},
            C[4] = {vector_length(Corners[0],Corners[6]), vector_length(Corners[1],Corners[7]), vector_length(Corners[2],Corners[4]), vector_length(Corners[3],Corners[5])};

    if (are_sides_equal(A)){
        if (A[0] == B[0])
            std::cout << ":( Przeciwlegle boki nie sa sobie rowne." << std::endl;
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
            std::cout << ":) Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
    }
    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << A[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << A[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << A[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << A[3] << std::endl << std::endl;

    if (are_sides_equal(B)){
        if (A[0] == B[0])
            std::cout << ":( Przeciwlegle boki nie sa sobie rowne." << std::endl;
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
            std::cout << ":) Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;  
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

//     std::cout << std::endl;

//     if(a - c < MAX_VALUE_DIFF && c - a < MAX_VALUE_DIFF){ /* Sprawdzenie spojnosci dlugosci przeciewleglych bokow */
//         if(a == b && a == d && c == b && c == d)          /* Warunek generujacy komunikat, gdy badana figura to kwadrat */
//             std::cout << ":) Przeciwlegle boki kwadratu sa sobie rowne." << std::endl;
//         else if(a > b && a > d && c > b && c > d)         /* Ustalenie, ktore boki prostokata sa dluzsze, a ktore krotsze */
//             std::cout << ":) Dluzsze przeciwlegle boki sa sobie rowne." << std::endl;
//         else
//             std::cout << ":) Krotsze przeciwlegle boki sa sobie rowne." << std::endl;
//     }
//     else{ 
//         if(a >= b && a >= d && c >= b && c >= d)
//             std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne." << std::endl;
//         else
//             std::cout << ":O Krotsze przeciwlegle boki nie sa sobie rowne." << std::endl;
//     }
//     std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << a << std::endl; /* Wyswietlenie informacji o dl. bokow */
//     std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << c << std::endl;
//     std::cout << std::endl;
    
//     if(b - d < MAX_VALUE_DIFF && d - b < MAX_VALUE_DIFF){
//         if(a == b && a == d && c == b && c == d) 
//             std::cout << ":) Przeciwlegle boki kwadratu sa sobie rowne." << std::endl;
//         else if(b >= a && b >= c && d >= a && d >= c)
//             std::cout << ":) Dluzsze przeciwlegle boki sa sobie rowne. "<< std::endl;
//         else
//             std::cout << ":) Krotsze przeciwlegle boki sa sobie rowne." << std::endl;
//     }
//     else{ 
//         if(a >= b && a >= d && c >= b && c >= d)
//             std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne." << std::endl;
//         else
//             std::cout << ":O  Krotsze przeciwlegle boki nie sa sobie rowne." << std::endl;
//     }
//     std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << b << std::endl;
//     std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << d << std::endl;
//     std::cout << std::endl;
 }