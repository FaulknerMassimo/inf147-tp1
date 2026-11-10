/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	main.cpp                                                        */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Fichier du programme principal                     */
/********************************************************************/

//Permet de desactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "tab_points.h"
#include "affichage.h"
#include "pile.h"
#include "interactions.h"


/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

//taille du tableau
#define TAILLE 20

//nombre de test par moyenne
#define NB_TESTS 10000

//nombre de points pour la premiere simulation
#define NB_PTS_MIN 5

//nombre de points pour la derniere simulation
#define NB_PTS_MAX 200

//incements du nombre de points
#define PAS_NB_PTS 5

//nom du fichier-log des moyennes
#define NOM_FICHIER_LOG "log_moyennes.txt"

//delai-ecran apres chaque ligne dessinee
#define DELAI_ECRAN 300


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
/*   ENTREE: le tableau de points, le nombre de points,    */
/*     le pointeur de la pile pour le resultat et le       */
/*   mode d'affichage (1 = avec affichages, 0 = sans)      */
/*   SORTIE: le nombre d'elements dans la pile_Graham      */
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham,
                     int mode_aff);


/*                 AFFICHER_SOLUTION                       */
/*           fonction qui affiche les segments             */
/*            qui forment l'enveloppe convexe              */
/*   ENTREE: la pile de Graham qui contient les segments   */
void afficher_solution(t_pile * pile_Graham);


/*                 SIMULATION_MOYENNE                      */
/*    fonction qui effectue "nb_tests" parcours de Graham  */
/*     avec "nb_pts" points aleatoires, sans affichages    */
/*  ENTREE: le nombre de points et le nombre de tests      */
/*  SORTIE: la moyenne du nombre de points de l'enveloppe  */
double simulation_moyenne(int nb_pts, int nb_tests);


/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {
    t_point *tab_pts = NULL;   //tableau dynamique des points
    t_point h_ref;             //point de reference horizontal
    t_pile pile_graham;        //pile qui contient l'enveloppe convexe
    int pos_pt_min;            //position du point minimal dans le tableau
    int mode;                  //mode d'execution choisi par l'usager
    int nb_pts;                //nombre de points dans le tableau
    double moyenne;            //moyenne du nombre de points de l'enveloppe
    FILE * fichier;            //fichier-texte des points (mode fichier)
    FILE * f_log;              //fichier-log des moyennes (mode simulation)

    //initialise le generateur de nombres aleatoires
    srand(time(NULL));

    //demande le mode d'execution a l'usager
    mode = demander_mode();

    if (mode == MODE_SIMULATION) {
        //ouvre le fichier-log en ecriture et valide l'ouverture
        f_log = fopen(NOM_FICHIER_LOG, "wt");
        assert(f_log);

        //pour chaque nombre de points de NB_PTS_MIN a NB_PTS_MAX
        for (nb_pts = NB_PTS_MIN; nb_pts <= NB_PTS_MAX; nb_pts += PAS_NB_PTS) {
            //calcule la moyenne sur NB_TESTS simulations
            moyenne = simulation_moyenne(nb_pts, NB_TESTS);

            //affiche le resultat a la console et l'ecrit dans le fichier-log
            printf("%d  %.2f\n", nb_pts, moyenne);
            fprintf(f_log, "%d  %.2f\n", nb_pts, moyenne);
        }

        //ferme le fichier-log
        fclose(f_log);
        printf("Resultats enregistres dans \"%s\"\n", NOM_FICHIER_LOG);
    }
    else {
        if (mode == MODE_ALEA) {
            nb_pts = TAILLE;

            //alloue le tableau et valide l'allocation
            tab_pts = (t_point *) malloc(nb_pts * sizeof(t_point));
            //initialise les points avec des coordonnees aleatoires
            init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

        } else if (mode == MODE_FICHIER) {
            //demande un fichier valide a l'usager
            fichier = choisir_fichier();

            //lis les points du fichier
            tab_pts = lire_points(fichier, &nb_pts);
        }

        //trouve le point minimal
        pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);

        //place ce point au debut et cree le point de reference horizontal
        h_ref = placer_pt_reference(tab_pts, pos_pt_min);

        //calcule les coordonnees polaires de chaque point, puis les trie
        calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
        trier_pts(tab_pts, nb_pts);

        //ouvre le mode graphique et affiche les points en ordre polaire
        mode_graphique();
        afficher_pts_en_ordre(tab_pts, nb_pts);
        pause_ecran();

        //efface l'ecran pour recommencer sans les vecteurs polaires
        nettoyer_ecran();

        //redessine seulement les points
        for(int i = 0; i < nb_pts; i++) {
            dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);
        }

        //initialise la pile selon le nombre de points
        pile_graham = init_pile(nb_pts);

        //fait le parcours de Graham avec les affichages
        algo_Graham_scan(tab_pts, nb_pts, &pile_graham, 1);

        //affiche l'enveloppe finale puis attend une touche
        afficher_solution(&pile_graham);
        pause_ecran();

        //ferme la fenetre graphique pour voir la console
        fermer_mode_graph();

        //libere la pile et le tableau de points
        liberer_pile(&pile_graham);
        free(tab_pts);
    }

    //retour obligatoire si le "main()" est de type "int"
	return EXIT_SUCCESS;
}


