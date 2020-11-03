#include "Matrice.h"
#include <iostream>
#include <cmath>
using namespace std;



int main(){
    float tab11[3]={1.0,1.0,0.0}; 
    Vecteur u1(tab11,3);
    float tab12[3]={-1./2,2.,-1.};
    Vecteur u2(tab12,3);
    float tab13[3]={0.0,-1.,1.};
    Vecteur u3(tab13,3);
    Vecteur mat1[3]={u1,u2,u3};
    Matrice A(mat1,3);
    cout<<"La Matrice A : "<<endl;
    A.affiche(); //affichage de la matrice A
    float tab21[2]={-2.0,0.0};
    Vecteur v1(tab21,2);
    float tab22[2]={3.0,1.0};
    Vecteur v2(tab22,2);
    Vecteur mat2[2]={v1,v2};
    Matrice B(mat2,2);
    cout<<"La Matrice B : "<<endl;
    B.affiche(); //affichage de la matrice B
    Matrice C(B); // recopie de B dans une matrice C
    B[1][0]=0.0; //on modifie l'élément B_1,2
    cout<<"Modification de l'élément B_1,2=0 "<<endl;
    cout<<"La Matrice B : "<<endl;
    B.affiche();//affichage de la nouvelle matrice B
    cout<<"La Matrice C : "<<endl;
    C.affiche();//affichage de la matrice C qui correspond à l'ancienne matrice B
    Matrice D(3,2);
    D=A.submat(1,3,1,2);
    cout<<"La Matrice D : "<<endl;
    D.affiche();// affichage de D qui est une sous matrice de A
    float tab3[3]={3.0,2.0,1.0};
    Vecteur v(tab3,3); //création du vecteur v
    Matrice E(v);
    cout<<"La Matrice E : "<<endl;
    E.affiche(); //affichage de E matrice diagonale dont les éléments diagonaux sont les composantes de v.
    cout<<"La Matrice B+C : "<<endl;
    (B+C).affiche();// affichage de la matrice B+C
    cout<<"La Matrice B-C : "<<endl;
    (B-C).affiche();// affichage de la matrice B-C
    cout<<"La Matrice D*C : "<<endl;
    (D*C).affiche();//affichage de la matrice D*C
    cout<<"La norme de Frobenius de C est : "<<norm(C)<<endl;
    cout<<"La matrice 0.5*(B+B^T) "<<endl;
    (0.5*(B+B.transpose())).affiche();
}