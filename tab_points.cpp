/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	tab_points.cpp                                                  */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Pour creer le tableau de points                    */
/********************************************************************/

// Librairies usuelles a inclure
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tab_points.h"


/*=========================================================*/
/*                       DISTANCE                          */
/*      fonction qui calcule la distance euclidienne       */
/*                   entre deux points                     */
/*=========================================================*/
double distance(t_point * pA, t_point * pB) {
    return sqrt(pow(pB->posx - pA->posx, 2) + pow(pB->posy - pA->posy, 2));
}


/*=========================================================*/
/*                    PROD_VECTORIEL                       */
/*       fonction qui calcule le produit vectoriel         */
/*                   de deux vecteurs                      */
/*=========================================================*/
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2) {
    double a = p2->posx - p0->posx;
    double b = p1->posx - p0->posx;
    double c = p2->posy - p0->posy;
    double d = p1->posy - p0->posy;

    return a*d - b*c;
}


/*=========================================================*/
/*                    COORD_POLAIRE                        */
/*    fonction qui calcule l'angle polaire d'un vecteur    */
/*           par rapport a l'axe horizontale               */
/*=========================================================*/
double coord_polaire(t_point * pA, t_point pB, t_point * h_ref) {
    double dist = distance(pA, &pB);
    double angle = asin((pB.posy - pA->posy)/dist);
    double produit = prod_vectoriel(pA, h_ref, &pB);

    if (produit > 0) {
        return angle;
    }
    else if (produit < 0) {
        return 2*((asin(1)/2) - angle) + angle;
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
static int alea(int min, int max) {
    return (rand() % (max - min + 1) + min);
}


/*=========================================================*/
/*                    INIT_TAB_ALEA                        */
/*      fonction qui initialise tous les points du         */
/*        tableau avec des coordonnees aleatoires          */
/*=========================================================*/
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {
    int posy_deja_utilise;

    for (int i = 0; i < taille; i++) {
        tab_pts[i].posx = alea(1, maxx);

        do {
            tab_pts[i].posy = alea(1, maxy);
            posy_deja_utilise = 0;

            for (int j = 0; j < i; j++) {
                if (tab_pts[j].posy == tab_pts[i].posy) {
                    posy_deja_utilise = 1;
                }
            }
        } while (posy_deja_utilise);
    }
}


/*=========================================================*/
/*                 TROUVER_PT_MINIMAL                      */
/*      fonction qui trouve l'indice du point minimal      */
/*               de depart dans un tableau                 */
/*=========================================================*/
int trouver_pt_minimal(const t_point tab_pts[], int taille) {
    int pt_minimal = 0;
    int pt_x;
    int indice = -1;

    for (int i = 0; i < taille; i++) {
        if (indice == -1) {
            pt_minimal = tab_pts[i].posy;
            pt_x = tab_pts[i].posx;
            indice = i;
        }
        else if (tab_pts[i].posy < pt_minimal) {
            pt_minimal = tab_pts[i].posy;
            pt_x = tab_pts[i].posx;
            indice = i;
        }
        else if (tab_pts[i].posy == pt_minimal) {
            if (tab_pts[i].posx < pt_x) {
                pt_minimal = tab_pts[i].posy;
                pt_x = tab_pts[i].posx;
                indice = i;
            }
        }
    }

    return indice;
}


/*=========================================================*/
/*                 PLACER_PT_REFERENCE                     */
/*     fonction qui place le point minimal dans la case    */
/*      [0] du tableau et cree le point de reference       */
/*=========================================================*/
t_point placer_pt_reference(t_point tab_pts[], int pos_min) {
    t_point point_minimal = tab_pts[pos_min];

    tab_pts[pos_min] = tab_pts[0];
    tab_pts[0] = point_minimal;

    t_point point_reference = {tab_pts[0].posx, 800, 0.0, 0.0, 0};
    return point_reference;
}


/*=========================================================*/
/*               CALCUL_COORD_POLAIRES                     */
/*     fonction qui calcule l'angle polaire relatif        */
/*           au point minimal et sa distance               */
/*=========================================================*/
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref) {
    for (int i = 1; i < taille; i++) {
        tab_pts[i].rad = coord_polaire(&tab_pts[0], tab_pts[i], ref);
        tab_pts[i].dist = distance(&tab_pts[0], &tab_pts[i]);
    }
}


/*=========================================================*/
/*                    TRIER_PTS                            */
/*       fonction qui effectue un tri des points           */
/*     en ordre croissant de leurs angles polaires         */
/*=========================================================*/
void trier_pts(t_point tab_pts[], int taille) {
    for (int i = 2; i < taille; i++) {
        t_point copie = tab_pts[i];
        int j;

        for (j = i; j > 1 && (tab_pts[j - 1].rad >= copie.rad); j--) {
            tab_pts[j] = tab_pts[j - 1];
        }

        tab_pts[j] = copie;
    }
}