/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	main.cpp                                                        */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Fichier du programme principal                     */
/********************************************************************/

//Permet de desactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles a inclure 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tab_points.h"
#include "affichage.h"


/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

// Taille du tableau / nombre de points
#define TAILLE 20

/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*                 AFFICHER_PTS_EN_ORDRE                   */
/*       fonction qui affiche les points a l'ecran         */
/*          ENTREE: tableau des points tab_pts[]           */
/*                et la taille du tableau                  */
void afficher_pts_en_ordre(t_point tab_pts[], int taille);


/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {

    //A FAIRE
    printf("test");

    //assert()

    //free()

    //retour obligatoire si le "main()" est de type "int"
	return EXIT_SUCCESS;
}


/*=========================================================*/
/*                 AFFICHER_PTS_EN_ORDRE                   */
/*       fonction qui affiche les points a l'ecran         */
/*=========================================================*/
void afficher_pts_en_ordre(t_point tab_pts[], int taille) {
    for(int i = 0; i < taille; i++) {
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
        tab_pts[i].position = i;

        if (i =! 0) {
            dessiner_lig(tab_pts[i].posx, tab_pts[i].posy,
                         tab_pts[i-1].posx, tab_pts[i-1].posy);
        }
    }
}