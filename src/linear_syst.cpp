#include "../headers/linear_syst.hpp"

template <typename Number> //Un template pour manipuler des matrices tant de int que de double
Matrix<Number> solve_grad(Matrix<Number>& A, Matrix<Number>& B, Matrix<Number> X0, const Number& epsilon){
    //Une fonction pour résoudre le système A.X = B avec la méthode du gradient conjugué
    Matrix<Number> r {B - (A*X0)};
    Matrix<Number> r_new {B - (A*X0)};
    Matrix<Number> p {r};
    Matrix<Number> q;
    int k=0;
    Number alpha;
    Number beta;
    Number gamma;
    while (r.norme()>epsilon)
    {
        gamma = (p.transpose()*A*p).get_values()[0];
        alpha = pow(r.norme(),2)/gamma;
        q = p*alpha;
        X0+=q;
        r_new=r-alpha*(A*p);
        beta=pow(r_new.norme(),2)/pow(r.norme(),2);
        p=beta*p+r_new;
        r=r_new;
        k += 1;
    }
    return X0;
    
    
}

template <typename Number> //Un template pour manipuler des matrices tant de int que de double
Matrix<Number> solve_pivot(Matrix<Number> A, Matrix<Number> B){
    int N = A.get_height();
    int M = A.get_width();
    std::vector<Number> v = A.get_values();
    std::vector<Number> vb = B.get_values();
    Number pivot;
    for(int r=1; r<N; r++){
        for(int i=r; i<N; i++){
            pivot = v[i*M+r-1]/v[r-1];
            vb[i]-=pivot*vb[0];
            for(int j=r-1; j<M; j++){
                v[i*M+j]-=pivot*v[j];
            }

        }
    }
    Matrix<Number> aprime (N,M,"A'",v);
    Matrix<Number> bprime (N,1,"B'",vb);
    aprime.print();
    bprime.print();

    for(int r=N-1; r>0; r--){
        for(int i=r-1; i>=0; i--){
            pivot = v[i*M+r]/v[r*(1+M)];
            //std::cout<<pivot<<std::endl;
            vb[i]-=pivot*vb[r];
            for(int j=r; j>=i; j--){
                //std::cout<<"i : "<<i<<", j : "<<j<<std::endl;
                v[i*M+j]-=pivot*v[r*M+j];
            }
        }
         
    }
    for(int i=0; i<N; i++){
        vb[i]/=v[i*(M+1)];
        v[i*(M+1)]/=v[i*(M+1)];
    }

    aprime = Matrix<Number>(N,M,"A''",v);
    bprime = Matrix<Number> (N,1,"B''",vb);
    aprime.print();
    bprime.print();
    return Matrix<Number>(N,1,"X",vb);
}



void tests_Solver(){
    std::cout<<"On se propose ici de résoudre le système A.X = B à l'aide de la méthode du gradient conjugué :\n"
        << "Vous trouverez ainsi ci-après la solution du système pour différentes valeurs de A et B : \n\n";   
    std::cout<<"On commence avec des multiples de l'identité pour A :\n\n";
    Matrix<double> A {2.0*ID<double>(4)};
    A.print();
    Matrix<double> B(4,1,"B",{1,2,3,4});
    B.print();
    Matrix<double> X0(4,1,"X",{0,0,0,0});
    double eps{0.1};
    solve_grad(A, B, X0, eps).print();
    std::cout<<"\nOù l'on vérifie bien que A.X = B\nDe même avec A = 3.I :\n\n";
    A = 3.0*ID<double>(4);
    A.print();
    B.print();
    X0 = Matrix<double>(4,1,"X",{0,0,0,0});
    solve_grad(A, B, X0, eps).print();

    std::cout<<"\n==========================================\n\n";
    std::cout<<"On prend maintenant pour A une matrice symétrique positive quelconque\n\n";
    A = Matrix<double>{4,4,"A",{1,2,3,4,2,1,3,4,3,3,1,4,4,4,4,1}};
    A.print();
    B.print();
    X0 = Matrix<double>(4,1,"X",{0,0,0,0});
    Matrix<double> X{solve_grad(A, B, X0, eps)};
    X.print();
    std::cout<<"Où l'on a A.X :\n\n";
    (A*X).print();

    std::cout<<"Ou encore : \n\n";
    Matrix<double> O {4,4,"O",{1.2,8.8,3,4.3,2.5,1,3,4.3,3.6,3.5,1,1.6,4,7.8,0.2,1}};
    A = (O.transpose() + O);
    A.set_name("A");
    A.print();
    B.print();
    X0 = Matrix<double>(4,1,"X",{0,0,0,0});
    X = Matrix<double>{solve_grad(A, B, X0, eps)};
    X.print();
    std::cout<<"Où l'on a A.X :\n\n";
    (A*X).print();

    std::cout<<"\n==========================================\n\n";
    std::cout<<"On va désormais résoudre les systèmes à l'aide de la méthode du pivot (moins efficace)\n\n";
    Matrix<double> C (3,3,"A",{1,2,3,4,5,6,7,8,9});
    Matrix<double> D (3,1,"B",{1,2,3});
    C.print();
    D.print();
    X = Matrix<double>{solve_pivot(C,D)};
    X.print();
    std::cout<<"Où l'on a A.X :\n\n";
    (C*X).print();

    Matrix<double> E (4,4,"A",{1.2,2,3,4.5,5,6,7,8.7,9,0,1,2.6,3,4,5,6,7.8,8,9,0.5,1,2,3,4,5});
    Matrix<double> F (4,1,"B",{1,2,3,5,7});
    E.print();
    F.print();
    X = Matrix<double>{solve_pivot(E,F)};
    X.print();
    std::cout<<"Où l'on a A.X :\n\n";
    (E*X).print();
}