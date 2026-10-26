/*
 Programme : Devoir 1
 Par    : Massimo Faulkner
 Date   : 15 octobre 2026

*/

/*=========================================================*/

//Permet de desactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles a inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*=========================================================*/
/*                      CONSTANTES                         */
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


/*                        ALEA                             */
/*            fonction qui retourne un entier              */
/*              aleatoire entre deux bornes                */
/* ENTREE: les bornes min et max entre l'entier aleatoire  */
/*              SORTIE: l"entier aleatoire                 */
int alea(int min, int max);


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


//A FAIRE
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref);


//A FAIRE
void trier_pts(t_point tab_pts[], int taille);

/*=========================================================*/
/*                PROGRAMME PRINCIPAL                      */
/*=========================================================*/
int main(void) {

    //A FAIRE


    //retour obligatoire si le "main()" est de type "int"
	return EXIT_SUCCESS;
}


/*=========================================================*/
/*                       DISTANCE                          */
/*      fonction qui calcule la distance euclidienne       */
/*                   entre deux points                     */
/*=========================================================*/
double distance(t_point * pA, t_point * pB) {
    return sqrt(pow(pB.posx - pA.posx, 2) + pow(pB.posy - pA.posy, 2));
}


/*=========================================================*/
/*                    PROD_VECTORIEL                       */
/*       fonction qui calcule le produit vectoriel         */
/*                   de deux vecteurs                      */
/*=========================================================*/
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2) {
    double a = p2.posx - p0.posx;
    double b = p1.posx - p0.posx;
    double c = p2.posy - p0.posy;
    double d = p1.posy - p0.posy;

    return a*d - b*c;
}


/*=========================================================*/
/*                    COORD_POLAIRE                        */
/*    fonction qui calcule l'angle polaire d'un vecteur    */
/*           par rapport a l'axe horizontale               */
/*=========================================================*/
double coord_polaire(t_point * pA, t_point pB, t_point * h_ref) {
    double dist = distance(pA, pB);
    double angle = asin((pB.posy - pA.posy)/dist);
    produit = prod_vectoriel(pA, h_ref, pB);

    if (produit > 0) {
        return angle;
    }
    else if (produit < 0) {
        return 2*((pi()/2) - angle) + angle;
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
int alea(int min, int max) {
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
    int pt_minimal = NULL;
    int pt_x;
    int indice;

    for (int i = 0; i < taille; i++) {
        if (pt_minimal == NULL) {
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


void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref) {
    //A FAIRE
}


void trier_pts(t_point tab_pts[], int taille) {
    //A FAIRE
}