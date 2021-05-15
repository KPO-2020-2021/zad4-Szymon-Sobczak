/* Przygotowal: Szymon Sobczak nr 259275 */

/* Executables must have the following defined if the library contains
doctest definitions. For builds with this disabled, e.g. code shipped to
users, this can be left out. */
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unistd.h>

#include "exampleConfig.h"
#include "vector.hh"
#include "matrix.hh"
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "cuboid.hh"
#include "scene.hh"
#include "../inc/lacze_do_gnuplota.hh"

int main(){
    double Apx1[]={2,3,3}, Apx2[]={22,3,3}, Apx3[]={2,18,3}, Apx4[]={22,18,3},Apx5[]={2,18,28},Apx6[]={22,18,28},Apx7[]={2,3,28},Apx8[]={22,3,28}, angle, multiplier; /* Inicjalizacja tablic wartosciami wierzcholkow prostokata oraz zmiennych potrzebnych w programie */
    Vector<SIZE> V1(Apx1),V2(Apx2),V3(Apx3),V4(Apx4),V5(Apx5),V6(Apx6),V7(Apx7),V8(Apx8),T_vector;   /* Inicjalizacja wektorow reprezentujacych wspolrzedne wierzcholkow prostokata i wektora translacji */

    Cuboid Cub(V1,V2,V3,V4,V5,V6,V7,V8);                /* Inicjalizacja prostokata za pomoca wektorow */
    PzG::LaczeDoGNUPlota Link;                         /* Zmienna potrzebna do wizualizacji rysunku prostokata */
    char Option;

    double X2[]={10,10}, Y2[]={60,10}, Z2[]={60,45}, U2[]={10,45}; 
    Vector<SIZE> A2(X2),B2(Y2),C2(Z2),D2(U2);   
    Cuboid Cub2(V1,V2,V3,V4,V5,V6,V7,V8);                      
    Scene Scenery(1);
    
    Matrix<SIZE> rotation_matrix, temp;
    /********************************************************************************
     |   Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"           |
     |  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane na dwa sposoby:|
     |  1.Rysowane jako linia ciagla o grubosci 2 piksele                           |
    */
    Link.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Ciagly,2);

    /*******************************************************************************
     |   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,           |
     |   których połowa długości boku wynosi 2.                                    |
    */
   // Link.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Punktowy,2);

    /******************************************************************************* 
     | Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów                  |
     |   znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj              |
     |  jako wspolrzedne punktow podajemy tylko x,y.                               |
    */
    Link.ZmienTrybRys(PzG::TR_3D);

    Link.UstawZakresY(-155,155);
    Link.UstawZakresX(-155,155);
    Link.UstawZakresZ(-155,155); 

    double A[3][3] = {1,2,3,4,5,6,7,8,9},B[3][3] = {9,6,3,8,5,2,7,4,1};

    Matrix3x3 temp_rot_matrix;

    Matrix3x3 matrix1(A),matrix2(B);

    std::cout << matrix1  << std::endl;
     std::cout << matrix2  << std::endl;
    std::cout << matrix1 * matrix2 << std::endl;
    std::cout << temp_rot_matrix;
    try{
        Scenery[0].Write_cub_to_file("../datasets/prostokat.dat"); /* Wyswietlenie w GNUplot stanu poczatkowego prostokata */
        Link.Rysuj();
        std::cout << "Poczatkowy stan bokow prostokata: " << std::endl;
        Scenery[0].Is_it_cub(); 
        std::cout << "Menu wyboru opcji:" << std::endl
                  << "\to - obrot bryly o zadana sekwencje katow" << std::endl
                  << "\tt - powtorzenie poprzedniego obrotu" << std::endl
                  << "\tr - wyswietlenie macierzy rotacji" << std::endl
                  << "\tp - przesuniecie bryly o zadany wektor " << std::endl
                  << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                  << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                  << "\tm - wyswietl menu" << std::endl
                  << "\tc - sprawdzenie kolizji" << std::endl
                  << "\tk - koniec dzialania programu" << std::endl;
                  
        while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia- k */
            std::cout << "Twoj wybor? (m - menu) > ";
            std::cin >> Option;
            switch(Option){
                case 'o': /* Opcja obrotu prostokata */
                    temp_rot_matrix.reset_matrix();

                    std::cout << temp_rot_matrix <<std::endl;
                    std::cout << "Podaj sekwencje: "; /* Okreslenie parametrow obrotu prostokata- kata i ilosci obrotow */
                    while (Option !='.'){   
                            std::cin >> Option;
                            switch(Option){
                                case 'x':
                                    std::cin >> angle;
                                    if(std::cin.fail())
                                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                                    temp_rot_matrix = Fill_matrix_OX(angle) * temp_rot_matrix;
                                    std::cout << Fill_matrix_OX(angle) << std::endl;
                                    std::cout << temp_rot_matrix << std::endl;
                                break;

                                case 'y':
                                std::cin >> angle;
                                    if(std::cin.fail())
                                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                                     temp_rot_matrix = Fill_matrix_OY(angle) * temp_rot_matrix;
                                break;

                                case 'z':
                                    std::cin >> angle;
                                    if(std::cin.fail())
                                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                                    temp_rot_matrix = Fill_matrix_OZ(angle) * temp_rot_matrix;
                                break;

                                case '.':
                                
                                break;

                                default:
                                    std::cout << ":/ Bledne oznaczenie osi. Dopuszczalne znaki to: (x, y, z, .)" << std::endl; 
                                break;
                            }    
                        }
                    std::cout << temp_rot_matrix;
                    std::cout << "Ile razy operacja obrotu ma byc powtorzona > ";
                    std::cin >> multiplier;
                        

                    for (unsigned int i=0; i<multiplier;++i){
                        Scenery.update_matrix(temp_rot_matrix);
                    }         

                    std::cout << "Czy obrot ma byc animowany? T/N? (Operacja wykonywana bardzo szybko dla duzej ilosci powtorzen) > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':  /* Gdy uzytkownik zdecyduje sie na animacje obrotu */
                        // std::cout << Scenery.get_matrix()<< std::endl;
                        //    temp = Scenery.get_matrix()/100;
                        //    std::cout << temp;
                        //     for (int i=0; i< multiplier;i++){
                        //         for(int j=0;j < FRAMES; j++){
                        //             Scenery[0].Rotate_cub(1,temp); /*Wywolanie metody obracajacej prostokat raz, o ulamek wybranego kata, w celu nadania wrazenia ruchu */ 
                        //             Scenery[0].Write_cub_to_file("../datasets/prostokat.dat");
                        //             usleep(4000);
                        //             Link.Rysuj();
                        //             usleep(4000);
                        //         }
                        //     }
                        //     Scenery[0].Is_it_cub(); 
                        break;

                        case 'N': /* Gdy uzytkownik nie zdecyduje sie na animacje obrotu */
                           // Scenery[0].Rotate_cub(multiplier,Scenery.get_matrix()); /* Wywolanie metody obracajacej prostokat wybrana ilosc razy o wybrany kat w stopniach */
                            Scenery.Move_figure(0);
                            Scenery[0].Write_cub_to_file("../datasets/prostokat.dat");
                            Scenery[0].Is_it_cub();
                            Link.Rysuj();
                        break;

                        default: /*Dzialanie, gdy opcja podmenu nie bedzie zdefiniowana */
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'p': /* Opcja translacji o wektor */
                    std::cout << "Wprowadz wspolrzedne wektora translacji w postaci liczb x i y > ";
                    std::cin >> T_vector;
                    std::cout << "Czy translacja ma byc animowana? T/N? > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':  /* Gdy uzytkownik zdecyduje sie na animacje translacji */
                        //     T_vector/FRAMES;
                        //     for(int i=0;i<FRAMES;i++){
                        //         Scenery[0].Translate_cub(T_vector/FRAMES);/* Wywolanie metody przesuwajacej prostokat raz, o ulamek wybranego wektora, w celu nadania wrazenia ruchu */
                        //         Scenery[0].Write_cub_to_file("../datasets/prostokat.dat");
                        //         usleep(4000);
                        //         Link.Rysuj();
                        //         usleep(4000); 
                        //     }
                        //     Scenery[0].Is_it_cub();
                        break;

                        case 'N': /* Gdy uzytkownik nie zdecyduje sie na animacje translacji */
                            Scenery.update_vector(T_vector);
                            Scenery.Move_figure(0);
                            Scenery[0].Write_cub_to_file("../datasets/prostokat.dat");
                            Scenery[0].Is_it_cub();
                            Link.Rysuj();
                        break;

                        default: /*Dzialanie, gdy opcja podmenu nie bedzie zdefiniowana */
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'w': /* Opcja wyswietlajaca wspolrzedne prsotokata */
                    std::cout << "Aktualne wspolrzedne prostokata: " << std::endl;
                    std::cout << Scenery[0];
                break;

                case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */
                    std::cout << "Menu wyboru opcji:" << std::endl
                              << "\to - obrot bryly o zadana sekwencje katow" << std::endl
                              << "\tt - powtorzenie poprzedniego obrotu" << std::endl
                              << "\tr - wyswietlenie macierzy rotacji" << std::endl
                              << "\tp - przesuniecie bryly o zadany wektor " << std::endl
                              << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                              << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                              << "\tm - wyswietl menu" << std::endl
                              << "\tc - sprawdzenie kolizji" << std::endl
                              << "\tk - koniec dzialania programu" << std::endl;
                break;

                case 'k': /* Opcja konczaca program */
                    std::cout << ":) Konczenie pracy programu" << std::endl;
                break;

                case 'c': /* Sprawdzenie kolizji dwoch prostokatow */
                    std::cout << "Test kolizji prostokatow " << std::endl;
                    Cub2.Write_cub_to_file("../datasets/prostokat_2.dat");
                    Link.DodajNazwePliku("../datasets/prostokat_2.dat",PzG::RR_Ciagly,2);
                    Link.DodajNazwePliku("../datasets/prostokat_2.dat",PzG::RR_Punktowy,2);
                    Link.Rysuj();
                    if(Cub.collision(Cub2)==1)
                        std::cout << ":O Wykryto kolizje!" << std::endl;
                    else 
                        if(Cub2.collision(Cub)) 
                            std::cout << ":O Wykryto kolizje!" << std::endl;
                        else
                            std::cout << ":) Brak kolizji." << std::endl; 
                break;

                default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
                    std::cout << ":/ Opcja niezdefiniowana" << std::endl;
            }
        }
    }
    catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
        std::cout << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
        exit(1);
    }
    return 0;
} 
