/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	interactions.cpp                                                */
/*  Auteur : Massimo Faulkner                                       */
/*                                                                  */
/*	Description: Module d'interaction avec l'usager et les          */
/*               fichier externes                                   */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include "interactions.h"


/*=========================================================*/
/*                    DEMANDER_MODE                        */
/* fonction qui demande a l'usager un des trois modes      */
/*                    d'execution                          */
/*=========================================================*/
int demander_mode(void) {
    int good;
    int mode;

    do {

        printf("Choisir le mode d'execution :\n");
        printf("  %d) mode aleatoire\n", MODE_ALEA);
        printf("  %d) mode fichier\n", MODE_FICHIER);
        printf("  %d) mode simulation\n", MODE_SIMULATION);
        printf("Votre choix : ");
        good = scanf("%d", &mode);
        FFLUSH();

        if (good != 1 || mode < MODE_ALEA || mode > MODE_SIMULATION) {
            good = 0;
        }

        if (good == 0) {
            printf("Entrez un nombre valide\n\n");
        }

    } while (!good);

    return mode;
}


/*=========================================================*/
/*                   CHOISIR_FICHIER                       */
/*      fonction qui permet de selectionner un des         */
/*         fichiers-texte de points disponibles            */
/*=========================================================*/
FILE * choisir_fichier(void) {
    FILE * fichier = NULL;
    char nom_fichier[80];

    do {
        printf("Entrez le nom du fichier: ");
        scanf("%79s", nom_fichier);
        FFLUSH();

        fichier = fopen(nom_fichier, "rt");

        if (fichier == NULL) {
            printf("Erreur d'ouverture du fichier\n\n");
        }
    } while (fichier == NULL);
    
    return fichier;
}


/*=========================================================*/
/*                    LIRE_POINTS                          */
/*     fonction qui lis tous les points du fichier et      */
/*        retourne un tableau dynamique de points          */
/*=========================================================*/
t_point * lire_points(FILE *fichier, int *nb_pts) {
    t_point * points;
    int nombre_points;

    if (fscanf(fichier, "%d", &nombre_points) != 1 || nombre_points <= 0) {
        printf("Erreur de lecture du nombre de points\n");
        return NULL;
    }

    points = (t_point *) malloc((size_t) nombre_points * sizeof(t_point));
    if (points == NULL) {
        printf("Erreur d'allocation de la memoire\n");
        return NULL;
    }

    for (int i = 0; i < nombre_points; i++) {
        if (fscanf(fichier, "%d %d", &points[i].posx, &points[i].posy) != 2) {
            printf("Erreur de lecture des points\n");
            return NULL;
        }

        points[i].rad = 0.0;
        points[i].dist = 0.0;
        points[i].position = 0;
    }

    fclose(fichier);

    *nb_pts = nombre_points;
    return points;
}