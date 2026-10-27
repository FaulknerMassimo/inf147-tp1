/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	pile.h                                                          */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Module de gestion d'une pile                       */
/********************************************************************/

// Librairies usuelles a inclure 
#include "tab_points.h"


/*=========================================================*/
/*                          TYPES                          */
/*=========================================================*/

typedef t_point t_element;

typedef struct {
    t_element * items;	  //tableau dynamique des éléments de la pile
    int sommet;			  //position du sommet (top) de la pile, sera == -1 lorsque vide 
	int taille;			  //taille maximale du tableau dynamique des éléments
} t_pile;


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*                       INIT_PILE                         */
/*      fonction qui initialise le tableau de la pile      */
/*              ENTREE: la taille du tableau               */
/*            SORTIE: une copie de la pile vide            */
t_pile init_pile(int taille);