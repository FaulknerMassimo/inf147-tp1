/*
 Programme : Devoir 1
 Par    : Massimo Faulkner
 Date   : 15 octobre 2026

*/

/*=========================================================*/

//Permet de desactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles a inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

typedef struct {
    int posx, posy; //coordonnees x, y du point dans le plan
    double rad;     //angle polaire relatif au point minimal
    double dist;    //la distance relative au point minimal
    int position;   //position-tableau du point suite au tri
} t_point;

/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/

/*                       DISTANCE                          */
/*      fonction qui calcule la distance euclidienne       */
/*                   entre deux points                     */
/* ENTREE: points pA et pB qu'on veut calculer la distance */
/*        SORTIE: la distance entre les deux points        */
double distance(t_point * pA, t_point * pB);


/*                    PROD_VECTORIEL                       */
/*       fonction qui calcule le produit vectoriel         */
/*                   de deux vecteurs                      */
/*   ENTREE: points p0, p1 et p2 qui forment les vecteurs  */
/*        qu'on veut calculer le produit vectoriel         */
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2);


/*                    COORD_POLAIRE                        */
/*    fonction qui calcule l'angle polaire d'un vecteur    */
/*           par rapport a l'axe horizontale               */
/*     ENTREE: points pA et pB qui forment le vecteur      */
/*   qu'on veut trouver l'angle et le point de reference   */
/*   h_ref qui sera toujours a la verticale du point pA    */
double coord_polaire(t_point * pA, t_point pB, t_point * h_ref);


/*                        ALEA                             */
/*            fonction qui retourne un entier              */
/*              aleatoire entre deux bornes                */
/* ENTREE: les bornes min et max entre l'entier aleatoire  */
/*              SORTIE: l"entier aleatoire                 */
int alea(int min, int max);


/*                    INIT_TAB_ALEA                        */
/*      fonction qui initialise tous les points du         */
/*        tableau avec des coordonnees aleatoires          */
/*     ENTREE: tableau tab_pts[], la taille du tableau,    */
/*      la coordonnee maximale de x et la coordonnee       */
/*                   maximale de y                         */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);



/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {



    //retour obligatoire si le "main()" est de type "int"
	return EXIT_SUCCESS;
}


/*=========================================================*/
/*                       DISTANCE                          */
/*      fonction qui calcule la distance euclidienne       */
/*                   entre deux points                     */
/*=========================================================*/
double distance(t_point * pA, t_point * pB) {
    return sqrt(pow(pB.posx - pA.posx, 2) + pow(pB.posy - pA.posy, 2));
}


/*=========================================================*/
/*                    PROD_VECTORIEL                       */
/*       fonction qui calcule le produit vectoriel         */
/*                   de deux vecteurs                      */
/*=========================================================*/
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2) {
    double a = p2.posx - p0.posx;
    double b = p1.posx - p0.posx;
    double c = p2.posy - p0.posy;
    double d = p1.posy - p0.posy;

    return a*d - b*c;
}


/*=========================================================*/
/*                    COORD_POLAIRE                        */
/*    fonction qui calcule l'angle polaire d'un vecteur    */
/*           par rapport a l'axe horizontale               */
/*=========================================================*/
double coord_polaire(t_point * pA, t_point pB, t_point * h_ref) {
    double dist = distance(pA, pB);
    double angle = asin((pB.posy - pA.posy)/dist);
    produit = prod_vectoriel(pA, h_ref, pB);

    if (produit > 0) {
        return angle;
    }
    else if (produit < 0) {
        return 2*((pi()/2) - angle) + angle;
    }
    else {
        return 90.0;
    }
}


/*=========================================================*/
/*                        ALEA                             */
/*            fonction qui retourne un entier              */
/*              aleatoire entre deux bornes                */
/*=========================================================*/
int alea(int min, int max) {
    return (rand() % (max - min + 1) + min);
}


/*=========================================================*/
/*                    INIT_TAB_ALEA                        */
/*      fonction qui initialise tous les points du         */
/*        tableau avec des coordonnees aleatoires          */
/*=========================================================*/
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {

}