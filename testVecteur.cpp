#include "Vecteur.h"
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    float tab1[3]={1.0,1.0,1.0}; //crétaion d'un tableau [1,1,1]
    Vecteur u(tab1,3);
    cout<<"Le vecteur u : "<<endl; //construction d'une classe vecteur avec le second constructeur pour tab
    u.affiche();
    float tab2[4]={3.0,4.0,0.0,0.0};
    Vecteur v(tab2,4);
    cout<<"Le vecteur v ="<<endl;
    v.affiche();
    Vecteur t(u); 
    cout<<"Copie de u dans un vecteur t "<<endl;
    u[2]=0.0; 
    cout<<"Modification de u[2]=0 désormais"<<endl;
    cout<<"Le vecteur  u : "<<endl;
    u.affiche();
    cout<<"Le vecteur t : "<<endl;
    t.affiche();
    cout<<"Le produit scalaire de v par lui même est : "<< dot(v,v)<<endl;
    cout<<"La norme de v est : "<<norm(v)<<endl;
    cout<<"Le vecteur v normailsé : "<<endl;
    ((1/norm(v))*v).affiche(); // valeur de v normalisée
    Vecteur w(4);
    w=v.subvec(2,4);
    cout<<"Le vecteur v tronqué renommé w : "<<endl;
    w.affiche();
    cout<<"La somme de u et w : "<<endl;
    (u+w).affiche();
    cout<<"La différence de u et w : "<<endl;
    (u-w).affiche();
}

