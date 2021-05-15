#include "cuboid.hh"

/************************************************************************************
 | Domyślny konstruktor obiektu typu Rectangle.                                     |
 | Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.              | 
 | Argumenty:                                                                       |
 |  brak.                                                                           | 
 | Zwraca:                                                                          |
 |  Prostokat o wierzcholakach zainicjowanych wartosciami wektorow zerowych.        |
 */
Cuboid::Cuboid(){
    for (int i=0;i<CORNERS;i++)
        Corners[i] = Vector3D();    
}
 
/****************************************************************************************************************
 | Alternatywny konstruktor obiektu typu Rectangle.                                                             |
 | Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.                                          |
 | Warunki wstepne:                                                                                             |
 |  CornerA - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerB - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerC - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerD - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 | Warunki koncowe:                                                                                             |
 |   brak.                                                                                                      |   
 | Argumenty:                                                                                                   |
 |  CornerA - wektor opisujacy polozenie wierzcholka A.                                                         | 
 |  CornerB - wektor opisujacy polozenie wierzcholka B.                                                         |
 |  CornerC - wektor opisujacy polozenie wierzcholka C.                                                         |
 |  CornerD - wektor opisujacy polozenie wierzcholka D.                                                         |
 | Zwraca:                                                                                                      |
 |   Prostokat o wierzcholakach zainicjowanych wartosciami wektorow.                                            |
 */

 Cuboid::Cuboid(Vector3D  CornerA, Vector3D  CornerB, Vector3D CornerC, Vector3D CornerD,Vector3D  CornerE,Vector3D  CornerF,Vector3D  CornerG,Vector3D  CornerH){
    Origin_Corners[0] = CornerA; 
    Origin_Corners[1] = CornerB;
    Origin_Corners[2] = CornerC; 
    Origin_Corners[3] = CornerD;
    Origin_Corners[4] = CornerE;
    Origin_Corners[5] = CornerF;
    Origin_Corners[6] = CornerG;
    Origin_Corners[7] = CornerH;
    for(int i = 0; i < CORNERS; ++i){
        Corners[i] = Origin_Corners[i];
    }
}

/******************************************************************************
 |  Funktor prostokata.                                                       |
 |  Warunki wstepne:                                                          |
 |      index - wartosc musi zawierac sie w przedziale od 0 do CORNERS.       |               
 |  Warunki koncowe:                                                          |
 |      brak.                                                                 |
 |  Argumenty:                                                                |
 |      index - index prostokata.                                             |
 |  Zwraca:                                                                   |
 |      Wartosc prostokata w danym miejscu tablicy jako stala.                |
 */

const Vector3D & Cuboid::operator [] (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu prostokata");
    } 
    return Corners[index];
}

/******************************************************************************
 |  Funktor prostokata.                                                       |
 |  Argumenty:                                                                |
 |      index - index prostokata.                                             |
 |  Zwraca:                                                                   |
 |      Wartosc prostokata w danym miejscu tablicy.                           |
 */
Vector3D & Cuboid::operator[](int index) {
    return const_cast <Vector3D  &> (const_cast <const Cuboid *> (this)->operator[](index));
}

Cuboid Cuboid::Move_cuboid(Vector3D const &vector, Matrix3x3 const & mtx){
    Matrix3x3 temp = mtx;
    for(int i=0; i<CORNERS; ++i)      
        Corners[i] = temp * Origin_Corners[i] + vector;
    return *this;
    }

/*****************************************************************************************************************
 | Metoda klasy Rectangle realizaujca dzialanie translacji prostokata o wybrany wektor.                          |
 | Warunki wstepne:                                                                                              |
 |   vector - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.  |
 | Warunki koncowe:                                                                                              |
 |   brak.                                                                                                       |
 | Argumenty:                                                                                                    |
 |   vector - wektor translacji.                                                                                 |
 | Zwraca:                                                                                                       |
 |   Prostokat o zmienionym polozeniu za sprawa operacji translacji o wektor.                                    |
 */

Cuboid Cuboid::Translate_cub(Vector3D const &vector){
    for (int i=0; i<CORNERS; ++i){
       Corners[i] = Origin_Corners[i] + vector;
    }
    return *this;
}


/*****************************************************************************************************
 | Metoda klasy Rectangle realizaujca dzialanie obrotu prostokata o wybrany kat, wybrana ilosc razy. |   
 | Warunki wstepne:                                                                                  |
 |   multiplier - wartosc musi miesicic sie w zakresie wlasciwym int.                                |
 |   angle - wartosc musi byc typu double.                                                           |
 | Warunki koncowe:                                                                                  |
 |   brak.                                                                                           |
 | Argumenty:                                                                                        |
 |   multiplier - ile razy ma zostac wykonany obrot.                                                 |
 |   angle - kat o jaki ma zostac obrocony prostokat.                                                |
 | Zwraca:                                                                                           |
 |  Prostokat o zmienionym polozeniu za sprawa operacji obrotu.                                      |
 */

