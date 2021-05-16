#include "scene.hh"

Scene::Scene(){
    double Apx1[]={2,3,3},Apx6[]={22,18,28};
    Vector3D A(Apx1), B(Apx6);
    Add_cuboid(A,B);
}

const Cuboid & Scene::operator [] (unsigned int index) const{
    if (index>=NBR_OF_FIGURES)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures.at(index);
}

 Cuboid & Scene::operator [] (unsigned int index){
    if (index>=NBR_OF_FIGURES)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures.at(index);
}

Matrix3x3 Scene::get_matrix(unsigned int index){
    return Rotation_matrix.at(index);
}

void Scene::update_matrix(Matrix3x3 const & mtx, unsigned int index){
    Matrix3x3 temp_matrix = mtx;
    Rotation_matrix.at(index) = temp_matrix * Rotation_matrix.at(index);
}

void Scene::update_vector(Vector3D const & vec, unsigned int index){
    Vector3D temp_vector = vec;
    Translation_vector.at(index) = Translation_vector.at(index) + temp_vector;
}

Scene Scene::Move_figure(unsigned int index){
    solid_figures.at(index).Move_cuboid(Translation_vector.at(index),Rotation_matrix.at(index));
    return *this;
}

void Scene::Add_cuboid(Vector3D const & Apx0, Vector3D const & Apx5){
    Vector3D VecOX, VecOY, VecOZ;
    Cuboid new_cuboid(Apx0,Apx0,Apx0,Apx0,Apx0,Apx5,Apx0,Apx0);
    
    Vector3D initial_vec;
    Matrix3x3 initial_mtx;

    VecOX[0] = abs(Apx0[0]-Apx5[0]);
    VecOY[1] = abs(Apx0[1]-Apx5[1]);
    VecOZ[2] = abs(Apx0[2]-Apx5[2]);

    new_cuboid[1] + VecOX;
    new_cuboid[2] + VecOY;
    new_cuboid[3] + VecOX; new_cuboid[3] + VecOY;

    new_cuboid[4] + VecOY; new_cuboid[4] + VecOZ;
    new_cuboid[6] + VecOZ;
    new_cuboid[7] + VecOX; new_cuboid[7] + VecOZ;

    solid_figures.push_back(new_cuboid); 
    Rotation_matrix.push_back(initial_mtx);
    Translation_vector.push_back(initial_vec);   
}