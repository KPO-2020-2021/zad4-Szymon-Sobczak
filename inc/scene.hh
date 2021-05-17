#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "vector.hh"
#include "matrix.hh"
#include "cuboid.hh"
#include "lacze_do_gnuplota.hh"


class Scene{
    private:
        std::vector <Cuboid> solid_figures;
        std::vector <Matrix3x3> Rotation_matrix;
        std::vector <Vector3D> Translation_vector;
        
    public:
        Scene();
        
        void Move_figure(unsigned int index);
        
        void update_matrix(Matrix3x3 const & mtx, unsigned int index);
        void update_vector(Vector3D const & vec,unsigned int index);
        
        Matrix3x3 get_matrix(unsigned int index);
        
        const Cuboid & operator [] (unsigned int index) const;
        //Cuboid & operator [] (unsigned int index);

        unsigned int how_many_cuboids();

        void Add_cuboid(Vector3D const & Apx0, Vector3D const & Apx5);
};
