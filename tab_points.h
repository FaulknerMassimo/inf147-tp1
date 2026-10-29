/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	tab_points.h                                                    */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Pour creer le tableau de points                    */
/********************************************************************/


#ifndef TAB_POINTS_H
#define TAB_POINTS_H

/*=========================================================*/
/*                          TYPES                          */
/*=========================================================*/

typedef struct {
    int posx, posy; //coordonnees x, y du point dans le plan
    double rad;     //angle polaire relatif au point minimal
    double dist;    //la distance relative au point minimal
    int position;   //position-tableau du point suite au tri
} t_point;


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*                       DISTANCE                          */
/*      fonction qui calcule la distance euclidienne       */
/*                   entre deux points                     */
/* ENTREE: points pA et pB qu'on veut calculer la distance */
/*        SORTIE: la distance entre les deux points        */
double distance(t_point * pA, t_point * pB);


/*                    PROD_VECTORIEL                       */
/*       fonction qui calcule le produit vectoriel         */
/*                   de deux vecteurs                      */
/*   ENTREE: points p0, p1 et p2 qui forment les vecteurs  */
/*        qu'on veut calculer le produit vectoriel         */
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2);


/*                    COORD_POLAIRE                        */
/*    fonction qui calcule l'angle polaire d'un vecteur    */
/*           par rapport a l'axe horizontale               */
/*     ENTREE: points pA et pB qui forment le vecteur      */
/*   qu'on veut trouver l'angle et le point de reference   */
/*   h_ref qui sera toujours a la verticale du point pA    */
double coord_polaire(t_point * pA, t_point pB, t_point * h_ref);


/*                    INIT_TAB_ALEA                        */
/*      fonction qui initialise tous les points du         */
/*        tableau avec des coordonnees aleatoires          */
/*     ENTREE: tableau tab_pts[], la taille du tableau,    */
/*      la coordonnee maximale de x et la coordonnee       */
/*                   maximale de y                         */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);


/*                 TROUVER_PT_MINIMAL                      */
/*      fonction qui trouve l'indice du point minimal      */
/*               de depart dans un tableau                 */
/*     ENTREE: tableau tab_pts[] qu'on veut trouver le     */
/*     point minimal de depart et la taille du tableau     */
/*       SORTIE: l'indice du point minimal de depart       */
int trouver_pt_minimal(const t_point tab_pts[], int taille);


/*                 PLACER_PT_REFERENCE                     */
/*     fonction qui place le point minimal dans la case    */
/*      [0] du tableau et cree le point de reference       */
/*          ENTREE: tableau tab_pts[] et indice            */
/*              pos_min du point minimal                   */
/*     SORTIE: le point de reference horizontal cree       */
t_point placer_pt_reference(t_point tab_pts[], int pos_min);


/*               CALCUL_COORD_POLAIRES                     */
/*     fonction qui calcule l'angle polaire relatif        */
/*           au point minimal et sa distance               */
/*   ENTREE: le tableau de points, la taille du tableau    */
/*              et le point de reference                   */
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref);


/*                    TRIER_PTS                            */
/*       fonction qui effectue un tri des points           */
/*     en ordre croissant de leurs angles polaires         */
/*   ENTREE: tableau des points et taille du tableau       */
void trier_pts(t_point tab_pts[], int taille);

#endif