#include "TenseurSVD.h"

//premier constructeur

TenseurSVD::TenseurSVD(int * dims, int ordre, Matrice * matr) : Tenseur(dims,ordre){
    for (int k=0;k<ordre;k++){
        mat[k]=matr[k];
    }
}

//second constructeur

TenseurSVD::TenseurSVD(int * dims, int ordre, Vecteur t, Matrice * matr) : Tenseur(dims,ordre,t) {
    for (int k=0;k<ordre;k++){
        mat[k]=matr[k];
    }
}

//troisième constructeur

TenseurSVD::TenseurSVD(int * dims, int ordre, int mode, Matrice M, Matrice * matr) : Tenseur(dims,ordre,mode,M){
    for (int k=0;k<ordre;k++){
        mat[k]=matr[k];
    }
}

//destructeur

TenseurSVD::~TenseurSVD() {
    delete [] mat;
}

//constructeur de recopie

TenseurSVD::TenseurSVD( TenseurSVD &T) : Tenseur(T.getdims(),T.getordre(),T.getvec()){
    for (int i=0;i<T.getordre();i++){
        mat[i]=T.mat[i];
    }
}

//surcharge de l'opérateur d'affectation

TenseurSVD & TenseurSVD::operator=(TenseurSVD &T){
    if ( this !=&T){
    delete  mat;
    *this=T;
    for (int i=0;i<T.getordre();i++)
        mat[i]=T.mat[i];
    }
    return * this;
}

//retourne le coeur du tenseur

Tenseur TenseurSVD::tenseurtotal(){
    Tenseur S = * this;
    for (int i=0;i<this->getordre();i++){
        S=pmod(S,mat[i].transpose(),i+1);
    }
    return S; 
}

//fonction hosvd

TenseurSVD hosvd(Tenseur T){
    //to be continued
}