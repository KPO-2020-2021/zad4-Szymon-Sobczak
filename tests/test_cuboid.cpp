#include "../tests/doctest/doctest.h"
#include "cuboid.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy cuboid"){
    Cuboid Example;
    CHECK(( Example[0][0]==0 && Example[0][1]==0 &&  Example[0][2]==0 &&
            Example[1][0]==0 && Example[1][1]==0 &&  Example[1][2]==0 &&
            Example[2][0]==0 && Example[2][1]==0 &&  Example[2][2]==0 &&
            Example[3][0]==0 && Example[3][1]==0 &&  Example[3][2]==0 &&
            Example[4][0]==0 && Example[4][1]==0 &&  Example[4][2]==0 &&
            Example[5][0]==0 && Example[5][1]==0 &&  Example[5][2]==0 &&
            Example[6][0]==0 && Example[6][1]==0 &&  Example[6][2]==0 &&
            Example[7][0]==0 && Example[7][1]==0 &&  Example[7][2]==0));
}

TEST_CASE("Test konstrukora bezparametrowego dla klasy cuboid"){
    double apx1[3]={1,2,3},apx2[3]={1,2,3},apx3[3]={1,2,3},apx4[3]={1,2,3},apx5[3]={1,2,3},apx6[3]={1,2,3},apx7[3]={1,2,3},apx8[3]={1,2,3}, center[3]={20,30,40};
    Vector3D v_Apx1(apx1),v_Apx2(apx2),v_Apx3(apx3),v_Apx4(apx4),v_Apx5(apx5),v_Apx6(apx6),v_Apx7(apx7),v_Apx8(apx8);
    Cuboid Example;
    CHECK(( Example[0][0]==0 && Example[0][1]==0 &&  Example[0][2]==0 &&
            Example[1][0]==0 && Example[1][1]==0 &&  Example[1][2]==0 &&
            Example[2][0]==0 && Example[2][1]==0 &&  Example[2][2]==0 &&
            Example[3][0]==0 && Example[3][1]==0 &&  Example[3][2]==0 &&
            Example[4][0]==0 && Example[4][1]==0 &&  Example[4][2]==0 &&
            Example[5][0]==0 && Example[5][1]==0 &&  Example[5][2]==0 &&
            Example[6][0]==0 && Example[6][1]==0 &&  Example[6][2]==0 &&
            Example[7][0]==0 && Example[7][1]==0 &&  Example[7][2]==0));
}
