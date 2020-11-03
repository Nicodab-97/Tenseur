#include "Matrice.h"

class Tenseur{
    int ordre;
    int * dims;
    int nbelts;
    Vecteur vec;
    public:
        void affiche();
        Tenseur(int * , int);
        Tenseur(int *, int, Vecteur);
        Tenseur(int *, int, int, Matrice);
        ~Tenseur();
        Tenseur(const Tenseur &);
        Tenseur & operator =( const Tenseur &);
        Tenseur  operator+(Tenseur );
        Tenseur  operator-(Tenseur );
        float & operator []( int );
        Matrice mode(int);
        int getordre();
        int * getdims();
        int getnbelts();
        Vecteur getvec();
        

};

Tenseur pmod(Tenseur,Matrice, int);