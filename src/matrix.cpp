#include "../headers/matrix.hpp"
#include <math.h>


template<typename Number>
int length_max(std::vector<Number> v){
    int max = 0;
    for(auto m: v){
        if(std::to_string(m).size()>max){max = std::to_string(m).size();}
    }
    return max;
}



// Le constructeur
template<class Number>
Matrix<Number>::Matrix(){
    this->width = 0;
    this->height = 0; 
    this->name = "";
    std::vector<Number> v;
    this->values = v;
}

template<class Number>
Matrix<Number>::Matrix(const int& h, const int& w, const std::string& n, std::vector<Number> v, const Number& defaultValue){
    this->width = w;
    this->height = h; 
    this->name = n;
    v.resize(w*h,defaultValue);  // Dans le cas où v n'est pas de taille w*h on le redimmensionne, en le complétant éventuellement avec des 0 (ou une autre valeur défaut)
    this->values = v;
}

template<class Number>
int Matrix<Number>::get_width(){
    return this->width;
}
template<class Number>
int Matrix<Number>::get_height(){
    return this->height;
}
template<class Number>
std::string Matrix<Number>::get_name(){
    return this->name;
}
template<class Number>
void Matrix<Number>::set_name(const std::string& nm){
    this->name = nm;
}
template<class Number>
std::vector<Number> Matrix<Number>::get_values(){
    return this->values;
}

template<class Number>
void Matrix<Number>::print(){
    //On print une matrice de la forme suivante :
    //  | 5    4 |
    //  | 10   7 |
    int max = length_max(this->values); //"taille" d'affichage de chaque éléments
    std::cout << "Matrice " << this->name << " :"<< std::endl << "| ";
    for (std::size_t i=0; i<this->values.size(); i++){
        auto val = this->values[i];
        auto q = (max - std::to_string(val).size()); 
        //Nombre de " " qu'il va falloir print pour que l'affichage soit de taille max 
        //(et que l'affichage de chaque élement prenne la même place)
        if ((i+1)%this->width!=0){ //On n'est pas en fin de ligne
            std::cout << val << "   ";
            for(int ii=0; ii<q; ii++){std::cout<<" ";} //On print les " "
        }
        else{ //On est en fin de ligne
            std::cout << val;
            for(int ii=0; ii<q; ii++){std::cout<<" ";}
            std::cout<< " |" << std::endl;
            if(i!=this->values.size()-1){std::cout << "| ";}
        }
    }
    std::cout << std::endl;
}

template<class Number>
void Matrix<Number>::add(Matrix<Number> B){
    if((this->width != B.get_width())||(this->height != B.get_height())){ //impossible de les additionner
        throw std::invalid_argument(this->name + " and " + B.get_name() + " have not the same shapes and can't be added.");}
    else{
        for(std::size_t i=0; i<this->values.size(); i++){
            this->values[i]+=B.get_values()[i];
        }
    }
}

template<class Number>
Matrix<Number> Matrix<Number>::operator+=(const Matrix<Number>& B){
    this->add(B);
    return *this;
}

template<class Number>
Matrix<Number> operator+(Matrix<Number> A, Matrix<Number>& B){
    int H = A.get_height();
    int W = A.get_width();
    std::string N {A.get_name() + " + " + B.get_name()};
    A.add(B);
    Matrix<Number> Retu(H, W, N, A.get_values());
    return Retu;
}
template Matrix<double> operator+<double>(Matrix<double>, Matrix<double>&);


template<class Number>
void Matrix<Number>::scalar_prod(const Number& lambda){
    for(std::size_t i=0; i<this->values.size(); i++){
            this->values[i]*=lambda;
        }
}

template<class Number>
Matrix<Number> Matrix<Number>::operator*=(const Number& lambda){
    this->scalar_prod(lambda);
    return *this;
}

template<class Number>
Matrix<Number> operator*(Matrix<Number> A, const Number& lambda){
    A.scalar_prod(lambda);
    std::string nom {std::to_string(lambda)};
    Matrix<Number> Retu(A.get_height(), A.get_width(), nom + " * " + A.get_name(), A.get_values());
    return Retu;
}
template Matrix<double> operator*<double>(Matrix<double>, const double& lambda);

template<class Number>
Matrix<Number> operator*(const Number& lambda, Matrix<Number> A){
    return A*lambda;
}
template Matrix<double> operator*<double>(const double& lambda, Matrix<double>);

template<class Number>
Number Matrix<Number>::trace(){
    int n {this->get_height()};
    if(this->get_width()!=n){
        throw std::invalid_argument(this->name + " is not a square matrix");}
    else{
        std::vector<Number> v{this->get_values()};
        Number T {0};
        for(int i=0; i<n; i++){
            T+=v[i*n+i];
        }
        return T;
    }

}

template<class Number>
Matrix<Number> Matrix<Number>::transpose(){
    int n{this->get_height()};
    int m{this->get_width()};
    std::vector<Number> v{this->get_values()};
    std::vector<Number> new_v;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            new_v.push_back(v[i+j*m]);
        }
    }
    Matrix<Number> Transp{m,n,this->get_name() + "_transpose",new_v};
    return Transp;
}

