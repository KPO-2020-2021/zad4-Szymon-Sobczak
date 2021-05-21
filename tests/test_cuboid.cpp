#include "../tests/doctest/doctest.h"
#include "cuboid.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy cuboid i przeciazenia operatora indeksujacego i funkcyjnego sluzacego odczytywaniu wartosci wierzcholkow globalnych i lokalnych z prostopadloscianu"){
Cuboid Example;
    CHECK(( Example(0)[0]==0 && Example(0)[1]==0 &&  Example(0)[2]==0 &&
            Example(1)[0]==0 && Example(1)[1]==0 &&  Example(1)[2]==0 &&
            Example(2)[0]==0 && Example(2)[1]==0 &&  Example(2)[2]==0 &&
            Example(3)[0]==0 && Example(3)[1]==0 &&  Example(3)[2]==0 &&
            Example(4)[0]==0 && Example(4)[1]==0 &&  Example(4)[2]==0 &&
            Example(5)[0]==0 && Example(5)[1]==0 &&  Example(5)[2]==0 &&
            Example(6)[0]==0 && Example(6)[1]==0 &&  Example(6)[2]==0 &&
            Example(7)[0]==0 && Example(7)[1]==0 &&  Example(7)[2]==0));

    CHECK(( Example[0][0]==0 && Example[0][1]==0 &&  Example[0][2]==0 &&
            Example[1][0]==0 && Example[1][1]==0 &&  Example[1][2]==0 &&
            Example[2][0]==0 && Example[2][1]==0 &&  Example[2][2]==0 &&
            Example[3][0]==0 && Example[3][1]==0 &&  Example[3][2]==0 &&
            Example[4][0]==0 && Example[4][1]==0 &&  Example[4][2]==0 &&
            Example[5][0]==0 && Example[5][1]==0 &&  Example[5][2]==0 &&
            Example[6][0]==0 && Example[6][1]==0 &&  Example[6][2]==0 &&
            Example[7][0]==0 && Example[7][1]==0 &&  Example[7][2]==0));
}

TEST_CASE("Test konstrukora wieloparametrycznego dla klasy cuboid"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);
    
    
    CHECK(( Example(0)[0]==-20 && Example(0)[1]==-15 &&  Example(0)[2]==-10 &&
            Example(1)[0]==20 && Example(1)[1]==-15 &&  Example(1)[2]== -10 &&
            Example(2)[0]==-20 && Example(2)[1]==15 &&  Example(2)[2]==-10 &&
            Example(3)[0]==20 && Example(3)[1]==15 &&  Example(3)[2]==-10 &&
            Example(4)[0]==-20 && Example(4)[1]==15 &&  Example(4)[2]==10 &&
            Example(5)[0]==20 && Example(5)[1]==15 &&  Example(5)[2]==10 &&
            Example(6)[0]==-20 && Example(6)[1]==-15 &&  Example(6)[2]==10 &&
            Example(7)[0]==20 && Example(7)[1]==-15 &&  Example(7)[2]==10));
    
    CHECK(( Example[0][0]==30 && Example[0][1]==45 &&  Example[0][2]==30 &&
            Example[1][0]==70 && Example[1][1]==45 &&  Example[1][2]==30 &&
            Example[2][0]==30 && Example[2][1]==75 &&  Example[2][2]==30 &&
            Example[3][0]==70 && Example[3][1]==75 &&  Example[3][2]==30 &&
            Example[4][0]==30 && Example[4][1]==75 &&  Example[4][2]==50 &&
            Example[5][0]==70 && Example[5][1]==75 &&  Example[5][2]==50 &&
            Example[6][0]==30 && Example[6][1]==45 &&  Example[6][2]==50 &&
            Example[7][0]==70 && Example[7][1]==45 &&  Example[7][2]==50));
}

