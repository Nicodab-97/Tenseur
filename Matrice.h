
#include "Vecteur.h"

class Matrice
{
    int dims[2];
    Vecteur* mat;

public:
    void affiche2();
    Matrice(int, int);
    /*Matrice(Vecteur);
        Matrice(Vecteur *);
        ~Matrice();
        Matrice(const Matrice &);
        Matrice & operator =( const Matrice &);
        Vecteur & operator []( int );
        Matrice  operator+(Matrice );
        Matrice  operator-(Matrice );
        Matrice  operator*(Matrice ); */
};