#include "scene.hh"

Scene::Scene(){
    double Apx1[]={2,3,3};
    Vector3D A(Apx1);
    Add_cuboid(A,20,15,25);
}

Scene::~Scene(){
    std::string datasets_path = "../datasets";
    for (const auto& entry : std::filesystem::directory_iterator(datasets_path)) 
        std::filesystem::remove_all(entry.path());
}

const Cuboid & Scene::operator [] (unsigned int index) const{
    if (index>=solid_figures.size())
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

void Scene::Move_figure(unsigned int index){
    solid_figures.at(index).Move_cuboid(Translation_vector.at(index), Rotation_matrix.at(index));
}

unsigned int Scene::how_many_cuboids(){
    return solid_figures.size();
}

void Scene::Add_cuboid(Vector3D const & Apx0, double const & tra_OX, double const & tra_OY, double const & tra_OZ){
    Vector3D initial_vec, VecOX, VecOY, VecOZ;
    Matrix3x3 initial_mtx;

    Vector3D cub_apx[8] = {Apx0,Apx0,Apx0,Apx0,Apx0,Apx0,Apx0,Apx0};

    VecOX[0] = tra_OX;
    VecOY[1] = tra_OY;
    VecOZ[2] = tra_OZ;
 
    cub_apx[1] + VecOX;
    cub_apx[2] + VecOY;
    cub_apx[3] + VecOX; cub_apx[3] + VecOY;
    cub_apx[4] + VecOY; cub_apx[4] + VecOZ;
    cub_apx[5] + VecOX; cub_apx[5] + VecOY; cub_apx[5] + VecOZ;
    cub_apx[6] + VecOZ;
    cub_apx[7] + VecOX; cub_apx[7] + VecOZ;

    Cuboid cuboid_dummy(cub_apx[0],cub_apx[1],cub_apx[2],cub_apx[3],cub_apx[4],cub_apx[5],cub_apx[6],cub_apx[7]);

    solid_figures.push_back(cuboid_dummy); 
    Rotation_matrix.push_back(initial_mtx);
    Translation_vector.push_back(initial_vec);   
}