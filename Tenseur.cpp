#include "Tenseur.h"
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

//les get qui permettent d'accéder aux membres de la classe Tenseur pour une fonction membre externe à la classe

int Tenseur::getordre() {
    return ordre;
}

int * Tenseur::getdims(){
    return dims;
}

int Tenseur::getnbelts(){
    return nbelts;
}

Vecteur Tenseur::getvec(){
    return vec;
}

//fonction produit des éléments d'un tableau qui sera utilisé pour trouver la position d'un d-uplet dans le vecteur

float prod(int * tab,int i, int j){
    assert(0<=i<=j);
    float s=1;
    for (int k=i;k<j+1;k++){
        s*=tab[k-1];
    }
    return s;
}

//fonction phi permettant de trouver la position d'un d-uplet dans le vecteur

int phi ( int ordre, int * dims, int * indices){
    float s=indices[ordre-1];
    for (int i=ordre-1;i>0;i--){
        s+=prod(dims,i+1,ordre)*(indices[i-1]-1);
    }
    return s;
}

//fonction invphi permettant de trouver le d-uplet associé à la position 

void invphi ( int ordre , int *dims , int i, int * indices ){
    int f[ordre];
    f[ordre-1]=i;
    indices[ordre-1]=i%(dims[ordre-1]) + dims[ordre-1]*(i%(dims[ordre-1])==0);
    for (int k=ordre-2;k>-1;k--){
        f[k]=(f[k+1]-indices[k+1])/dims[k+1] + 1;
        indices[k]=f[k]%(dims[k]) + dims[k]*(f[k]%(dims[k])==0);
    }
}

//fonction phik utilisée pour le mode k (afin de trouver jk)

int phik ( int ordre , int *dims ,int * indices ,int mode ){
    int dims2[ordre-1];
    int indices2[ordre-1];
    for (int i=0; i<mode; i++){
        dims2[i]=dims[i];
        indices2[i]=indices[i];
    }
    for (int i=mode+1; i<ordre; i++){
        dims2[i-1]=dims[i];
        indices2[i-1]=indices[i];
    }
    return phi(ordre-1,dims2,indices2);

}

//fonction affiche de notre tenseur

void Tenseur::affiche(){
    cout<<"L'ordre du tenseur est : "<<ordre<<endl;
    cout<<"La dimensions du tenseur sont :" << endl;
    for (int k=0; k<ordre;k++){
        cout<<dims[k]<<endl;
    }
    cout<<"Voici la forme vectorisée du tenseur :"<<endl;
    for (int j=0; j<nbelts;j++){
        cout<<vec[j]<<endl;
    }
}

//premier constructeur

Tenseur::Tenseur(int * tab, int d){
    ordre=d;
    nbelts=1;
    dims = new int[d];
    for (int i=0; i<d; i++){
        nbelts*=tab[i];
        dims[i]=tab[i];
    }
    vec = Vecteur(nbelts);
}

//deuxième constructeur

Tenseur::Tenseur(int * tabr, int d, Vecteur t){
    ordre=d;
    nbelts=1;
    dims = new int[d];
    for (int i=0; i<d; i++){
        nbelts*=tabr[i];
        dims[i]=tabr[i];
    }
    vec = Vecteur(t);
}

//troisième constructeur

Tenseur::Tenseur(int * tab, int d, int mode, Matrice M){
    assert(1<=mode && mode<=d);
    ordre=d;
    nbelts=1;
    dims = new int[d];
    int indices[d];
    for (int k=0; k<d; k++){
        indices[k]=0;
    }
    for (int i=0; i<d; i++){
        nbelts*=tab[i];
        dims[i]=tab[i];
    }
    vec = Vecteur(nbelts);
    for (int n=0; n<nbelts; n++){
        invphi(d,dims,n+1,indices);
        cout<<phik(ordre,dims,indices,mode-1)<<endl;
        vec[n] = M[phik(ordre,dims,indices,mode-1)-1][indices[mode-1]-1];
    }
}

//constructeur de recopie

Tenseur::Tenseur(const Tenseur &T){
    ordre=T.ordre;
    dims = new int[ordre];
    for (int i=0;i<ordre;i++){
        dims[i]=T.dims[i];
    }
    nbelts=T.nbelts;
    vec = Vecteur(T.vec);
    
}

//surdéfinition de l'opérateur d'affectation

Tenseur & Tenseur::operator=(const Tenseur &T){ 
    if ( this !=&T){
    delete  dims;
    ordre=T.ordre;
    dims = new int[ordre];
    for (int i=0;i<ordre;i++)
        dims[i]=T.dims[i];
    }
    nbelts=T.nbelts;
    vec = Vecteur(T.vec);
    return * this ;
}

//destructeur

Tenseur::~Tenseur(){
    delete dims;
}

//surdéfinition de l'opérateur +

Tenseur Tenseur::operator+(Tenseur T){
    for (int i=0; i<T.ordre; i++){
        assert(dims[i]==T.dims[i]);
    }
    int nrbelts=T.nbelts;
    Vecteur vecr(vec + T.vec);
    return Tenseur(dims,ordre,vecr);

}

//surdéfinition de l'opérateur -

Tenseur Tenseur::operator-(Tenseur T){
    for (int i=0; i<T.ordre; i++){
        assert(dims[i]==T.dims[i]);
    }
    int nrbelts=T.nbelts;
    Vecteur vecr = vec - T.vec;
    return Tenseur(dims,ordre,vecr);
}

//surdéfinition de l'opérateur []

float & Tenseur::operator[]( int i){
    return vec[i];
}

//fonction membre mode

Matrice Tenseur::mode(int mode){
    assert(1<=mode && mode<=ordre);
    int dims2[ordre-1];
    int indices2[ordre-1];
    for (int i=0; i<mode-1; i++){
        dims2[i]=dims[i];
        indices2[i]=0;
    }
    for (int i=mode; i<ordre; i++){
        dims2[i-1]=dims[i];
        indices2[i-1]=0;
    }
    Matrice M(dims[mode-1],nbelts/dims[mode-1]);
    for (int i=0; i<dims[mode-1]; i++){
        for (int j=0; j<nbelts/dims[mode-1]; j++){
            invphi(ordre-1,dims2,j+1,indices2);
            int indices3[ordre];
            for (int m=0;m<mode-1;m++){
                indices3[m]=indices2[m];
            }
            indices3[mode-1]=i+1;
            for (int m=mode;m<ordre;m++){
                indices3[m]=indices2[m-1];
            }
            M[j][i]=vec[phi(ordre,dims,indices3)-1];
        }
    }
    return M;
}

//fonction pmod effectuant le produit k-modal d'un tenseur par une matrice

Tenseur pmod( Tenseur T, Matrice M, int mode){
    int ordre = T.getordre();
    int m = M.getdim0();
    int n = M.getdim1();
    int dims[ordre];
    for (int i=0; i<ordre; i++){
        dims[i]=T.getdims()[i];
    }
    dims[mode-1]=m;
    int nbelts;
    nbelts = prod(dims,1,ordre);
    Vecteur vec(nbelts);
    int indices[ordre];
    int indices2[ordre];
    int i;
    for (int k=0; k<nbelts; k++){
        invphi(ordre,dims,k+1,indices);
        i=indices[mode-1];
        for (int m=0; m<ordre;m++){
            indices2[m]=indices[m];
        }
        for (int j=1; j<n+1; j++){
            indices2[mode-1]=j;
            vec[k]+=M[j-1][i-1]*T.getvec()[phi(ordre,T.getdims(),indices2)-1];
        }
    }
    
    Tenseur U(dims,ordre,vec);
    return U;
}


