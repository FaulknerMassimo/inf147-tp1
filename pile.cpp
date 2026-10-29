/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	pile.h                                                          */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Module de gestion d'une pile                       */
/********************************************************************/

// Librairies usuelles a inclure 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pile.h"


/*=========================================================*/
/*                       INIT_PILE                         */
/*      fonction qui initialise le tableau de la pile      */
/*=========================================================*/
t_pile init_pile(int taille) {
    t_pile pile = {NULL, -1, 0};

    if (taille <= 0) {
        return pile;
    }

    pile.items = (t_element *) malloc(taille * sizeof(t_element));

    pile.taille = taille;
    return pile;
}


/*=========================================================*/
/*                     LIBERER_PILE                        */
/*       fonction qui libere l'allocation de memoire       */
/*             et vide les champs de la pile               */
/*=========================================================*/
void liberer_pile(t_pile * pile) {
    if (pile == NULL) {
        return;
    }

    free(pile->items);
    pile->items = NULL;
    pile->sommet = -1;
    pile->taille = 0;
}


/*=========================================================*/
/*                    GET_NB_ELEMENTS                      */
/*       fonction qui retourne le nombre d'elements        */
/*                  actuellement empiles                   */
/*=========================================================*/
int get_nb_elements(const t_pile * pile) {
    if (pile == NULL || pile->sommet < 0) {
        return 0;
    }

    return pile->sommet + 1;
}


/*=========================================================*/
/*                         PUSH                            */
/*        fonction qui ajoute un element au sommet         */
/*=========================================================*/
void push(t_pile * pile, t_element * elem) {
    pile->sommet++;
    pile->items[pile->sommet] = *elem;
}


/*=========================================================*/
/*                          POP                            */
/*       fonction qui retire l'element au sommet           */
/*=========================================================*/
void pop(t_pile * pile) {
    pile->sommet--;
}


/*=========================================================*/
/*                       GET_SOMMET                        */
/*      fonction qui copie l'element au sommet sans        */
/*                    modifier la pile                     */
/*=========================================================*/
int get_sommet(const t_pile * pile, t_element * elem) {
    if (pile == NULL || elem == NULL || pile->items == NULL ||
        pile->sommet < 0) {
        return 0;
    }

    *elem = pile->items[pile->sommet];
    return 1;
}


/*=========================================================*/
/*                    GET_SUIV_SOMMET                      */
/*   fonction qui copie l'element suivant du sommet sans   */
/*                    modifier la pile                     */
/*=========================================================*/
int get_suiv_sommet(const t_pile * pile, t_element * elem) {
    if (pile == NULL || elem == NULL || pile->items == NULL ||
        pile->sommet < 1) {
        return 0;
    }

    *elem = pile->items[pile->sommet - 1];
    return 1;
}
