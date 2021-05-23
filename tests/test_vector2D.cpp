#include "../tests/doctest/doctest.h"
#include "vector.hh"
#include "vector2D.hh"

TEST_CASE("Test odczytywania wartosci wektora2D z uzyciem operatora indeksowania."){
    double values[]={1,2},a,b;
    Vector2D Vec(values);
    a= Vec[0];
    b= Vec[1];
    CHECK((a==1 && b==2));
}
 
TEST_CASE("Test wpraowadzania wartosci do wektora2D z uzyciem operatora indeksowania."){ 
    Vector2D Vec;
    double a=7,b=15;
    Vec[0]=a;
    Vec[1]=b;
    CHECK((Vec[0]==7 && Vec[1]==15));
}

TEST_CASE("Test konstrukora bezparametrycznego dla klasy Vector2D."){
    Vector2D Vec;
    CHECK((Vec[0]==0 && Vec[1]==0));
}

TEST_CASE("Test konstrukora z argumentem dla klasy Vector2D."){
    double values[]={1,2};
    Vector2D Vec(values);
    CHECK((Vec[0]==1 && Vec[1]==2));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy odczytywaniu wartosci z wektora2D."){
    double values[]={1,2};
    Vector2D Vec(values);
    WARN_THROWS (Vec[-8]);
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy przypisywaniu wartosci do wektora2D."){
    double values[]={1,2};
    Vector2D Vec(values);
    WARN_THROWS (Vec[-8]=5);
}

TEST_CASE("Test wyswietlenia wartosci wektora2D z uzyciem przeciazenia <<."){
    double values[]={1,2};
    Vector2D Vec(values);
    std::ostringstream out;
    out << Vec;
    CHECK ("1.0000000000\t2.0000000000\t" == out.str());  
}

TEST_CASE("Test wczytywania wartosci do wektora2D z uzyciem przeciazenia >>."){
    Vector2D Vec;
    std::istringstream input("1 2");
    input >> Vec;
    CHECK ((Vec[0]==1 && Vec[1]==2));  
}

TEST_CASE("Test reakcji na wczytywanie wartosci nie bedacej typu double do wektora2D z uzyciem przeciazenia >>."){
    double values[]={1,2};
    Vector2D Vec(values);
    std::istringstream input("Z %");
    WARN_THROWS (input >> Vec);
}

TEST_CASE("Test dodawania dwoch wektorow przy pomocy przeciazenia operatora +."){
    double values1[]={1,2},values2[]={6,8};
    Vector2D Vec1(values1),Vec2(values2);
    Vec1=Vec1+Vec2;
    CHECK ((Vec1[0]==7 && Vec1[1]==10));  
}

TEST_CASE("Test odejmowania dwoch wektorow przy pomocy przeciazenia operatora -."){
    double values1[]={1,2},values2[]={6,8};
    Vector2D Vec1(values1),Vec2(values2);
    Vec1=Vec1-Vec2;
    CHECK ((Vec1[0]==-5 && Vec1[1]==-6));  
}

TEST_CASE("Test mnozenia wektora2D i liczby typu double przy pomocy przeciazenia operatora *."){
    double values1[]={1,2};
    Vector2D Vec1(values1);
    Vec1=Vec1*2;
    CHECK ((Vec1[0]==2 && Vec1[1]==4));  
}

TEST_CASE("Test dzielenia wektora2D przez liczbe typu double przy pomocy przeciazenia operatora /."){
    double values1[]={1,2};
    Vector2D Vec1(values1);
    Vec1=Vec1/2;
    CHECK ((Vec1[0]==0.5 && Vec1[1]==1));  
}

TEST_CASE("Test reakcji na dzielenie wektora2D przez 0."){
    double values1[]={1,2};
    Vector2D Vec1(values1);
    WARN_THROWS (Vec1=Vec1/0);
}

TEST_CASE("Test funkcji wyznaczajacej dlugosc odcinka pomiedzy dwoma wektorami w 2D."){
    double values1[]={1,2},values2[]={12,2};
    Vector2D Vec1(values1),Vec2(values2);
    CHECK (vector_length(Vec1,Vec2) == 11);
}