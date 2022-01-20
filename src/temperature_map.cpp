#include "../headers/temperature_map.hpp"
#include<math.h>
#include<iostream>

#define NC "\e[0m"
#define CYN "\e[0;36m" //Des couleurs pour écrire dans la console

template <typename Number>
void write(std::vector<Number> v, const std::string& NomFichier){
    std::ofstream monFlux(NomFichier + ".txt",  std::ios::app);
    for(auto m:v){
        monFlux<< m << "; ";
    }
    monFlux << std::endl;;
}

template<class Number>  //Même si l'utilité semble moindre ici, on s'autorise à faire tous les calculs avec des int
TempMap<Number>::TempMap(const int& NX, const int& NT){
    this->Nx=NX;
    this->Nt=NT;
    this->X=1;
    this->T=0.5;
    this->DeltaX=this->X/(this->Nx-1);
    this->DeltaT=this->T/(this->Nt-1);
    std::vector<Number> K_vec;
    for(int i=0; i<this->Nx ; i++){
        for(int j=0; j<this->Nx; j++){
            if((j==i-1)&&(i!=this->Nx-1)){K_vec.push_back(1);}
            else if(i==j){K_vec.push_back(-2);}
            else if((j==i+1)&&(i!=0)){K_vec.push_back(1);}
            else{K_vec.push_back(0);}
        }
    }
    Matrix<Number> K(this->Nx,this->Nx,"K",K_vec);
    this->ThermicalConductivity = K;
    std::vector<Number> v;
    for(int i=0; i<this->Nx-1; i++){
        v.push_back(.5 + sin(2*M_PI*i*this->DeltaX)-0.5*cos(2*M_PI*i*this->DeltaX));
    }
    v.push_back(0);
    Matrix<Number> B(this->Nx, 1, "T", v);
    this->TempVector = B;
}

template<class Number>
TempMap<Number>::TempMap(const double& X, const double& T, const int& NX, const int& NT, const Matrix<Number> TempVector_init, const std::vector<Number>& ConductivityCoefficient){
    this->Nx=NX;
    this->Nt=NT;
    this->X=X;
    this->T=T;
    this->DeltaX=this->X/(this->Nx-1);
    this->DeltaT=this->T/(this->Nt-1);
    std::vector<Number> K_vec;
    for(int i=0; i<this->Nx ; i++){
        for(int j=0; j<this->Nx; j++){
            if(j==i-1){K_vec.push_back(ConductivityCoefficient[i]);}
            else if(i==j){K_vec.push_back(-ConductivityCoefficient[i]-ConductivityCoefficient[i+1]);}
            else if(j==i+1){K_vec.push_back(ConductivityCoefficient[i+1]);}
            else{K_vec.push_back(0);}
        }
    }
    Matrix<Number> K(this->Nx,this->Nx,"K",K_vec);
    this->ThermicalConductivity = K;
    this->TempVector = TempVector_init;
}

template<class Number>
void TempMap<Number>::iterer_Eexplicite(){
    Matrix<Number> A {this->ThermicalConductivity * this->TempVector};
    A*=this->DeltaT/(this->DeltaX*this->DeltaX);
    this->TempVector +=  A;
}

template<class Number>
void TempMap<Number>::iterer_Eimplicite(Matrix<Number> T0){
    auto a {this->DeltaT/(this->DeltaX*this->DeltaX)};
    Matrix<Number> Q{a*this->ThermicalConductivity};
    Matrix<Number> A {ID<Number>(this->Nx)-Q};
    Number eps{0.0000001};
    this->TempVector = solve_grad(A, this->TempVector, T0, eps);}

void ecrire_Pourcentage(double x){
    if(int(x)==x){std::cout<<"\r";
    int a=0;
    std::cout<<CYN;
    for(int i=0; i<int(x/5); i++){
        std::cout<<"#";
        a = i;
    }
    for(int j=0; j<20-a; j++){
        std::cout<<" ";
    }
    std::cout<<NC " "<<x<<"%";}
}

template<class Number>
void TempMap<Number>::Resoudre(){
    int a=0;
    do{
        std::cout<<"Veuillez choisir une méthode : \n1) Euler explicite\n2) Euler implicite\nVotre choix : ";
        std::cin>>a;
        std::cout<<"\n\nCalcul en Cours...\n====================\n";
        if(a==1){
            std::ofstream monFlux("Resultats_Explicite.txt");
            monFlux << this->X << std::endl << this->DeltaX << std::endl << this->DeltaT << std::endl;
            write(this->TempVector.get_values(), "Resultats_Explicite");
            for(int t=1; t<=this->Nt-1; t++){
                this->iterer_Eexplicite();
                ecrire_Pourcentage(100*(t+1)/this->Nt);
                write(this->TempVector.get_values(), "Resultats_Explicite");
            }
            if(this->TempVector.norme()<2){
                std::cout<<"\n\nLa méthode semble avoir convergé.\n";
                std::cout<<"Les résultats sont disponibles dans le fichier " << CYN "Resultats_Explicite.txt\n\n";}
            else{std::cout<<"\n\nLa méthode semble avoir divergé : veuillez revoir vos pas de temps et d'espace.\n\n";}
        }
        else if(a==2){
            std::ofstream monFlux("Resultats_Implicite.txt");
            monFlux << this->X << std::endl << this->DeltaX << std::endl << this->DeltaT << std::endl;
            write(this->TempVector.get_values(), "Resultats_Implicite");
            for(int t=1; t<=this->Nt-1; t++){
                this->iterer_Eimplicite(this->TempVector);
                ecrire_Pourcentage(100*(t+1)/this->Nt);
                write(this->TempVector.get_values(), "Resultats_Implicite");
            }
            if(this->TempVector.norme()<2){
                std::cout<<"\n\nLa méthode semble avoir convergé.\n";
                std::cout<<"Les résultats sont disponibles dans le fichier " << CYN "Resultats_Implicite.txt\n\n";}
            else{std::cout<<"\n\nLa méthode semble avoir divergé : veuillez revoir vos pas de temps et d'espace.\n\n";}
        }
        else{std::cout<<"Cette entrée n'est pas correcte\n";}
    } while((a!=1)&&(a!=2));
}