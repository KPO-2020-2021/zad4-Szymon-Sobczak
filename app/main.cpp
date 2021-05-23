/* Executables must have the following defined if the library contains
doctest definitions. For builds with this disabled, e.g. code shipped to
users, this can be left out. */

/*!
    \file
        \brief Plik zawierajacy "main" programu.
*/

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include "exampleConfig.h"
#include "vector.hh"
#include "matrix.hh"
#include "vector3D.hh"
#include "matrix4x4.hh"
#include "matrix3x3.hh"
#include "matrix2x2.hh"
#include "cuboid.hh"
#include "scene.hh"
#include "../inc/lacze_do_gnuplota.hh"

/*! \brief Glowna funkcja programu.*/

int main(){
    
    unsigned int active_cuboid = 0;   /* Inicjalizacja zmiennych tymczasowych */
    double angle = 0, multiplier = 1, tr_X = 0, tr_Y = 0,tr_Z = 0; 
    char Option;

    PzG::LaczeDoGNUPlota Link;         /* Zmienna potrzebna do wizualizacji rysunku prostopadloscianu */
    Vector3D T_vector, ctr_of_new_cub; /* Inicjalizacja wektorow tymczasowych */
    Matrix3x3 temp_rot_matrix;         /* Inicjalizacja macierzy tymczasowej  */
    
    Scene Scenery; /* Inicjalizacja sceny */

    std::vector <std::string> adresses_of_files; /* Inicjalizacja wektora zapamietujacego nazwy plikow z danymi poszczegolnych prostopadloscianow */

    std::string name_of_new_file;  /* Inicjalizacja zmiennej typu string - nazwy pojedynczego pliku ze wspolrzednymi prostopadloscianu */
    
    adresses_of_files.push_back("../datasets/cuboid1.dat");  

    Link.DodajNazwePliku(adresses_of_files.at(0).c_str(),PzG::RR_Ciagly,2); /* Rysowanie prostopadloscianu jako linia ciagla o grubosci 2 pikseli. */ 

    Link.ZmienTrybRys(PzG::TR_3D); /* Ustawienie trybu rysowania w gnuplot na 3D. */

    Link.UstawZakresY(-150,150);   /* Uwstawienie zakresu osi OX, OY i OZ w Gnuplot */ 
    Link.UstawZakresX(-150,150);
    Link.UstawZakresZ(-150,150); 

    try{
        double Apx1[]={50,60,40}; /* Dodanie do sceny pierwszego, przykladowego prostopadloscianu */
        Vector3D A(Apx1);
        Scenery.Add_cuboid(A,40,30,20);
        Scenery[active_cuboid].Write_cub_to_file(adresses_of_files.at(active_cuboid).c_str()); /* Zapis i wyswietlenie w GNUplot stanu poczatkowego, pierwszego, przykladowego prostopadloscianu */
        Link.Rysuj();
 
        std::cout << "Poczatkowy stan bokow prostopadloscianu: " << std::endl;
        Scenery[active_cuboid].Is_it_cub(); 

        std::cout << "Menu wyboru opcji:" << std::endl
                  << "\ta - zmien aktywny prostopadloscian" << std::endl
                  << "\to - obrot bryly o zadana sekwencje katow" << std::endl
                  << "\tt - powtorzenie poprzedniego obrotu" << std::endl
                  << "\tr - wyswietlenie macierzy rotacji" << std::endl
                  << "\tp - przesuniecie bryly o zadany wektor " << std::endl
                  << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                  << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                  << "\tm - wyswietl menu" << std::endl
                  << "\td - dodaj nowy prostopadloscian" << std::endl
                  << "\tk - koniec dzialania programu" << std::endl << std::endl;

        while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia- k */
            std::cout << "Numer aktywnego prostopadloscianu: " << active_cuboid << std::endl;
            std::cout << "Twoj wybor? (m - menu) > ";
            std::cin >> Option;
            switch(Option){  
                case 'a': /* Opcja pozwalajaca na zmiane aktywnego prostopaloscianu */
                    while (true){
                        try{
                            std::cout << "Podaj numer prostopadloscianu, ktory ma byc aktywny: " << std::endl;;
                            std::cout << "Dostepne prostopadlosciany [0;" << Scenery.how_many_cuboids()-1  << "] " << std::endl;
                            std::cin >> active_cuboid; 
                            if(std::cin.fail() || active_cuboid > (Scenery.how_many_cuboids()-1))
                                throw std::invalid_argument(":/ Podano bledny numer prostopadloscianu ");
                            else   
                                break;
                        }
                        catch (std::invalid_argument & a){ 
                            std::cerr << a.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    } 
                break;

                case 'o': /* Opcja pozwalajaca na zadanie sekwencji obrotu prostopadloscianu */
                    temp_rot_matrix.reset_matrix();
                    std::cout << "Podaj sekwencje: " << std::endl; /* Okreslenie sekwencji obrotow prostopadloscianu */
                    while (Option !='.'){  
                        try{
                            std::cin >> Option;
                            switch(Option){
                                case 'x':
                                std::cin >> angle;
                                if(std::cin.fail())
                                    throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu "); /*  */
                                else 
                                    temp_rot_matrix = Fill_matrix_OX(angle) * temp_rot_matrix;
                                break;

                                case 'y':
                                std::cin >> angle;
                                if(std::cin.fail())
                                    throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu ");
                                else
                                    temp_rot_matrix = Fill_matrix_OY(angle) * temp_rot_matrix;
                                break;

                                case 'z':
                                std::cin >> angle;
                                if(std::cin.fail())
                                    throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu ");
                                else
                                    temp_rot_matrix = Fill_matrix_OZ(angle) * temp_rot_matrix;
                                break;

                                case '.':    
                                    std::cout << ":) Podawanie sekwencji obrotow zakonczone pomyslnie. " << std::endl;      
                                break;

                                default:
                                    std::cout << ":/ Bledne oznaczenie osi. Dopuszczalne znaki to: (x, y, z, .)" << std::endl; 
                                    std::cout << ":/ Sprobuj jeszcze raz" << std::endl;
                                    std::cin.ignore(10000,'\n');
                                break;            
                              } 
                        }
                        catch (std::invalid_argument & d){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
                            std::cerr << d.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    }

                    while (true){
                        try{
                            std::cout << "Ile razy operacja obrotu ma byc powtorzona? "<< std::endl; /* Okreslenie ile razy wprowadzony obrot ma sie wykonac */
                            std::cin >> multiplier; 
                            if(std::cin.fail() || multiplier < 0)
                                throw std::invalid_argument(":/ Podano bledna wartosc mnoznika ");
                            else   
                                break;
                        }
                        catch (std::invalid_argument & f){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
                            std::cerr << f.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    } 

                    for (unsigned int i=0; i<multiplier;++i) /* Uzupelnienie macierzy rotacji dla wskazanego prostopadloscianu o zadana sekwencje obrotu, zadana ilosc razy */
                        Scenery.update_matrix(temp_rot_matrix, active_cuboid);
                    
                    Scenery.Move_figure(active_cuboid); /* Wykonanie obrotu i wyswietlenie w Gnuplot */
                    Scenery[active_cuboid].Is_it_cub();
                    Scenery[active_cuboid].Write_cub_to_file(adresses_of_files.at(active_cuboid).c_str());
                    Link.Rysuj();
                break;

                case 'p': /* Opcja translacji o wektor */
                    std::cout << "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb 'x y z' ";
                    std::cin >> T_vector;

                    Scenery.update_vector(T_vector,active_cuboid);
                    Scenery.Move_figure(active_cuboid);

                    Scenery[active_cuboid].Write_cub_to_file(adresses_of_files[active_cuboid].c_str());
                    Scenery[active_cuboid].Is_it_cub();
                    
                    Link.Rysuj();
                break;

                case 'w': /* Opcja wyswietlajaca wspolrzedne prostopadloscianu */
                    std::cout << "Aktualne wspolrzedne prostopadloscianu: " << std::endl;
                    std::cout << Scenery[active_cuboid];
                break;

                case 't': /* Opcja pozwlajaca na powtorzenie ostatniej rotacji na aktywnym prostopadloscianie */
                    for (unsigned int i=0; i<multiplier;++i)
                        Scenery.update_matrix(temp_rot_matrix,active_cuboid);  
                    Scenery.Move_figure(active_cuboid);
                    Scenery[active_cuboid].Write_cub_to_file(adresses_of_files[active_cuboid].c_str());
                    Scenery[active_cuboid].Is_it_cub();
                    Link.Rysuj();
                break;

                case 'r': /* Opcja ponawiajaca ostatni obrot prostopadloscianu */   
                    std::cout << "Macierz rotacji " << std::endl << Scenery.get_matrix(active_cuboid) << std::endl; 
                break;

                case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */        
                    std::cout << "Menu wyboru opcji:" << std::endl
                              << "\ta - zmien aktywny prostopadloscian" << std::endl
                              << "\to - obrot bryly o zadana sekwencje katow" << std::endl
                              << "\tt - powtorzenie poprzedniego obrotu" << std::endl
                              << "\tr - wyswietlenie macierzy rotacji" << std::endl
                              << "\tp - przesuniecie bryly o zadany wektor " << std::endl
                              << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                              << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                              << "\tm - wyswietl menu" << std::endl
                              << "\td - dodaj nowy prostopadloscian" << std::endl
                              << "\tk - koniec dzialania programu" << std::endl << std::endl;
                break;

                case 'k': /* Opcja konczaca program */
                    std::cout << ":) Konczenie pracy programu" << std::endl;
                break;

                case 's': /* Opcja wyswietlajaca wspolrzedne prostopadloscianu */
                    Scenery[active_cuboid].Is_it_cub();
                break;

                case 'd': /* Opcja dodajaca do sceny nowy prostopadloscian */
                    std::cout << "Podaj wspolrzedne punktow, na ktorych zostanie rozpiety nowy prostopadloscian: " << std::endl; 
                    std::cout << "Podaj wspolrzedne x y z pierwszego punktu: "; 
                    std::cin >> ctr_of_new_cub;
                    std::cout << "Podaj wartosci dlugosci o jakie punkt ma zostac rozsuniety na osiach OX, OY, OZ " << std::endl; 
                    std::cin >> tr_X >> tr_Y >> tr_Z;
                    if (std::cin.fail() || (tr_X == 0 && tr_Y == 0 && tr_Z == 0)){
                        std::cerr << ":( Niepoprawne oznaczenie dlugosci, dodawanie przerwane." << std::endl; 
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');   
                        break;
                    }

                    name_of_new_file = "../datasets/cuboid.dat";
                    name_of_new_file.insert(18, std::to_string(Scenery.how_many_cuboids() + 1));
                    adresses_of_files.push_back(name_of_new_file);
                    Link.DodajNazwePliku(name_of_new_file.c_str(),PzG::RR_Ciagly, 2);

                    Scenery.Add_cuboid(ctr_of_new_cub,tr_X,tr_Y,tr_Z);

                    Scenery[Scenery.how_many_cuboids()-1].Write_cub_to_file(name_of_new_file.c_str());

                    Link.Rysuj();
                break;

                default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
                    std::cout << ":/ Opcja niezdefiniowana" << std::endl;
            }
        }
    }
    catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
        std::cerr << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
        exit(1);
    }

    return 0;
} 
