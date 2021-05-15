#include "scene.hh"

Scene::Scene(unsigned int number_of_cuboids){
    if (number_of_cuboids > NBR_OF_FIGURES || number_of_cuboids == 0)
         throw std::runtime_error("Podano bledna wartosc ");
    if (number_of_cuboids <= 1){   
            double Apx1[]={2,3,3}, Apx2[]={22,3,3}, Apx3[]={2,18,3}, Apx4[]={22,18,3}, Apx5[]={2,18,28}, Apx6[]={22,18,28}, Apx7[]={2,3,28}, Apx8[]={22,3,28};
            Vector3D V1(Apx1),V2(Apx2),V3(Apx3),V4(Apx4),V5(Apx5),V6(Apx6),V7(Apx7),V8(Apx8);  
            Cuboid Cub(V1,V2,V3,V4,V5,V6,V7,V8); 
            solid_figures[0]= Cub;               
        }
}

const Cuboid & Scene::operator [] (unsigned int index) const{
    if (index>=NBR_OF_FIGURES)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures[index];
}

 Cuboid & Scene::operator [] (unsigned int index){
    if (index>=NBR_OF_FIGURES)
        throw std::runtime_error("Bledna wartosc indeksu macierzy");
    return solid_figures[index];
}

Matrix3x3 Scene::get_matrix(){
    return Rotation_matrix;
}

void Scene::update_matrix(Matrix3x3 const & mtx){
    Matrix3x3 temp_matrix = mtx;
    Rotation_matrix = temp_matrix * Rotation_matrix ;
}

void Scene::update_vector(Vector3D const & vec){
    Vector3D temp_vector = vec;
    Translation_vector = Translation_vector + temp_vector;
}

Scene Scene::Move_figure(unsigned int cuboid_number){
    solid_figures[cuboid_number].Move_cuboid(Translation_vector,Rotation_matrix);
    return *this;
}

Scene Scene::Move_figure_animation(unsigned int cuboid_number){
    solid_figures[cuboid_number].Move_cuboid(Translation_vector/FRAMES,Rotation_matrix/FRAMES);
    return *this;
}