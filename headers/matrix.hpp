#ifndef DEF_MATRIX
#define DEF_MATRIX

#include<vector>
#include<string>
#include<iostream>

template<typename Number>
int length_max(std::vector<Number> v); 
//Une fonction qui retourne la plus grande longueur (en nombre de caractère) des éléments de v 
//(utile pour afficher la matrice, cf. suite)

template<class Number> //permet de définir des matrices de différents types : Matrix<int>, Matrix<double>, ...
class Matrix{
    protected:
        int width;//largeur de la matrice
        int height;//hauteur de la matrice
        std::string name;//nom de la matrice
        std::vector<Number> values;//vecteur de taille width * height contenant les valeurs de la matrice
    
    public:
        Matrix(); //Un constructeur sans argument
        Matrix(const int& h, const int& w, const std::string& n, std::vector<Number> v, const Number& defaltValue = 0);
        //Un constructeur pour une Matrice de taille h*w, de nom n et de valeurs v (et une valeur par défault qui sera utilisée
        //pour compléter v si il n'est pas de taille w*h)
        int get_width(); //retourne la largeur de la matrice
        int get_height(); //retourne la hauteur de la matrice
        std::string get_name(); //retourne le nom de la matrice
        void set_name(const std::string& nm);
        std::vector<Number> get_values();//retourne le std::vector contenant les valeurs de la matrice 
        void print();//Affiche la matrice dans la console
        void add(Matrix<Number> B); //Ajoute la matrice B à la matrice considérée
        Matrix<Number> operator+=(const Matrix<Number>& B);
        void scalar_prod(const Number& lambda); //Multiplie la matrice considérée par le scalaire lambda
        Matrix<Number> operator*=(const Number& lambda);
        Matrix<Number> operator-=(Matrix<Number> B);
        Number trace();//retourne la trace de la matrice
        Matrix<Number> transpose();//retourne la transposée de la matrice
        Number norme();//retourne la norme de la matrice
};

template<typename Number>
Number somm_mat(const int& i, const int& j, const int& nn, const int& na, const std::vector<Number>& valuesA, const std::vector<Number>& valuesB);
//Une fonction qui donne la valeur du coefficient i,j de la matrice A*B
template<typename Number>
Matrix<Number> operator+(Matrix<Number> A, Matrix<Number>& B);
template<typename Number>
Matrix<Number> operator*(Matrix<Number> A,const Number& lambda);
template<typename Number>
Matrix<Number> operator*(const Number& lambda, Matrix<Number> A);
template<typename Number>
Matrix<Number> operator*(Matrix<Number> A, Matrix<Number>& B);
template<typename Number>
Matrix<Number> operator-(Matrix<Number> A, Matrix<Number> B);
template<typename Number>
Matrix<Number> operator/(Matrix<Number> A, const Number& lambda);

template<typename Number>
Matrix<Number> ID(const int& N);//Retourne la matrice identité de taille N

void tests_Matrices();//Fonction void qui print des essais sur la classe Matrix

template class Matrix<int>;

template class Matrix<double>;


#endif