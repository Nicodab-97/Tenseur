class Vecteur {
    int dim;
    float * tab;
    public:
        void affiche();
        Vecteur(int);
        ~Vecteur();
        Vecteur(const Vecteur &);
        Vecteur & operator =( const Vecteur &);
        Vecteur & operator+(Vecteur &);
        Vecteur & operator-(Vecteur &);
        Vecteur & operator*(float, Vecteur &);
        /*Vecteur(float *,int);
        int & operator []( int );
        friend Vecteur operator*(float, Vecteur t);
        float subvec(Vecteur t, int i, int j);
        float dot(Vecteur , Vecteur);
        float norm(Vecteur);*/
};