Cuboid Cuboid::Rotate_cub(Matrix3x3 const & mtx){
    Matrix3x3 temp = mtx;
    for(int i=0; i<CORNERS; ++i)
        Corners[i] = temp * Origin_Corners[i];
    return *this;
}

/*********************************************************************************************************************
 | Funkcja wykonujaca operacje przeciazenia operatora <<.                                                            |
 | Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych wierzcholka prostokata.       |
 | Warunki wstepne:                                                                                                  |
 |  & Strm- wybrany strumien musi byc typu ostream.                                                                  |
 |  & Rc - do poprawnego dzialania prostokat musi byc poprawnie zainicjowany wartosciami wspolrzednych wierzcholkow. |
 | Warunki koncowe:                                                                                                  |
 |   brak.                                                                                                           |
 | Argumenty:                                                                                                        |
 |   & Strm - Referencja do strumienia typu ostream, na ktory maja zostac wypisane wspolrzedne wektora.              |
 |   & Rc - Referencja do prostokata, ktorego wspolrzedne wierzcholkow maja zostac wpisane na wskazany strumien.     |
 | Zwraca:                                                                                                           |
 |   Wypisane wspolrzende wksazanego prostokata, w odpowiedniej formie na wskazane wyjscie.                          |
 */
std::ostream & operator << (std::ostream & Out, const Cuboid & Rc){
    for (int i=0; i<CORNERS;i++){
        Out << Rc[i] << std::endl;
        if(i%2==1)
            Out << std::endl;
    }
    return Out;
}

/***********************************************************************************************************************
 | Funkcja wykonujaca operacje przeciazenia operatora >>.                                                               |
 | Funkcja sluzy do wprowadzania wartosci wspolrzednych wierzcholkow prostokata ze wskazanego strumienia wejsciowego.   |
 | Warunki wstepne:                                                                                                     |
 |    Strm- wybrany strumien musi byc typu istream.                                                                     |
 |    Rc - do poprawnego dzialania prostokat musi byc wczesniej zainicjowany.                                           |
 | Warunki koncowe:                                                                                                     |
 |   brak;                                                                                                              |
 | Argumenty:                                                                                                           |
 |    Strm - Referencja do strumienia typu istream, z ktorego maja zostac wczytane wspolrzedne wierzcholkow prostokata. |
 |    Vec - Referencja do prostokata, do ktorego maja zostac wpisane podane wspolrzedne weirzcholkow.                   |
 | Zwraca:                                                                                                              |
 |   Wczytany obiekt- prostokat.                                                                                        |
 */
std::istream & operator >> (std::istream & In,Cuboid & Rc){
    for (int i=0; i<CORNERS;i++){
        In >> Rc[i];
    }
    return In;
}

/************************************************************************************************************
 | Metoda klasy Rectangle realizujaca zapis wartosci wspolrzednych wierzcholkow do pliku.                   | 
 | Warunki wstepne:                                                                                         |
 |   this - Do poprawnego dzialania prostokat musi byc zainicjowany wartosciami wzpolrzednych weirzcholkow  |
 |   *sNazwaPliku - do poprawnego dzialania wybrany napis stanowiacy nazwe musi być zgodny z nazwa          |
 |   pliku wskazanego programowi GNUplot.                                                                   |
 | Warunki koncowe:                                                                                         |
 |   brak;                                                                                                  |
 | Argumenty:                                                                                               |
 |    this - prostokat do zapisu.                                                                           |
 |   *sNazwaPliku - wskaznik na napis stanowiacy nazwe pliku wyjsciowego.                                   |
 | Zwraca:                                                                                                  |
 |   brak.                                                                                                  |
 */
void Cuboid::Write_cub_to_file(const char *sNazwaPliku) const{
  std::ofstream  StrmPlikowy;
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open()){
    throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
  }
  StrmPlikowy << *this;
  StrmPlikowy << Corners[0] << std::endl;
  StrmPlikowy << Corners[1] << std::endl;
  StrmPlikowy.close();
}

/***************************************************************************************************
 | Metoda klasy Rectangle wykonujaca operacje wyznaczenia dlugosic bokow prostokata i sprawdzenia, |
 |   czy przeciwlegle boki sa sobie rowne.                                                         |
 | Warunki wstepne:                                                                                |
 |   this - Do poprawnego dzialania prostokat musi byc zainicjowany wartosciami                    |
 |          reprezentujacym wzpolrzedne weirzcholkow                                               |
 | Warunki koncowe:                                                                                |
 |   brak;                                                                                         |
 | Argumenty:                                                                                      |
 |   this - prostokat, ktory ma zostac poddany sprawdzeniu.                                        |
 | Zwraca:                                                                                         |
 |   Wypisuje na standardowe wyjscie dane o bokach prostokata.                                     |
 */
