#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector.hh"
#include "matrix.hh"
#include "cuboid.hh"
#include "lacze_do_gnuplota.hh"


class Scene{
    private:
        Cuboid solid_figures[NBR_OF_FIGURES];
        Matrix3x3 Rotation_matrix;
        Vector3D Translation_vector;
    public:
        Scene(unsigned int number_of_cuboids);
        Scene Move_figure(unsigned int cuboid_number);
        
        Matrix3x3 get_matrix();
        void update_matrix(Matrix3x3 const & mtx);
        void update_vector(Vector3D const & vec);
        const Cuboid & operator [] (unsigned int index) const;
        Cuboid & operator [] (unsigned int index);
};
