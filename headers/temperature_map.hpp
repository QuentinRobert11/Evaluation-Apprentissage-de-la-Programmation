#ifndef DEF_TEMP_MAP
#define DEF_TEMP_MAP

#include "../headers/matrix.hpp"
#include<fstream>
#include "../headers/linear_syst.hpp"

template <typename Number>
void write(std::vector<Number> v, const std::string& NomFichier);
template<class Number>
class TempMap {
    protected:
        double X; //longueur de la zone de diffusion
        double T; //durée de l'étude
        int Nx; //Nombre de discrétisations spatiales
        int Nt; //Nombre de discrétisations temporelles
        double DeltaX; //Distance entre deux discrétisations spatiales
        double DeltaT; //Temps entre deux discrétisations temporelles
        Matrix<Number> TempVector; //Vecteur de température (Matrice de taille Nx * 1)
        Matrix<Number> ThermicalConductivity; //Matrice K
    public:
        TempMap(const int& NX, const int& NT); //Constructeur
        TempMap(const double& X, const double& T, const int& NX, const int& NT, const Matrix<Number> TempVector_init, const std::vector<Number>& ConductivityCoefficient);
        //Surcharge du constructeur pour les questions Bonus
        void iterer_Eexplicite(); // Une itération selon la méthode explicite
        void iterer_Eimplicite(Matrix<Number> T0); // Une itération selon la méthode implicite
        void Resoudre(); // effectue un nombre Nt d'itérations avec la méthode choisie
}; 

void ecrire_Pourcentage(double x);


template class TempMap<double>;

#endif