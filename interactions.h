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
/*                   MACRO-FONCTIONS                       */
/*=========================================================*/

//macro-fonction FFLUSH() qui flush la memoire du scanf
#define FFLUSH() while (getchar() != '\n') {}


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/

/*                    DEMANDER_MODE                        */
/* fonction qui demande a l'usager deux modes d'execution  */
/*    SORTIE: 1 pour mode aleatoire a 20 points, 2 pour    */
/*           mode a partir d'un fichier texte              */
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