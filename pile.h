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


/*                     LIBERER_PILE                        */
/*       fonction qui libere l'allocation de memoire       */
/*             et vide les champs de la pile               */
/*            ENTREE: la pile qu'on veut vider             */
void liberer_pile(t_pile * pile);


/*                    GET_NB_ELEMENTS                      */
/*       fonction qui retourne le nombre d'elements        */
/*                  actuellement empiles                   */
/*    ENTREE: la pile qu'on veut le nombre d'elements      */
/*   SORTIE: le nombre d'elements actuellement empiles     */
int get_nb_elements(const t_pile * pile);


/*                         PUSH                            */
/*        fonction qui ajoute un element au sommet         */
/*         ENTREE: la pile et l'element a ajouter          */
void push(t_pile * pile, t_element * elem);


/*                          POP                            */
/*       fonction qui retire l'element au sommet           */
/*   ENTREE: la pile et le pointeur pour l'element enleve  */
void pop(t_pile * pile);


/*                       GET_SOMMET                        */
/*      fonction qui copie l'element au sommet sans        */
/*                    modifier la pile                     */
/*  ENTREE: la pile qu'on veut copier l'element au sommet  */
/*              et le pointeur pour l'element              */
/*          SORTIE: 1 en cas de succes, 0 sinon            */
int get_sommet(const t_pile * pile, t_element * elem);


/*                    GET_SUIV_SOMMET                      */
/*   fonction qui copie l'element suivant du sommet sans   */
/*                    modifier la pile                     */
/*   ENTREE: la pile qu'on veut copier l'element suivant   */
/*         du sommet et le pointeur pour l'element         */
/*          SORTIE: 1 en cas de succes, 0 sinon            */
int get_suiv_sommet(const t_pile * pile, t_element * elem);