TEST_CASE("Test wyswietlenia wartosci globalnych prostopadloscianu z uzyciem przeciazenia <<."){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);
    std::ostringstream out;
    out << Example;
    CHECK ("30.0000000000\t45.0000000000\t30.0000000000\t\n70.0000000000\t45.0000000000\t30.0000000000\t\n\n30.0000000000\t75.0000000000\t30.0000000000\t\n70.0000000000\t75.0000000000\t30.0000000000\t\n\n30.0000000000\t75.0000000000\t50.0000000000\t\n70.0000000000\t75.0000000000\t50.0000000000\t\n\n30.0000000000\t45.0000000000\t50.0000000000\t\n70.0000000000\t45.0000000000\t50.0000000000\t\n\n" == out.str());  
}


TEST_CASE("Test przypiywania wratosci wektorow3D do tablicy wektorow reprezentujacych wspolrzedne globalne prostopadloscianu, przy uzyciu przeciazenia operatora indeksujacego"){
    Cuboid Example;
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8);
    
    Example[0] = v_Apx1;
    Example[1] = v_Apx2;
    Example[2] = v_Apx3;
    Example[3] = v_Apx4;
    Example[4] = v_Apx5;
    Example[5] = v_Apx6;
    Example[6] = v_Apx7;
    Example[7] = v_Apx8;

    CHECK(( Example[0][0]==-20 && Example[0][1]==-15 &&  Example[0][2]==-10 &&
            Example[1][0]==20 && Example[1][1]==-15 &&  Example[1][2]== -10 &&
            Example[2][0]==-20 && Example[2][1]==15 &&  Example[2][2]==-10 &&
            Example[3][0]==20 && Example[3][1]==15 &&  Example[3][2]==-10 &&
            Example[4][0]==-20 && Example[4][1]==15 &&  Example[4][2]==10 &&
            Example[5][0]==20 && Example[5][1]==15 &&  Example[5][2]==10 &&
            Example[6][0]==-20 && Example[6][1]==-15 &&  Example[6][2]==10 &&
            Example[7][0]==20 && Example[7][1]==-15 &&  Example[7][2]==10));
}

TEST_CASE("Test funkcji porownujacej zadane cztery dlugosci w celu stwierdzenia, czy sa spojne. Test, gdy dlugosci sa takie same. "){
    double sides[4]={50,50,50,50};
    CHECK((are_sides_equal(sides)));
}

TEST_CASE("Test funkcji porownujacej zadane cztery dlugosci w celu stwierdzenia, czy sa spojne. Test, gdy dlugosci nie sa takie same. "){
    double sides[4]={50,40,50,900};
    CHECK(!(are_sides_equal(sides)));
}


TEST_CASE("Test metody obracjacej lokalnie i przesuwajacej o wektor globalnie prostopaloscian. Obrot o 90 stopni w osi OX"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);

    Vector3D translation;

    Example.Move_cuboid(translation,Fill_matrix_OX(90));

    CHECK(( Example[0][0]==30 && Example[0][1]==70 &&  Example[0][2]==25 &&
            Example[1][0]==70 && Example[1][1]==70 &&  Example[1][2]==25 &&
            Example[2][0]==30 && Example[2][1]==70 &&  Example[2][2]==55 &&
            Example[3][0]==70 && Example[3][1]==70 &&  Example[3][2]==55 &&
            Example[4][0]==30 && Example[4][1]==50 &&  Example[4][2]==55 &&
            Example[5][0]==70 && Example[5][1]==50 &&  Example[5][2]==55 &&
            Example[6][0]==30 && Example[6][1]==50 &&  Example[6][2]==25 &&
            Example[7][0]==70 && Example[7][1]==50 &&  Example[7][2]==25));
}

TEST_CASE("Test metody obracjacej lokalnie i przesuwajacej o wektor globalnie prostopaloscian. Obrot o 90 stopni w osi OY"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);

    Vector3D translation;

    Example.Move_cuboid(translation,Fill_matrix_OY(90));

    CHECK(( Example[0][0]==40 && Example[0][1]==45 &&  Example[0][2]==60 &&
            Example[1][0]==40 && Example[1][1]==45 &&  Example[1][2]==20 &&
            Example[2][0]==40 && Example[2][1]==75 &&  Example[2][2]==60 &&
            Example[3][0]==40 && Example[3][1]==75 &&  Example[3][2]==20 &&
            Example[4][0]==60 && Example[4][1]==75 &&  Example[4][2]==60&&
            Example[5][0]==60 && Example[5][1]==75 &&  Example[5][2]==20 &&
            Example[6][0]==60 && Example[6][1]==45 &&  Example[6][2]==60 &&
            Example[7][0]==60 && Example[7][1]==45 &&  Example[7][2]==20));
}

