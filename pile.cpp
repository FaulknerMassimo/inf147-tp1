/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	pile.h                                                          */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Module de gestion d'une pile                       */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include "pile.h"


/*=========================================================*/
/*                       INIT_PILE                         */
/*      fonction qui initialise le tableau de la pile      */
/*=========================================================*/
t_pile init_pile(int taille) {
    //vide la pile
    t_pile pile = {NULL, -1, 0};

    //si la taille est invalide, retourne la pile vide
    if (taille <= 0) {
        return pile;
    }

    //alloue le tableau dynamique des elements
    pile.items = (t_element *) malloc(taille * sizeof(t_element));

    //memorise la capacite de la pile
    pile.taille = taille;
    return pile;
}


/*=========================================================*/
/*                     LIBERER_PILE                        */
/*       fonction qui libere l'allocation de memoire       */
/*             et vide les champs de la pile               */
/*=========================================================*/
void liberer_pile(t_pile * pile) {
    //rien a liberer si le pointeur est NULL
    if (pile == NULL) {
        return;
    }

    //libere le tableau puis remet les champs a leur etat initial
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
    //si la pile est invalide ou vide, retourne 0
    if (pile == NULL || pile->sommet < 0) {
        return 0;
    }

    //le sommet est un indice (nombre d'elements = sommet + 1)
    return pile->sommet + 1;
}


/*=========================================================*/
/*                         PUSH                            */
/*        fonction qui ajoute un element au sommet         */
/*=========================================================*/
void push(t_pile * pile, t_element * elem) {
    //avance le sommet puis copie l'element a cette position
    pile->sommet++;
    pile->items[pile->sommet] = *elem;
}


/*=========================================================*/
/*                          POP                            */
/*       fonction qui retire l'element au sommet           */
/*=========================================================*/
void pop(t_pile * pile) {
    //recule le sommet
    pile->sommet--;
}


/*=========================================================*/
/*                       GET_SOMMET                        */
/*      fonction qui copie l'element au sommet sans        */
/*                    modifier la pile                     */
/*=========================================================*/
int get_sommet(const t_pile * pile, t_element * elem) {
    //echec si les pointeurs sont invalides ou si la pile est vide
    if (pile == NULL || elem == NULL || pile->items == NULL ||
        pile->sommet < 0) {
        return 0;
    }

    //copie le sommet dans elem
    *elem = pile->items[pile->sommet];
    return 1;
}


/*=========================================================*/
/*                    GET_SUIV_SOMMET                      */
/*   fonction qui copie l'element suivant du sommet sans   */
/*                    modifier la pile                     */
/*=========================================================*/
int get_suiv_sommet(const t_pile * pile, t_element * elem) {
    //echec si les pointeurs sont invalides ou s'il y a moins de 2 elements
    if (pile == NULL || elem == NULL || pile->items == NULL ||
        pile->sommet < 1) {
        return 0;
    }

    //copie l'element sous le sommet dans elem
    *elem = pile->items[pile->sommet - 1];
    return 1;
}
