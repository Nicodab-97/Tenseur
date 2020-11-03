#include "Matrice.h"
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

int Matrice::getdim0(){
    return dims[0];
}

int Matrice::getdim1(){
    return dims[1];
}

//affichage de la matrice

void Matrice::affiche(){
    cout<<"Les dimensions de la matrice sont : "<<dims[0]<<" et "<<dims[1]<<endl;
    for(int j=0;j<dims[0];j++){
        for(int i=0;i<dims[1];i++){
                   cout<<mat[i][j];
                   cout<<"  ";
                   
                   }
        cout<<endl;
        }
}

//premier constructeur prenant en argument les dimensions de la matrice

Matrice::Matrice( int n,  int m){
    dims[0]=n;
    dims[1]=m;
    mat = new Vecteur[m];
    for (int i=0;i<m;i++){;
        mat[i]=  Vecteur(n);
    }
}

//second constructeur renvoyant une matrice diagonale dont les éléments diagonaux correspondent aux coordonnées du vecteur en argument.

Matrice::Matrice(Vecteur v){
    dims[0]=v.dim;
    dims[1]=v.dim;
    mat = new Vecteur[dims[1]];
    for (int i=0;i<dims[1];i++){;
            mat[i]=  Vecteur(dims[0]);
    }
    for (int i=0;i<dims[1];i++){;
            mat[i][i]= v[i];
    }

}

//troisième constructeur prenant en argument un tableau de vecteurs et sa taille.

Matrice::Matrice(Vecteur * vec, int n){
    mat = new Vecteur[n];
    dims[0]=vec[0].dim;
    dims[1]=n;
    for (int i=0;i<n;i++){
        mat[i]=vec[i];
    }

}

//constructeur de recopie.

Matrice::Matrice(const Matrice &M){
    dims[0]=M.dims[0];
    dims[1]=M.dims[1];
    mat=new Vecteur[dims[1]];
    for (int i=0;i<dims[1];i++){
        mat[i]=M.mat[i];
    }
}

//définition du destructeur.

Matrice::~Matrice(){
    delete [] mat;
}

//surdéfinition de l'opérateur d'affectation.

Matrice & Matrice::operator =(const Matrice &M){
    if ( this !=&M){
    delete [] mat;
    dims[0] = M.dims[0] ;
    dims[1] = M.dims[1] ;
    mat = new Vecteur[dims[1]];
    for( int i =0;i< dims[1] ;i++)
        mat[i] = M.mat[i];
    }
    return * this ;
}

//surdéfinition de l'opérateur + 

Matrice Matrice::operator+(Matrice M){
    assert(dims[0]==M.dims[0] && dims[1]==M.dims[1]); //matrices de même dimentions.
    Vecteur * matr = new Vecteur[dims[1]];
    for( int i =0;i< dims[1] ;i++){
        matr[i]= mat[i] + M.mat[i];
    }
    Matrice R(matr,dims[1]);
    return R;
    
}

//surdéfinition de l'opérateur -

Matrice Matrice::operator-(Matrice M){
    assert(dims[0]==M.dims[0] && dims[1]==M.dims[1]); //matrices de même dimentions.
    Vecteur * matr = new Vecteur[dims[1]];
    for( int i =0;i< dims[1] ;i++){
        matr[i]= mat[i] - M.mat[i];
    }
    Matrice R(matr,dims[1]);
    return R;
    
}

//surdéfinition de l'opérateur [] retournant un objet vecteur.

Vecteur & Matrice::operator [](int i){
    return mat[i];
}

//surdéfinition de l'opérateur *

Matrice Matrice::operator*(Matrice M){
    assert(dims[1]==M.dims[0]); //le nombre de colonnes de la matrice de gauche doit correspondre au nombre de lignes de la matrice de droite.
    Vecteur * matr = new Vecteur[M.dims[1]];
    for (int i=0;i<M.dims[1];i++){
        matr[i]= Vecteur(dims[0]);
        for (int j=0;j<dims[0];j++){
            for (int k=0;k<dims[1];k++){
                matr[i][j]+=mat[k][j]*M.mat[i][k];
            }
            
        }
    }
    Matrice R(matr,M.dims[1]);
    return R;

}

//fonction transpose.

Matrice Matrice::transpose(){
    Vecteur * matr = new Vecteur[dims[0]];
    for (int i=0; i<dims[0]; i++){
        matr[i] = Vecteur(dims[1]);
        for (int j=0; j<dims[1]; j++){
            matr[i][j] = mat[j][i];
        }
    }
    Matrice R(matr,dims[0]);
    return R;
}

//fonction retournant le produit de la matrice appelante par le vecteur donné en argument.

Vecteur  Matrice::mvprod(Vecteur t){
    assert(dims[1]==t.dim); //le nombre de colonnes de la matrice doit correspondre à la dimension du vecteur donné en argument.
    Vecteur u(dims[0]);
    for (int i=0; i<dims[0];i++){
        for (int j=0;j<dims[1]; j++){
            u[i]+=mat[j][i]*t[j];
        }
        
    }
    return u;
}

//fonction permettant de retourner une sous matrice de la matrice de départ.

Matrice Matrice::submat(int il, int jl, int ic, int jc){
    assert(il<=jl && ic<=jc);
    Vecteur * matr = new Vecteur[jc-ic+1];
    for (int i=0; i<jc-ic+1;i++){
        matr[i]=Vecteur(jl-il+1);
        for (int j=0; j<jl-il+1;j++){
            matr[i][j]=mat[ic+i-1][il+j-1];
        }
    }
    Matrice R(matr,jc-ic+1);
    return R;

}

void  Matrice::submat1(int il, int jl, int ic, int jc, const Matrice &M){
    for (int k=ic-1; k<jc; k++){
        for (int m=il-1; m<jl; m++){
            mat[k][m] = M.mat[k-ic+1][m-il+1];
        }
    }
}

//fonction retournant la norme de Frobenius d'une matrice.

float norm(Matrice M){
    float s=0.0;
    for (int i=0; i<M.dims[1]; i++){
        for (int j=0; j<M.dims[0];j++){
            s+=M.mat[i][j]*M.mat[i][j];
        }
    }
    return sqrt(s);
}

//surdéfinition de l'opérateur * permettant de multiplier la matrice donnée en argument par un scalaire.

Matrice operator*(float s,const Matrice &M){
    int dims[2];
    dims[0]=M.dims[0];
    dims[1]=M.dims[1];
    Vecteur * matr = new Vecteur[dims[1]];
    for (int i=0;i<dims[1];i++){
        matr[i]=s*M.mat[i];
    }
    Matrice R(matr,dims[1]);
    return R;
}

//fonction retournant le produit externe de deux vecteurs

Matrice outer(Vecteur u, Vecteur v){
    assert(u.getdim()==v.getdim());
    int dim= u.getdim();
    Vecteur *matr= new Vecteur[dim];
    for (int i=0; i<dim; i++){
        matr[i]=Vecteur(dim);
        for (int j=0; j<dim; j++){
            matr[i][j]=u[j]*v[i];
        }
    }
    return Matrice(matr,dim);
}



