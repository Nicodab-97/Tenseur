
class Vecteur {
    int dim;
    float * tab;
    friend class Matrice;
    friend class Tenseur;
    public:
        void affiche();
        Vecteur();
        Vecteur(int);
        Vecteur(float *,int);
        ~Vecteur();
        Vecteur(const Vecteur &);
        Vecteur & operator =( const Vecteur &);
        Vecteur  operator+(Vecteur );
        Vecteur  operator-(Vecteur );
        float & operator []( int );
        Vecteur  subvec(int i, int j);
        void subvec1(int i, int j,const  Vecteur &); //rajouté pour les algorithmes de la partie 3
        //permet de modifier une partie d'un vecteur
        
        friend float dot(Vecteur , Vecteur);
        friend float norm(Vecteur);
        friend Vecteur operator*(float,const  Vecteur &);
        int getdim();
        
};



             