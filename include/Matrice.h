
#include "Vecteur.h"

class Matrice{
    int dims[2];
    Vecteur* mat;
    friend class Tenseur;
    public:
        void affiche();
        Matrice(int, int);
        Matrice(Vecteur);
        Matrice(Vecteur *, int);
        ~Matrice();
        Matrice(const Matrice &);
        Vecteur & operator []( int );
        Matrice & operator =( const Matrice &);
        Matrice  operator+(Matrice );
        Matrice  operator-(Matrice );
        Matrice  operator*(Matrice);
        Matrice transpose();
        Vecteur  mvprod( Vecteur );
        Matrice submat(int, int, int, int);
        void submat1(int, int, int, int,const Matrice &);//rajouté pour les algorithmes de la partie 3
        //permet de modifier une partie d'une matrice

        friend float norm(Matrice);
        friend Matrice operator*(float, const Matrice &);
        int getdim0();
        int getdim1();

};


Matrice outer(Vecteur , Vecteur );