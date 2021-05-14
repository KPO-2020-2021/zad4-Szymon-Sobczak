#include "../tests/doctest/doctest.h"
#include "matrix.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy Matrix"){
    Matrix Example;
    CHECK((Example(0,0)==0 && Example(0,1)==0 && Example(1,0)==0 && Example(1,1)==0));
}

TEST_CASE("Test konstrukora z argumentem dla klasy Matrix. Stworzenie macierzy 2x2"){ 
    Matrix Example[2][2];
    CHECK((sizeof(Example)/sizeof(Matrix)==4));
}

TEST_CASE("Test wczytywania do oraz odczytywania wartosci macierzy z uzyciem operatora funkcyjnego "){
    double values_M[2][2]={1,2,3,4};
    Matrix Example(values_M);
    CHECK((Example(0,0)==1 && Example(0,1)==2 && Example(1,0) ==3 && Example(1,1)==4));
}
 
TEST_CASE("Test metody klasy Matrix wypelnijacej ja odpowiednimi wartosciami funkcji tryg. dla podanego w stopniach kata"){
    Matrix Example;
    Example.Fill_matrix(90);
    CHECK((Example(0,0)>-MAX_VALUE_DIFF &&  Example(0,0) < MAX_VALUE_DIFF && Example(0,1)>-1-MAX_VALUE_DIFF 
          &&  Example(0,1) < -1 + MAX_VALUE_DIFF  && Example(1,0)>1-MAX_VALUE_DIFF &&  Example(1,0) < 1 + MAX_VALUE_DIFF 
          && Example(1,1)>-MAX_VALUE_DIFF &&  Example(1,1) < MAX_VALUE_DIFF));
}

TEST_CASE("Test wyswietlenia wartosci macierzy z uzyciem przeciazenia << "){
    double values_M[2][2]={1,2,3,4};
    Matrix Example(values_M);
    std::ostringstream out;
    out << Example;
    CHECK("| 1 | | 2 | | 3 | | 4 | " == out.str());
}

TEST_CASE("Test wczytywania wartosci do wektora z uzyciem przeciazenia >> "){
    Matrix Example;
    std::istringstream input("1 2 3 4");
    input >> Example;
    CHECK((Example(0,0)==1 && Example(0,1)==2 && Example(1,0)==3 && Example(1,1)==4));  
}

TEST_CASE("Test reakcji na wczytywanie wartosci nie bedacej typu double do macierzy z uzyciem przeciazenia >> "){
    Matrix Example;
    std::istringstream input("1 % 3 Z");
    WARN_THROWS(input >> Example);
}

TEST_CASE("Test mnozenia maceirzy i wektora przy pomocy przeciazenia operatora * "){
    double values_V[]={5,10}, values_M[2][2]={1,2,3,4};
    Vector Vec(values_V);
    Matrix Example(values_M);
    Vec=Example*Vec;
    CHECK((Vec[0]==25 && Vec[1]==55));
}

TEST_CASE("Test wyznaczenia wyznacznika macierzy z uzyciem metody 'determinant_of_the_matrix'"){
    double values[2][2] = {89,51,33,47};
    Matrix example_matrix(values);
    CHECK(example_matrix.determinant_of_the_matrix()==2500);
}

TEST_CASE("Test detekcji bledu wyznaczenia wyznacznika macierzy z uzyciem metody 'determinant_of_the_matrix', gdy w macierzy znajduje sie wartosc 0.0"){
    double values[2][2] = {0,51,33,47};
    Matrix example_matrix(values);
    WARN_THROWS(example_matrix.determinant_of_the_matrix());
}
     