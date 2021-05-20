#include "../tests/doctest/doctest.h"
#include "matrix.hh"
#include "matrix2x2.hh"
#include "vector2D.hh"

TEST_CASE("Test konstrukora bezparametrycznego dla klasy Matrix2x2."){
    Matrix2x2 Example;
    CHECK((Example(0,0)==1 && Example(0,1)==0 && Example(1,0)==0 && Example(1,1)==1));
}

TEST_CASE("Test konstrukora z argumentem dla klasy Matrix2x2. Stworzenie macierzy2x2."){ 
    Matrix2x2 Example[2][2];
    CHECK((sizeof(Example)/sizeof(Matrix2x2)==4));
}

TEST_CASE("Test wczytywania do oraz odczytywania wartosci macierzy2x2 z uzyciem operatora funkcyjnego."){
    double values_M[2][2]={1,2,3,4};
    Matrix2x2 Example(values_M);
    CHECK((Example(0,0)==1 && Example(0,1)==2 && Example(1,0) ==3 && Example(1,1)==4));
}
 
TEST_CASE("Test funkcji wypelnijacej macierz2x2 odpowiednimi wartosciami funkcji tryg. dla podanego w stopniach kata."){
    Matrix2x2 Example;
    Example = Rotation_matrix_2x2(90);
    CHECK((Example(0,0)>-MAX_VALUE_DIFF &&  Example(0,0) < MAX_VALUE_DIFF && Example(0,1)>-1-MAX_VALUE_DIFF 
          &&  Example(0,1) < -1 + MAX_VALUE_DIFF  && Example(1,0)>1-MAX_VALUE_DIFF &&  Example(1,0) < 1 + MAX_VALUE_DIFF 
          && Example(1,1)>-MAX_VALUE_DIFF &&  Example(1,1) < MAX_VALUE_DIFF));
}

TEST_CASE("Test wyswietlenia wartosci macierzy2x2 z uzyciem przeciazenia <<."){
    double values_M[2][2]={1,2,3,4};
    Matrix2x2 Example(values_M);
    std::ostringstream out;
    out << Example;
    CHECK(" 1.0000000000\t 2.0000000000\t 3.0000000000\t 4.0000000000\t" == out.str());
}

TEST_CASE("Test wczytywania wartosci do macierzy2x2 z uzyciem przeciazenia >>."){
    Matrix2x2 Example;
    std::istringstream input("1 2 3 4");
    input >> Example;
    CHECK((Example(0,0)==1 && Example(0,1)==2 && Example(1,0)==3 && Example(1,1)==4));  
}

TEST_CASE("Test reakcji na wczytywanie wartosci nie bedacej typu double do macierzy2x2 z uzyciem przeciazenia >>."){
    Matrix2x2 Example;
    std::istringstream input("1 % 3 Z");
    WARN_THROWS(input >> Example);
}

TEST_CASE("Test mnozenia macierzy2x2 i wektora przy pomocy przeciazenia operatora *."){
    double values_V[]={5,10}, values_M[2][2]={1,2,3,4};
    Vector2D Vec(values_V);
    Matrix2x2 Example(values_M);
    Vec=Example*Vec;
    CHECK((Vec[0] == 25 && Vec[1] == 55));
}

TEST_CASE("Test mnozenia macierzy2x2 i macierzy2x2 przy pomocy przeciazenia operatora *."){
    double values_M1[2][2]={1,2,3,4},values_M2[2][2]={9,5,3,2};
    Matrix2x2 Example1(values_M1),Example2(values_M2),Result;
    Result = Example1 * Example2;
    CHECK((Result(0,0) == 15 && Result(0,1) == 9 && Result(1,0) == 39 && Result(1,1) == 23));
}

TEST_CASE("Test dzielenia macierzy2x2 przez skalar przy pomocy przeciazenia operatora /."){
    double values_M1[2][2]={4,6,8,12};
    Matrix2x2 Example1(values_M1);
    Example1 = Example1 / 2;
    CHECK((Example1(0,0) == 2 && Example1(0,1) == 3 && Example1(1,0) == 4 && Example1(1,1) == 6));
}

TEST_CASE("Test reakcji metody przeciazenia operatora / na dzielenie macierzy przez zero. "){
    double values_M1[2][2]={4,6,8,12};
    Matrix2x2 Example1(values_M1);
    WARN_THROWS(Example1 = Example1 / 0);
}

TEST_CASE("Test dodawania dwoch macierzy2D przy pomocy przeciazenia operatora +."){
    double values_M1[2][2]={4,6,8,12},values_M2[2][2]={6,4,2,-2};
    Matrix2x2 Example1(values_M1),Example2(values_M2),Result;
    Result = Example1 + Example2;
    CHECK((Result(0,0) == 10 && Result(0,1) == 10 && Result(1,0) == 10 && Result(1,1) == 10));
}

TEST_CASE("Test porownania dwoch takich samych macierzy z uzyciem przeciazenia operatora porowania ==."){
    double values_M1[2][2]={1,2,3,4};
    Matrix2x2 Example1(values_M1),Example2(values_M1);
    CHECK((Example1==Example2));
}

TEST_CASE("Test porownania dwoch roznych macierzy z uzyciem przeciazenia operatora porowania ==."){
    double values_M1[2][2]={1,2,3,4},values_M2[2][2]={1,5,7,4};
    Matrix2x2 Example1(values_M1),Example2(values_M2);
    CHECK(!(Example1==Example2));
}

TEST_CASE("Test funkcji wypelniajacej macierz2D wartosciami macierzy obrotu dla zadanego kata, poprzez porownanie, z uzyciem przeciazenia operatora porownania, iloczynu dwoch macierzy dla przeciwnych katow."){
    Matrix2x2 Example1, Example2, Result, Unit_matrix;
    Example1 = Rotation_matrix_2x2(50);
    Example2 = Rotation_matrix_2x2(-50);
    Result = Example1 * Example2;
    CHECK((Result == Unit_matrix));
}

TEST_CASE("Test dzialania metody przywracajacej dowolna macierz do postaci macierzy jednostkowej."){
    double values_M1[2][2]={1,2,3,4};
    Matrix2x2 Example1(values_M1),Unit_matrix;
    Example1.reset_matrix();
    CHECK((Example1==Unit_matrix));
}