#include "../tests/doctest/doctest.h"
#include "rectangle.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy rectangle"){
    Cuboid Example;
    CHECK((Example[0][0]==0 && Example[0][1]==0 && Example[1][0]==0 && Example[1][1]==0 && 
          Example[2][0]==0 && Example[2][1]==0 && Example[3][0]==0 && Example[3][1]==0));
}

TEST_CASE("Test konstruktora wieloparametrowego dla klasy rectangle"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    CHECK((Example[0][0]==3 && Example[0][1]==1 && Example[1][0]==8 && Example[1][1]==1 && 
           Example[2][0]==8 && Example[2][1]==4 && Example[3][0]==3 && Example[3][1]==4));
}
 
TEST_CASE("Test wpraowadzania i odczytywania wartosci wierzcholkow prostokata z uzyciem operatora indeksowania "){
    Cuboid Example;
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Example[0]= A;
    Example[1]= B;
    Example[2]= C;
    Example[3]= D;
    CHECK((Example[0][0]==3 && Example[0][1]==1 && Example[1][0]==8 && Example[1][1]==1 && 
           Example[2][0]==8 && Example[2][1]==4 && Example[3][0]==3 && Example[3][1]==4));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy odczytywaniu wartosci z prostokata"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    WARN_THROWS((Example[15][0]==3 && Example[-9][1]==1));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy wprowadzaniu wartosci z prostokata"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example;
    WARN_THROWS((Example[-9]=A));
}

TEST_CASE("Test wyswietlania wartosci wektorow reprezentujacych polozenia wierzcholkow prostokata za pomoca przeciazenia operatora << "){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    std::ostringstream out;
    out << Example;
    CHECK(("3.0000000000\t1.0000000000\t\n8.0000000000\t1.0000000000\t\n8.0000000000\t4.0000000000\t\n3.0000000000\t4.0000000000\t\n"==out.str()));
}

TEST_CASE("Test zapisu inforamcji o wspolrzednych wierzcholkow prostokata do wskazanego pliku wraz ze sprawdzeniem ich porpawnosci"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    std::string test[10],pattern[10]= {"3.0000000000","1.0000000000", "8.0000000000", "1.0000000000", "8.0000000000","4.0000000000","3.0000000000","4.0000000000","3.0000000000","1.0000000000"};
    std::ifstream  StrmPlikowy;
    Example.Write_rec_to_file("../tests/datasets/test_rec.dat");
    StrmPlikowy.open("../tests/datasets/test_rec.dat");
    for (int i=0; i<10 ; i++){
        StrmPlikowy >> test[i];
        CHECK((pattern[i]==test[i]));
    }  
}

TEST_CASE("Test wczytywania wartosci do wektora z uzyciem przeciazenia >> "){
    Vector Vec;
    std::istringstream input("1 2");
    input >> Vec;
    CHECK ((Vec[0]==1 && Vec[1]==2));  
}

TEST_CASE("Test dzialania metody przesunieca prostokata o zadany wektor"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    double values[]={1,2};
    Vector Vec(values);
    Example.Translate_rec(Vec);
    CHECK((Example[0][0]==4 && Example[0][1]==3 && Example[1][0]==9 && Example[1][1]==3 && 
           Example[2][0]==9 && Example[2][1]==6 && Example[3][0]==4 && Example[3][1]==6));
}

