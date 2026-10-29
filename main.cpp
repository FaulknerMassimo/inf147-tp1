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
    t_pile pile_graham;
    int pos_pt_min;     //position du point minimal dans le tableau

    srand(time(NULL));    //initialise le générateur “rand()” (on doit inclure <time.h>)

    tab_pts = (t_point *) malloc(TAILLE * sizeof(t_point));
    assert(tab_pts);
    init_tab_alea(tab_pts, TAILLE, MAXX, MAXY);

    pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);

    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
    trier_pts(tab_pts, TAILLE);

    mode_graphique();
    afficher_pts_en_ordre(tab_pts, TAILLE);
    pause_ecran();

    nettoyer_ecran();

    for(int i = 0; i < TAILLE; i++) {
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
    }

    pile_graham = init_pile(TAILLE);
    algo_Graham_scan(tab_pts, TAILLE, &pile_graham);
    afficher_solution(&pile_graham);
    pause_ecran();

    fermer_mode_graph();

    liberer_pile(&pile_graham);
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
                         tab_pts[0].posx, tab_pts[0].posy);
        }
    }
}


/*=========================================================*/
/*                  ALGO_GRAHAM_SCAN                       */
/*     fonction qui complete l'algorithme de Graham        */
/*=========================================================*/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham) {
    push(pile_Graham, &tab_pts[0]);
    push(pile_Graham, &tab_pts[1]);
    push(pile_Graham, &tab_pts[2]);

    // Ligne de p0 à p1 et de p1 à p2
    dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
    dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);

    delai_ecran(300);

    for (int i = 3; i < nb_pts; i++) {
        t_element pB, pA;
        get_sommet(pile_Graham, &pB);
        get_suiv_sommet(pile_Graham, &pA);

        // Tant que le segment tourne vers la droite (produit vectoriel > 0)
        while (get_nb_elements(pile_Graham) >= 2 && prod_vectoriel(&pA, &pB, &tab_pts[i]) > 0) {
            pop(pile_Graham); // Retirer pB de l'enveloppe
            // Effacer la ligne qui relie pA à pB
            effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
            delai_ecran(100);

            get_sommet(pile_Graham, &pB);
            get_suiv_sommet(pile_Graham, &pA);
        }

        push(pile_Graham, &tab_pts[i]);
        dessiner_lig(pB.posx, pB.posy, tab_pts[i].posx, tab_pts[i].posy);
        delai_ecran(100);
    }
    return get_nb_elements(pile_Graham);

}


/*=========================================================*/
/*                 AFFICHER_SOLUTION                       */
/*           fonction qui affiche les segments             */
/*            qui forment l'enveloppe convexe              */
/*=========================================================*/
void afficher_solution(t_pile * pile_graham) {
    printf("Nombre de points dans l'enveloppe : %d\n", get_nb_elements(pile_graham));

    if (pile_graham == NULL || get_nb_elements(pile_graham) == 0) {
        return;
    }

    t_element pt_fin = pile_graham->items[0];
    t_element p0 = pt_fin;
    printf("Point : %d\n", p0.position);

    for (int i = 1; i <= pile_graham->sommet; i++) {
        t_element p1 = pile_graham->items[i];
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
        printf("Point : %d\n", p1.position);
        p0 = p1;
    }

    // Fermer l'enveloppe
    dessiner_lig(p0.posx, p0.posy, pt_fin.posx, pt_fin.posy);
    printf("Point (fin) : %d\n", pt_fin.position);
}