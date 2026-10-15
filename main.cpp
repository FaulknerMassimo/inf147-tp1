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


/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {



    //retour obligatoire si le "main()" est de type "int"
	return EXIT_SUCCESS;
}