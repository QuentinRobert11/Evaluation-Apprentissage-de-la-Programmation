# include<iostream>
# include "../headers/matrix.hpp"
# include "../headers/temperature_map.hpp"
# include "../headers/linear_syst.hpp"

#define NC "\e[0m"
#define CYN "\e[0;36m" //Des couleurs pour écrire dans la console

const char* cmd_clear="clear";

void Clear(){ //Une fonction qui 'lave' la console (pas du tout pompée sur le snake)
    int out = system( cmd_clear);
    if( out != 0){
        std::cerr << "clear command failed" << std::endl;
        exit(1);
    }
}

void Pause(){ //Une fonction qui demande à l'utilisateur d'appuyer sur Entrée pour continuer
    std::cout<< CYN "Appuyez sur Entrée pour continuer..." NC;
    getchar();
    Clear();
}

int main(){
    Clear();
    std::cout<<"Quentin ROBERT, Janvier 2022 : Evaluation de C++\n\n";
    Pause();
    tests_Matrices();//Fonction void qui print des essais sur la classe Matrix
    Pause();
    tests_Solver();//Fonction void qui print des essais du Solver
    Pause();
    int nx; //Nombre de discrétisations spatiales
    int nt; //Nombre de discrétisations temporelles
    std::cout<<"On se propose maintenant de résoudre l'équation de la chaleur : \n";
    std::cout<<"Veuillez renseigner une valeur pour Nx : ";
    std::cin>>nx;
    std::cout<<"Veuillez renseigner une valeur pour Nt : ";
    std::cin>>nt;
    TempMap<double> T(nx,nt); //On fait tous les calculs avec des doubles
    T.Resoudre();//On résoud l'équation de la chaleur
    return EXIT_SUCCESS;
}