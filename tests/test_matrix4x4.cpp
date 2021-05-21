#include "../tests/doctest/doctest.h"
#include "matrix.hh"
#include "matrix4x4.hh"
#include "vector3D.hh"

TEST_CASE("Test funkcji poprzez przekazanie na strumien, wypelnijacej macierz4x4 wartosciami macierzy polaczonego obrotu w osiach OX, OY i OZ i translacji o wektor"){
    double val_translation[3]={10,20,30};
    Matrix4x4 Example;
    Vector3D translation(val_translation);
    std::ostringstream out;
    Example = Fill_combined_matrix_4x4(90,60,30,translation);
    out << Example;
    CHECK(" 0.4330127019\t 0.7500000000\t 0.5000000000\t 10.0000000000\t 0.2500000000\t 0.4330127019\t -0.8660254038\t 20.0000000000\t -0.8660254038\t 0.5000000000\t 0.0000000000\t 30.0000000000\t 0.0000000000\t 0.0000000000\t 0.0000000000\t 1.0000000000\t" == out.str());
}