/*=========================================================*/
/*                 AFFICHER_PTS_EN_ORDRE                   */
/*       fonction qui affiche les points a l'ecran         */
/*=========================================================*/
void afficher_pts_en_ordre(t_point tab_pts[], int taille) {
    for(int i = 0; i < taille; i++) {
        //dessine le point avec son numero
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, i);

        //memorise la position du point dans le tableau
        tab_pts[i].position = i;

        //relie chaque point au point minimal
        if (i != 0) {
            dessiner_lig(tab_pts[i].posx, tab_pts[i].posy,
                         tab_pts[0].posx, tab_pts[0].posy);

            //delai-ecran apres chaque ligne
            delai_ecran(DELAI_ECRAN);
        }
    }
}


/*=========================================================*/
/*                  ALGO_GRAHAM_SCAN                       */
/*     fonction qui complete l'algorithme de Graham        */
/*=========================================================*/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham,
                     int mode_aff) {
    //empile les trois premiers points (toujours un virage a gauche)
    push(pile_Graham, &tab_pts[0]);
    push(pile_Graham, &tab_pts[1]);
    push(pile_Graham, &tab_pts[2]);

    if (mode_aff) {
        // Ligne de p0 à p1 et de p1 à p2
        dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
        delai_ecran(DELAI_ECRAN);
        dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
        delai_ecran(DELAI_ECRAN);
    }

    //traite chaque point restant, de p3 a pNB-1
    for (int i = 3; i < nb_pts; i++) {
        t_element pB, pA;   //sommet de la pile et element sous le sommet

        //copie le sommet (pB) et l'element suivant (pA) de la pile
        get_sommet(pile_Graham, &pB);
        get_suiv_sommet(pile_Graham, &pA);

        // Tant que le segment tourne vers la droite (produit vectoriel > 0)
        while (get_nb_elements(pile_Graham) >= 2 && prod_vectoriel(&pA, &pB, &tab_pts[i]) > 0) {
            pop(pile_Graham); // Retirer pB de l'enveloppe

            if (mode_aff) {
                // Effacer la ligne qui relie pA à pB
                effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
                delai_ecran(DELAI_ECRAN);
            }

            //met a jour pB et pA avec le nouveau sommet
            get_sommet(pile_Graham, &pB);
            get_suiv_sommet(pile_Graham, &pA);
        }

        //empile le point courant
        push(pile_Graham, &tab_pts[i]);

        if (mode_aff) {
            //dessine la ligne de pB au nouveau point
            dessiner_lig(pB.posx, pB.posy, tab_pts[i].posx, tab_pts[i].posy);
            delai_ecran(DELAI_ECRAN);
        }
    }

    //retourne le nombre de points de l'enveloppe
    return get_nb_elements(pile_Graham);

}


/*=========================================================*/
/*                 AFFICHER_SOLUTION                       */
/*           fonction qui affiche les segments             */
/*            qui forment l'enveloppe convexe              */
/*=========================================================*/
void afficher_solution(t_pile * pile_graham) {
    //affiche le nombre de points de l'enveloppe
    printf("Nombre de points dans l'enveloppe : %d\n", get_nb_elements(pile_graham));

    //rien a afficher si la pile est invalide ou vide
    if (pile_graham == NULL || get_nb_elements(pile_graham) == 0) {
        return;
    }

    //le premier point est aussi le dernier de l'enveloppe
    t_element pt_fin = pile_graham->items[0];
    t_element p0 = pt_fin;
    printf("Point : %d\n", p0.position);

    //relie chaque point au suivant dans la pile
    for (int i = 1; i <= pile_graham->sommet; i++) {
        t_element p1 = pile_graham->items[i];
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);

        //delai-ecran apres chaque ligne
        delai_ecran(DELAI_ECRAN);

        printf("Point : %d\n", p1.position);
        p0 = p1;
    }

    // Fermer l'enveloppe
    dessiner_lig(p0.posx, p0.posy, pt_fin.posx, pt_fin.posy);
    delai_ecran(DELAI_ECRAN);
    printf("Point (fin) : %d\n", pt_fin.position);
}

/*=========================================================*/
/*                 SIMULATION_MOYENNE                      */
/*    fonction qui effectue "nb_tests" parcours de Graham  */
/*     avec "nb_pts" points aleatoires, sans affichages    */
/*=========================================================*/
double simulation_moyenne(int nb_pts, int nb_tests) {
    t_pile pile_Graham;          //pile de l'enveloppe
    t_point *tab_pts = NULL;     //tableau dynamique des points
    t_point h_ref = { 0 }; //point de reference horizontal
    int p_min;                   //position du point minimal
    int nb_pts_tot = 0;          //total des points de l'enveloppe

    //alloue le tableau de points et valide l'allocation
    tab_pts = (t_point *) malloc(nb_pts * sizeof(t_point));
    assert(tab_pts);

    for (int i = 0; i < nb_tests; i++) {
        //initialise la pile pour ce test
        pile_Graham = init_pile(nb_pts);

        //genere des points aleatoires
        init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

        //trouve et place le point minimal et cree la reference
        p_min = trouver_pt_minimal(tab_pts, nb_pts);
        h_ref = placer_pt_reference(tab_pts, p_min);

        //calcule les coordonnees polaires et trie les points
        calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
        trier_pts(tab_pts, nb_pts);

        //parcours de Graham sans affichage et cumule la taille de l'enveloppe
        nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

        //libere la pile avant le prochain test
        liberer_pile(&pile_Graham);
    }

    //libere le tableau de points
    free(tab_pts);

    //retourne la moyenne

    return (double) nb_pts_tot / nb_tests;
}
