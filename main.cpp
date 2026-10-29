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
#include <time.h>
#include <assert.h>
#include "tab_points.h"
#include "affichage.h"
#include "pile.h"


/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

// Taille du tableau / nombre de points
#define TAILLE 20

#define MAXX 1400

#define MAXY 800

/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*                 AFFICHER_PTS_EN_ORDRE                   */
/*       fonction qui affiche les points a l'ecran         */
/*          ENTREE: tableau des points tab_pts[]           */
/*                et la taille du tableau                  */
void afficher_pts_en_ordre(t_point tab_pts[], int taille);

/*                  ALGO_GRAHAM_SCAN                       */
/*     fonction qui complete l'algorithme de Graham        */
/* ENTREE: le tableau de points, le nombre de points et    */
/*        le pointeur de la pile pour le resultat          */
/*   SORTIE: le nombre d'elements dans la pile_Graham      */
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham);


/*                 AFFICHER_SOLUTION                       */
/*           fonction qui affiche les segments             */
/*            qui forment l'enveloppe convexe              */
/*   ENTREE: la pile de Graham qui contient les segments   */
void afficher_solution(t_pile * pile_Graham);


/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {
    t_point *tab_pts = NULL;
    t_point h_ref;
    int pos_pt_min;     //position du point minimal dans le tableau

    srand(time(NULL));    //initialise le générateur “rand()” (on doit inclure <time.h>)

    tab_pts = (t_point *) malloc(TAILLE * sizeof(t_point));
    assert(tab_pts);

    init_tab_alea(tab_pts, TAILLE, MAXX, MAXY);

    pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);

    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);

    trier_pts(tab_pts, TAILLE);

    free(tab_pts);

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

        if (i != 0) {
            dessiner_lig(tab_pts[i].posx, tab_pts[i].posy,
                         tab_pts[i-1].posx, tab_pts[i-1].posy);
        }
    }
}


/*=========================================================*/
/*                  ALGO_GRAHAM_SCAN                       */
/*     fonction qui complete l'algorithme de Graham        */
/*=========================================================*/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham) {
    //A FAIRE
    return 1;
}


/*=========================================================*/
/*                 AFFICHER_SOLUTION                       */
/*           fonction qui affiche les segments             */
/*            qui forment l'enveloppe convexe              */
/*=========================================================*/
void afficher_solution(t_pile * pile_Graham) {
    //A FAIRE
}