void Cuboid::Is_it_cub() const{
    double a,b,c,d;
    a = sqrt(pow(Corners[1][0] - Corners[0][0],2) + pow(Corners[1][1] - Corners[0][1],2)); /* Wyliczenie dlugosci bokow prostokata */
    b = sqrt(pow(Corners[2][0] - Corners[1][0],2) + pow(Corners[2][1] - Corners[1][1],2));
    c = sqrt(pow(Corners[3][0] - Corners[2][0],2) + pow(Corners[3][1] - Corners[2][1],2));
    d = sqrt(pow(Corners[0][0] - Corners[3][0],2) + pow(Corners[0][1] - Corners[3][1],2));
    std::cout << std::endl;
    if(a - c < MAX_VALUE_DIFF && c - a < MAX_VALUE_DIFF){ /* Sprawdzenie spojnosci dlugosci przeciewleglych bokow */
        if(a == b && a == d && c == b && c == d)          /* Warunek generujacy komunikat, gdy badana figura to kwadrat */
            std::cout << ":) Przeciwlegle boki kwadratu sa sobie rowne." << std::endl;
        else if(a > b && a > d && c > b && c > d)         /* Ustalenie, ktore boki prostokata sa dluzsze, a ktore krotsze */
            std::cout << ":) Dluzsze przeciwlegle boki sa sobie rowne." << std::endl;
        else
            std::cout << ":) Krotsze przeciwlegle boki sa sobie rowne." << std::endl;
    }
    else{ 
        if(a >= b && a >= d && c >= b && c >= d)
            std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne." << std::endl;
        else
            std::cout << ":O Krotsze przeciwlegle boki nie sa sobie rowne." << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << a << std::endl; /* Wyswietlenie informacji o dl. bokow */
    std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << c << std::endl;
    std::cout << std::endl;
    
    if(b - d < MAX_VALUE_DIFF && d - b < MAX_VALUE_DIFF){
        if(a == b && a == d && c == b && c == d) 
            std::cout << ":) Przeciwlegle boki kwadratu sa sobie rowne." << std::endl;
        else if(b >= a && b >= c && d >= a && d >= c)
            std::cout << ":) Dluzsze przeciwlegle boki sa sobie rowne. "<< std::endl;
        else
            std::cout << ":) Krotsze przeciwlegle boki sa sobie rowne." << std::endl;
    }
    else{ 
        if(a >= b && a >= d && c >= b && c >= d)
            std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne." << std::endl;
        else
            std::cout << ":O  Krotsze przeciwlegle boki nie sa sobie rowne." << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << b << std::endl;
    std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << d << std::endl;
    std::cout << std::endl;
}

/****************************************************************************************************
 | Funkcja pomocnicza metody detekcji kolizji, sluzy do sprawdzenia orientacji polozenia 3 punktow. |
 | Warunki wstepne:                                                                                 |
 |   p,q,r - Do poprawnego dzialania wektory musza byc zainicjowane poprawnie wartosciami           |
 |           reprezentujacym wzpolrzedne weirzcholkow.                                              |
 | Warunki koncowe:                                                                                 |
 |   brak;                                                                                          |
 | Argumenty:                                                                                       |
 |   p,q,r - wektory, ktorym ma zostac wytyczony typ polozenia w przestrzeni.                       |
 | Zwraca:                                                                                          |
 |   funkcja zwraca wartosci typu int, okreslajace w jakim ulozeniu sa podane punkty:               |
 |   0 - gdy punkty ukladanja sie wspolliniowo.                                                     |
 |   1 - gdy punkty ukladaja sie w kierunku ruchu wskazowek zegara.                                 |
 |   2 - gdy punkty ukladaja sie w kierunku przeciwnym do ruchu wskazowek zegara.                   |
 */

int orientation(Vector<SIZE>const &p, Vector3D const &q, Vector3D const &r){
    int value = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (value == 0) return 0;  
    return (value > 0)? 1: 2;
}

/****************************************************************************************************
 | Funkcja pomocnicza metody detekcji kolizji, sluzy do sprawdzenia, czy punkt q lezy na odcingu pr.|
 | Warunki wstepne:                                                                                 |
 |   p,q,r - Do poprawnego dzialania wektory musza byc zainicjowane poprawnie wartosciami           |
 |           reprezentujacym wzpolrzedne weirzcholkow.                                              |
 | Warunki koncowe:                                                                                 |
 |   brak;                                                                                          |
 | Argumenty:                                                                                       |
 |   p,q,r - wektory, ktore zostana poddane sprawdzeniu.                                            |
 | Zwraca:                                                                                          |
 |   funkcja zwraca wartosci typu bool okreslajace, czy punkt q lezy na odcingu pr:                 |
 |   true - jesli punkt q lezy na odcinku pr.                                                       |
 |  false - jesli punkt q nie lezy na odcinku pr.                                                   |
 */

bool onSegment(Vector3D const &p, Vector3D const &q, Vector3D const &r){
    if (q[0] <= std::max(p[0], r[0]) && q[0] >= std::min(p[0], r[0]) && q[1] <= std::max(p[1], r[1]) && q[1] >= std::min(p[1], r[1]))
        return true;
    return false;
}

/****************************************************************************************************
 | Metoda klasy Rectangle sluzaca sprawdzeniu, czy wskazany prostokat wchodzi                       |
 |  w kolizje z innym prostokatem.                                                                  | 
 | Warunki wstepne:                                                                                 |
 |   this, ScRec - Do poprawnego dzialania prostokaty musza byc zainicjowane wartosciami            |
 |                 reprezentujacym wzpolrzedne weirzcholkow.                                        |
 | Warunki koncowe:                                                                                 |
 |   brak;                                                                                          |
 | Argumenty:                                                                                       |
 |   this - prostokat, ktorego kolizyjnosc sprawdzamy.                                              |
 |   ScRec - prostokat, ktory moze kolidowac z prostokatem "this".                                  |               
 | Zwraca:                                                                                          |
 |   funkcja zwraca wartosci typu bool okreslajace, czy prostokat ScRec koliduje z prostokatem this.|
 |   true - jesli dochodzi do kolzji                                                                |
 |   false - jesli nie dochodzi do kolizji                                                          |
 */
bool Cuboid::collision(Cuboid const &ScRec) const{
    Vector3D A1= Corners[0], B1= Corners[2], A2= ScRec[0], B2= ScRec[2], S1= (A1+B1)/2, S2= (A2+B2)/2;  /* Inicjalizacja wektorow reprezentujacych wiechcholki prostokatow i punkty ich srodkow */
    Vector3D  p1,p2,q1,q2; /* Inicjalizacja wektorow tymczasowych reprezentujacych wiechcholki prostokatow */ 
    int orts[4];
    double R1= sqrt(pow(B1[0] - S1[0],2) + pow(B1[1] - S1[1],2));
    double R2 = sqrt(pow(B2[0] - S2[0],2) + pow(B2[1] - S2[1],2));
    /* W celu zaoszczedzenia mocy obliczeniowej, pierwszym testem jest sprawdzenie, czy prostokaty leza wystarczajaco blisko siebie, aby moglo dojsc do kolizji */
    if(sqrt(pow(S1[0] - S2[0],2) + pow(S1[1] - S2[1],2)) > R1+R2)
        return false; /* Jesli prostokaty nie koliduja ze soba */
    else /* Jesli prostokaty znajduja sie w swoim zasiegu- circle colliders nachodza na siebie, rozwazane jest mozliwe przeciecie sie bokow prostokatow */
        for(int i=0;i<4;i++)
            for (int j=0;j<4;j++)
            {
                p1 = Corners[i]; q1 = Corners[(i + 1) == 4 ? 0 : i + 1]; /* Ustalanie odcinkow- bokow prostokatow */
                p2 = ScRec[j]; q2 = ScRec[(j + 1) == 4 ? 0 : j + 1];       
                orts[0] = orientation(p1, q1, p2);                       /* okreslenie 4 orientacji  */
                orts[1] = orientation(p1, q1, q2);
                orts[2] = orientation(p2, q2, p1);
                orts[3] = orientation(p2, q2, q1);
                /* Przypadek glowny */
                if (orts[0] != orts[1] && orts[2] != orts[3])        
                    return true;
                /* Przypadki szczegolne */
                if (orts[0] == 0 && onSegment(p1, p2, q1)) return true; /* p1, q1 i p2 sa wspolniowe i p2 lezy na odcinku p1q1 */
                if (orts[1]== 0 && onSegment(p1, q2, q1)) return true;  /* p1, q1 i q2 sa wspolniowe i q2 lezy na odcinku p1q1 */
                if (orts[2] == 0 && onSegment(p2, p1, q2)) return true; /* p2, q2 i p1 sa wspolniowe i p1 lezy na odcinku p2q2 */
                if (orts[3]== 0 && onSegment(p2, q1, q2)) return true;  /* p2, q2 i q1 sa wspolniowe i q1 lezy na odcinku p2q2 */
            }
    return false; /* Jesli prostokaty nie koliduja ze soba */
}