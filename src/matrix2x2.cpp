
#include "matrix2x2.hh"

Matrix2x2 Rotation_matrix_2x2 (double const angle){
    Matrix2x2 tmp;
    double angle_radians = angle * M_PI / 180.0;
    tmp(0,0) = cos(angle_radians);
    tmp(0,1) = -sin(angle_radians);
    tmp(1,0) = sin(angle_radians);
    tmp(1,1) = cos(angle_radians);
    return tmp;
}
