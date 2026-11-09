/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	interactions.h                                                  */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Module d'interaction avec l'usager et les          */
/*               fichier externes                                   */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tab_points.h"


/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

#define MODE_ALEA 1
#define MODE_FICHIER 2
#define MODE_SIMULATION 3


/*=========================================================*/
/*                   MACRO-FONCTIONS                       */
/*=========================================================*/

//macro-fonction FFLUSH() qui flush la memoire du scanf
#define FFLUSH() while (getchar() != '\n') {}


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/

/*                    DEMANDER_MODE                        */
/* fonction qui demande a l'usager un des trois modes      */
/*                    d'execution                          */
/*  SORTIE: MODE_ALEA (1) pour le mode aleatoire a 20      */
/*     points, MODE_FICHIER (2) pour le mode a partir      */
/*     d'un fichier texte, MODE_SIMULATION (3) pour le     */
/*                 mode simulation                         */
int demander_mode(void);


/*                   CHOISIR_FICHIER                       */
/*      fonction qui permet de selectionner un des         */
/*         fichiers-texte de points disponibles            */
/*     SORTIE: le pointeur d'acces au fichier choisi       */
FILE * choisir_fichier(void);


/*                    LIRE_POINTS                          */
/*     fonction qui lis tous les points du fichier et      */
/*        retourne un tableau dynamique de points          */
/*      ENTREE: le pointeur pour le fichier texte et       */
/*             le nombre de points a lire                  */
/*        SORTIE: le tableau dynamique de points           */
t_point * lire_points(FILE *fichier, int *nb_pts);