TEST_CASE("Test dzialania metody obrotu prostokata o zadany kat, wybrana ilosc razy"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4}, angle= 90, mulitpier = 3;
    Vector A(X),B(Y),C(Z),D(U);
    Cuboid Example(A,B,C,D);
    double values[]={1,2};
    Vector Vec(values);
    Example.Rotate_rec(mulitpier,angle);
    CHECK((Example[0][0]>1-MAX_VALUE_DIFF && Example[0][0]<1+MAX_VALUE_DIFF &&
            Example[0][1]>-3-MAX_VALUE_DIFF && Example[0][1]<-3+MAX_VALUE_DIFF &&
            Example[1][0]>1-MAX_VALUE_DIFF && Example[1][0]<1+MAX_VALUE_DIFF &&
            Example[1][1]>-8-MAX_VALUE_DIFF && Example[1][1]<-8+MAX_VALUE_DIFF &&
            Example[2][0]>4-MAX_VALUE_DIFF && Example[2][0]<4+MAX_VALUE_DIFF &&
            Example[2][1]>-8-MAX_VALUE_DIFF && Example[2][1]<-8+MAX_VALUE_DIFF &&
            Example[3][0]>4-MAX_VALUE_DIFF && Example[3][0]<4+MAX_VALUE_DIFF &&
            Example[3][1]>-3-MAX_VALUE_DIFF && Example[3][1]<-3+MAX_VALUE_DIFF));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nachodzacych na siebie, równoległych do osi OX i OY."){
    double X[]={1,2}, Y[]={15,2}, Z[]={15,8}, U[]={1,8};
    Vector A(X),B(Y),C(Z),D(U);   
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");   

    double X2[]={4,5}, Y2[]={17,5}, Z2[]={17,11}, U2[]={4,11}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   

    CHECK((Rec.collision(Rec2)==true));
    CHECK((Rec2.collision(Rec)==true));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nie nachodzacych na siebie, równoległych do osi OX i OY."){
    double X[]={1,2}, Y[]={15,2}, Z[]={15,8}, U[]={1,8};
    Vector A(X),B(Y),C(Z),D(U);   
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");   

    double X2[]={16,8}, Y2[]={28,8}, Z2[]={28,14}, U2[]={16,14}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");  

    CHECK((Rec.collision(Rec2)==false));
    CHECK((Rec2.collision(Rec)==false));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nie nachodzacych na siebie, nachylonych pod tym samym katem 45 stopni."){
    double X[]={0,1.41}, Y[]={5.66,7.07}, Z[]={-0.71,13.44}, U[]={-6.36,7.78};
    Vector A(X),B(Y),C(Z),D(U);  
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");    
    double X2[]={4.24,9.9}, Y2[]={6.36,7.78}, Z2[]={9.19,10.61}, U2[]={7.07,12.73}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   
    CHECK((Rec.collision(Rec2)==false));
    CHECK((Rec2.collision(Rec)==false));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nachodzacych na siebie, gdzie 1 jest nachylony pod katem 45 stopni a 2 rownolegly do osi OX i OY nachylonych pod rozynmi katami."){
    double X[]={-0.71,2.12},Y[]={9.19,12.02}, Z[]={4.95,16.26}, U[]={-4.95,6.36};
    Vector A(X),B(Y),C(Z),D(U);  
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");    
    double X2[]={6,12}, Y2[]={6,6}, Z2[]={14,6}, U2[]={14,12}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   
    CHECK((Rec.collision(Rec2)==true));
    CHECK((Rec2.collision(Rec)==true));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nachodzacych na siebie, stycznych 1 bokiem "){
    double X[]={1,2}, Y[]={15,2}, Z[]={15,8}, U[]={1,8};
    Vector A(X),B(Y),C(Z),D(U); 
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");    
    double X2[]={15,2}, Y2[]={20,2}, Z2[]={20,8}, U2[]={15,8}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   
    CHECK((Rec.collision(Rec2)==true));
    CHECK((Rec2.collision(Rec)==true));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność prostokątów nachodzacych na siebie, stycznych 1 wierzcholkiem "){
    double X[]={1,2}, Y[]={15,2}, Z[]={15,8}, U[]={1,8};
    Vector A(X),B(Y),C(Z),D(U);  
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");    
    double X2[]={15,8}, Y2[]={22,8}, Z2[]={22,14}, U2[]={15,14}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   
    CHECK((Rec.collision(Rec2)==true));
    CHECK((Rec2.collision(Rec)==true));
}

TEST_CASE("Test dzialania metody sprawdzającej kolizyjność takich samych prostokątów nachodzacych na siebie w calosci "){
    double X[]={1,2}, Y[]={15,2}, Z[]={15,8}, U[]={1,8};
    Vector A(X),B(Y),C(Z),D(U);  
    Cuboid Rec(A,B,C,D);  
    Rec.Write_rec_to_file("../tests/datasets/coll_rec1.dat");    
    double X2[]={1,2}, Y2[]={15,2}, Z2[]={15,8}, U2[]={1,8}; 
    Vector A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Rec2(A2,B2,C2,D2);   
    Rec2.Write_rec_to_file("../tests/datasets/coll_rec2.dat");   
    CHECK((Rec.collision(Rec2)==true));
    CHECK((Rec2.collision(Rec)==true));
}