TEST_CASE("Test metody obracjacej lokalnie i przesuwajacej o wektor globalnie prostopaloscian. Obrot o 90 stopni w osi OZ"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);

    Vector3D translation;

    Example.Move_cuboid(translation,Fill_matrix_OZ(90));

    CHECK(( Example[0][0]==65 && Example[0][1]==40 &&  Example[0][2]==30 &&
            Example[1][0]==65 && Example[1][1]==80 &&  Example[1][2]==30 &&
            Example[2][0]==35 && Example[2][1]==40 &&  Example[2][2]==30 &&
            Example[3][0]==35 && Example[3][1]==80 &&  Example[3][2]==30 &&
            Example[4][0]==35 && Example[4][1]==40 &&  Example[4][2]==50 &&
            Example[5][0]==35 && Example[5][1]==80 &&  Example[5][2]==50 &&
            Example[6][0]==65 && Example[6][1]==40 &&  Example[6][2]==50 &&
            Example[7][0]==65 && Example[7][1]==80 &&  Example[7][2]==50));
}

TEST_CASE("Test metody obracjacej lokalnie i przesuwajacej o wektor globalnie prostopaloscian. Translacja o wektor (20,-20,30)"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);

    double translation_values[3] = {20,-20,30};
    Vector3D translation(translation_values);

    Matrix3x3 Unit_matrix;

    Example.Move_cuboid(translation,Unit_matrix);

    CHECK(( Example[0][0]==50 && Example[0][1]==25 &&  Example[0][2]==60 &&
            Example[1][0]==90 && Example[1][1]==25 &&  Example[1][2]==60 &&
            Example[2][0]==50 && Example[2][1]==55 &&  Example[2][2]==60 &&
            Example[3][0]==90 && Example[3][1]==55 &&  Example[3][2]==60 &&
            Example[4][0]==50 && Example[4][1]==55 &&  Example[4][2]==80 &&
            Example[5][0]==90 && Example[5][1]==55 &&  Example[5][2]==80 &&
            Example[6][0]==50 && Example[6][1]==25 &&  Example[6][2]==80 &&
            Example[7][0]==90 && Example[7][1]==25 &&  Example[7][2]==80));
}


TEST_CASE("Test metody obracjacej lokalnie i przesuwajacej o wektor globalnie prostopaloscian. Zlozenie obrotu o 90 stopni w osi OX i translacji o wektor (50, 30, -50)"){
    double apx1[3]={-20,-15,-10}, apx2[3]={20,-15,-10}, apx3[3]={-20,15,-10}, apx4[3]={20,15,-10}, apx5[3]={-20,15,10}, 
    apx6[3]={20,15,10}, apx7[3]={-20,-15,10}, apx8[3]={20,-15,10}, center[3]={50,60,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8),v_center(center);
    Cuboid Example(v_Apx1,v_Apx2,v_Apx3,v_Apx4,v_Apx5,v_Apx6,v_Apx7,v_Apx8,v_center);

    double translation_values[3] = {50,30,-50};

    Vector3D translation(translation_values);

    Example.Move_cuboid(translation,Fill_matrix_OX(90));

    CHECK(( Example[0][0]==80 && Example[0][1]==100 &&  Example[0][2]==-25 &&
            Example[1][0]==120 && Example[1][1]==100 &&  Example[1][2]== -25 &&
            Example[2][0]==80 && Example[2][1]==100 &&  Example[2][2]==5 &&
            Example[3][0]==120 && Example[3][1]==100 &&  Example[3][2]==5 &&
            Example[4][0]==80 && Example[4][1]==80 &&  Example[4][2]==5 &&
            Example[5][0]==120 && Example[5][1]==80 &&  Example[5][2]==5 &&
            Example[6][0]==80 && Example[6][1]==80 &&  Example[6][2]==-25 &&
            Example[7][0]==120 && Example[7][1]==80 &&  Example[7][2]==-25));
}
