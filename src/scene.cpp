#include "scene.hh"

Scene::Scene(){
    double Apx1[]={2,3,3}, Apx6[]={22,18,28};
    Vector3D A(Apx1), B(Apx6);
    Add_cuboid(A,B);
}

const Cuboid & Scene::operator [] (unsigned int index) const{
    if (index>=solid_figures.size())
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures.at(index);
}

 /* Cuboid & Scene::operator [] (unsigned int index){
    if (index>=solid_figures.size())
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures.at(index);
} */

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

void Scene::Move_figure(unsigned int index){
    solid_figures.at(index).Move_cuboid(Translation_vector.at(index), Rotation_matrix.at(index));
}

unsigned int Scene::how_many_cuboids(){
    return solid_figures.size();
}


void Scene::Add_cuboid(Vector3D const & Apx0, Vector3D const & Apx5){
    Vector3D initial_vec;
    Matrix3x3 initial_mtx;
    
    Vector3D temp_apx0 = Apx0, temp_apx5 = Apx5,VecOX, VecOY, VecOZ;
    
    //Vector3D cub_apx[8] = {Apx0,Apx0,Apx0,Apx0,Apx0,Apx5,Apx0,Apx0};
    Vector3D cub_apx[8] = {Apx0,Apx0,Apx0,Apx5,Apx5,Apx5,Apx0,Apx5};

    VecOX[0] = abs(temp_apx0 [0]-temp_apx5[0]);
    VecOY[1] = abs(temp_apx0 [1]-temp_apx5[1]);
    VecOZ[2] = abs(temp_apx0 [2]-temp_apx5[2]);
    /* DO PRZEROBIENIA NA PODAWANIE DL X Y Z bo tak za duzo wyjatkow*/
/*     
    cub_apx[1] + VecOX;
    cub_apx[2] + VecOY;
    cub_apx[3] + VecOX; cub_apx[3] + VecOY;

    cub_apx[4] + VecOY; cub_apx[4] + VecOZ;
    cub_apx[6] + VecOZ;
    cub_apx[7] + VecOX; cub_apx[7] + VecOZ;
      */
     if (Apx0[0]>Apx5[0])
    cub_apx[1] + VecOX;
    cub_apx[2] + VecOY;
    cub_apx[6] + VecOZ; 

    cub_apx[3] - VecOZ;
    cub_apx[4] - VecOX;
    cub_apx[7] - VecOY; 

    Cuboid cuboid_dummy(cub_apx[0],cub_apx[1],cub_apx[2],cub_apx[3],cub_apx[4],cub_apx[5],cub_apx[6],cub_apx[7]);

    solid_figures.push_back(cuboid_dummy); 
    Rotation_matrix.push_back(initial_mtx);
    Translation_vector.push_back(initial_vec);   
}