template<typename Number>
Number Matrix<Number>::norme(){
    return sqrt((this->transpose()*(*this)).trace());
}


template<typename Number>
Number somm_mat(const int& i, const int& j, const int& nn, const int& na, const std::vector<Number>& valuesA, const std::vector<Number>& valuesB){
    Number sum = 0;
    for(int k=0; k<nn; k++){
        sum+=(valuesA[(i-1)*nn+k]*valuesB[(j-1)+k*(na)]);
    }
    return sum;
}

template<class Number>
Matrix<Number> operator*(Matrix<Number> A, Matrix<Number>& B){
    if(A.get_width()!=B.get_height()){
        throw std::invalid_argument(A.get_name() + " and " + B.get_name() + " have not correct shapes.");}
    else{
        int n = A.get_height();
        int m = B.get_width();
        std::vector<Number> v;
        for(int i = 1 ; i<=n; i++){
            for(int j=1; j<=m; j++){
                v.push_back(somm_mat(i, j, A.get_width(), B.get_width(), A.get_values(), B.get_values()));
            }
        }
        Matrix<Number> Retu(n, m, A.get_name() + "." + B.get_name(),v);
        return Retu;
    }
}
template Matrix<double> operator*<double>(Matrix<double>, Matrix<double>&);

template<class Number>
Matrix<Number> operator-(Matrix<Number> A, Matrix<Number> B){
    int H = A.get_height();
    int W = A.get_width();
    std::string N {A.get_name() + " - " + B.get_name()};
    B*=-1;
    A.add(B);
    Matrix<Number> Retu(H, W, N, A.get_values());
    return Retu;
}
template Matrix<double> operator-<double>(Matrix<double>, Matrix<double>);

template<class Number>
Matrix<Number> Matrix<Number>::operator-=(Matrix<Number> B){
    B*=-1;
    this->add(B);
    return *this;
}

template<class Number>
Matrix<Number> operator/(Matrix<Number> A, const Number& lambda){
    A.scalar_prod(1/lambda);
    std::string nom {std::to_string(lambda)};
    Matrix<Number> Retu(A.get_height(), A.get_width(), A.get_name()+" / "+nom, A.get_values());
    return Retu;
}

template<typename Number>
Matrix<Number> ID(const int& N){
    std::vector<Number> v;
    int k{-N-1};
    for(int i=0; i<N*N; i++){
        if(i-k==N+1){
            k=i;
            v.push_back(1);
        }
        else{v.push_back(0);}
    }
    Matrix<Number> I(N,N,"I",v);
    return I;
}

void tests_Matrices(){
    std::cout<<"Voici une série de tests de la classe Matrix : \n\nOn commence par définir une matrice A de type Matrix<int> :"
        << std::endl;
    Matrix<int> A(2, 2, "A", {1, 2, 3, 4});
    A.print();

    std::cout << "Et une matrice B (de même type) : \n";
    Matrix<int> B(2, 2, "B", {2, 2, 4, 4});
    B.print();

    std::cout << "On peut alors calculer A + B : \n";
    Matrix<int> C {A+B};
    C.print();

    std::cout<<"On remarque que cela n'a pas d'effet sur les valeurs de A et B, "
        <<"\nla Matrice A + B est bien une nouvelle matrice à part entière (copie et somme des valeurs de A et B) :\n";
    A.print();
    B.print();
    std::cout<<"On a cependant pris soins de définir un opérateur += qui lui modifie directement les valeurs de la matrice.\n\n";

    std::cout<<"On peut ensuite multiplier nos matrices par des scalaires : \n";
    Matrix<int> D = A*2;
    D.print();

    std::cout<<"Et calculer un produit matriciel :\n";
    Matrix<int> E = A*B;
    E.print();

    std::cout<<"Notons que tout ceci fonctionne avec des matrices de type Matrix<float>, Matrix<double>, etc.. "
        <<"Et des matrices plus grandes ou non carrées.\n";
    
    Matrix<double> F(4, 3, "F", {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 8.8, 7.7, 6.6});
    F.print();
    Matrix<double> G(3, 4, "G", {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 8.8, 7.7, 6.6});
    G.print();
    Matrix<double> H = F*G;
    H.print();
    std::cout<<"Je vous promets, c'est un hasard complet de trouver 45.98 à chaque fois sur la ligne du haut,"
        <<"vous pouvez faire les calculs !\n\nAu final, on définit pour la classe Matrix les opérateurs +, -, *, ., +=, *=, -=\n"
        <<"On définit également les opérations de trace, transposition, et une norme matricielle.\n";
    std::cout<<"Voici donc la trace de F.G, puis F.G transposée : \n\n";
    std::cout<<"Trace de F.G : "<<H.trace()<<std::endl;
    (H.transpose()).print();

    std::cout<<"On définit enfin la matrice identité de taille n (ici n=6).\n\n";
    Matrix<double> I{ID<double>(6)}; 
    I.print();
    std::cout<<"De norme : "<< I.norme()<<"\n\n";
    

}