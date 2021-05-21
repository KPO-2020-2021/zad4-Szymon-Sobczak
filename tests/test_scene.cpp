#include "../tests/doctest/doctest.h"
#include "scene.hh"


TEST_CASE("Test metody dodajacej do sceny nowy prostopadloscian, oraz test przeciazania operatora indeksowania sluzacego do podgladania wartosci wierzcholkow prospoadloscianow zawarych w scenie."){
    Scene Example;
    
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
 
    CHECK(( Example[0](0)[0]==-20 && Example[0](0)[1]==-15 &&  Example[0](0)[2]==-10 &&
            Example[0](1)[0]==20 && Example[0](1)[1]==-15 &&  Example[0](1)[2]== -10 &&
            Example[0](2)[0]==-20 && Example[0](2)[1]==15 &&  Example[0](2)[2]==-10 &&
            Example[0](3)[0]==20 && Example[0](3)[1]==15 &&  Example[0](3)[2]==-10 &&
            Example[0](4)[0]==-20 && Example[0](4)[1]==15 &&  Example[0](4)[2]==10 &&
            Example[0](5)[0]==20 && Example[0](5)[1]==15 &&  Example[0](5)[2]==10 &&
            Example[0](6)[0]==-20 && Example[0](6)[1]==-15 &&  Example[0](6)[2]==10 &&
            Example[0](7)[0]==20 && Example[0](7)[1]==-15 &&  Example[0](7)[2]==10));

    
    CHECK(( Example[0][0][0]==30 && Example[0][0][1]==45 &&  Example[0][0][2]==30 &&
            Example[0][1][0]==70 && Example[0][1][1]==45 &&  Example[0][1][2]==30 &&
            Example[0][2][0]==30 && Example[0][2][1]==75 &&  Example[0][2][2]==30 &&
            Example[0][3][0]==70 && Example[0][3][1]==75 &&  Example[0][3][2]==30 &&
            Example[0][4][0]==30 && Example[0][4][1]==75 &&  Example[0][4][2]==50 &&
            Example[0][5][0]==70 && Example[0][5][1]==75 &&  Example[0][5][2]==50 &&
            Example[0][6][0]==30 && Example[0][6][1]==45 &&  Example[0][6][2]==50 &&
            Example[0][7][0]==70 && Example[0][7][1]==45 &&  Example[0][7][2]==50));
}


TEST_CASE("Test reakcji metody przeciazania operatora indeksowania mna bledny indeks prostopadloscianu."){
    Scene Example;
    
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
 
    WARN_THROWS((Example[-11](0)[0]==-20));
           
}

TEST_CASE("Test metody pozwalajacej odczytac wartosci macierzy rotacji dla wskazanego prostopaloscianu"){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    Matrix3x3 Unit_matrix;
    CHECK((Example.get_matrix(0)==Unit_matrix));
}

TEST_CASE("Test reakcji metody pozwalajacej odczytac wartosci macierzy rotacji dla wskazanego prostopaloscianu na podanie blednego indeksu prostopaldoscianu"){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    Matrix3x3 Unit_matrix;
    WARN_THROWS((Example.get_matrix(-9)==Unit_matrix));
}

TEST_CASE("Test metody pozwalajacej na skladanie kolejnych macierzy rotacji dla wskazanego prostopadloscianu. Obrot w osi OX o 90 stopni"){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    double Values[3][3]= {1,0,0,0,0,-1,0,1,0};
    Matrix3x3 Result_matrix(Values);
    Example.update_matrix(Fill_matrix_OX(90),0);
    CHECK((Example.get_matrix(0) == Result_matrix));
}


TEST_CASE("Test metody pozwalajacej odczytac wartosci wektora translacji dla wskazanego prostopaloscianu"){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    Matrix3x3 Unit_matrix;
    CHECK((Example.get_vector(0)[0]==0 && Example.get_vector(0)[1]==0 && Example.get_vector(0)[2]==0));
}

TEST_CASE("Test reakcji metody pozwalajacej odczytac wartosci wektora translacji dla wskazanego prostopaloscianu na podanie blednego indeksu prostopaldoscianu" ){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    Matrix3x3 Unit_matrix;
    WARN_THROWS((Example.get_vector(-6)[0]==0 && Example.get_vector(-6)[1]==0 && Example.get_vector(-6)[2]==0));
}

TEST_CASE("Test metody pozwalajacej na skladanie kolejnych wektorow translacji dla wskazanego prostopadloscianu"){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);
    double Values[3] = {1,2,3};
    Vector3D Translation_vector(Values);
    Example.update_vector(Translation_vector,0);
    CHECK((Example.get_vector(0)[0]==1 && Example.get_vector(0)[1]==2 && Example.get_vector(0)[2]==3));
}

TEST_CASE("Test metody okreslajacej ile prostopadloscianow znajduje sie obecnie na scenie. Przypadek sceny pustej"){
    Scene Example;
    CHECK((Example.how_many_cuboids()==0));
}


TEST_CASE("Test metody okreslajacej ile prostopadloscianow znajduje sie obecnie na scenie. Przypadek sceny zawierajacej 2 prostopadlosciany"){
    Scene Example;
    double center_val1[]={50,60,40},center_val2[]={60,70,30}; 
    Vector3D A(center_val1),B(center_val2);
    Example.Add_cuboid(A,40,30,20);
    Example.Add_cuboid(B,10,20,50);
    CHECK((Example.how_many_cuboids()==2));
}

TEST_CASE("Test metody pozwalajacej na przemieszczenie globalne figury na scenie. Rotacja o "){
    Scene Example;
    double center_val[]={50,60,40}; 
    Vector3D A(center_val);
    Example.Add_cuboid(A,40,30,20);

    
    double translation_values[3] = {50,30,-50};

    Vector3D Translation_vector(translation_values);
    
    Example.update_vector(Translation_vector,0);

    Example.update_matrix(Fill_matrix_OX(90),0);

    Example.Move_figure(0);

    CHECK(( Example[0][0][0]==80 && Example[0][0][1]==100 &&  Example[0][0][2]==-25 &&
            Example[0][1][0]==120 && Example[0][1][1]==100 &&  Example[0][1][2]== -25 &&
            Example[0][2][0]==80 && Example[0][2][1]==100 &&  Example[0][2][2]==5 &&
            Example[0][3][0]==120 && Example[0][3][1]==100 &&  Example[0][3][2]==5 &&
            Example[0][4][0]==80 && Example[0][4][1]==80 &&  Example[0][4][2]==5 &&
            Example[0][5][0]==120 && Example[0][5][1]==80 &&  Example[0][5][2]==5 &&
            Example[0][6][0]==80 && Example[0][6][1]==80 &&  Example[0][6][2]==-25 &&
            Example[0][7][0]==120 && Example[0][7][1]==80 &&  Example[0][7][2]==-25));
}


