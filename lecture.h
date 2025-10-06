#ifndef LECTURE_H_INCLUDED
#define LECTURE_H_INCLUDED
#include "stack.h"
#include "image.h"

/*
Ce type sert à garder en mémoire différentes coordonnées, notemment couplé au type lcoord
*/
typedef struct {
    int x;
    int y;
} coord;

typedef struct {
    coord* l;
    int taille;
    int compteur;
} lcoord;

/*
ce type permet de garder en mémoire la direction et le bord pour s'assurer de l'itinéraire régulant les déplacements à l'interieur de l'image
*/
typedef struct {
    int direction;
    int bord;
} itineraire;

/*
@requires deux valeurs
@assign rien
@ensure renvoie 0 si les deux valeurs sont différentes et 1 sinon
*/

int egal_valeur(valeur v1, valeur v2);

/*
@requires un tableau, deux entier x et y, une valeur, et une matrice d'entier
@assign un tableau
@ensure met dans la liste de coordonées toutes les coordonnée des éléments du bloc associé à la valeur v situé en (x,y)
*/
void bloc(calque* cal, int x, int y, valeur v, int** traite, lcoord* list);

/*
@requires un pointeur de calque, un pointeur vers une lcoord (liste de coordonnée) traduisant un bloc, deux entiers représentant respectivement la direction et le bord
@assign de la mémoire pour une lcoord
@ensure renvoie les coordonnées du pixel correspondant à l'endroit où le programme va essayer de sortir pour changer de bloc 
*/
coord recherche_du_pixel_de_depart(calque* cal, lcoord* list, itineraire* db);

/*
@requires un pointeur de calque, deux entiers x et y, un itineraire, entier de fin, et la pile sur laquelle faire les actions
@assign la fonction n'assign rien en elle-même, mais appelle d'autres fonctions qui modifie la mémoire
@ensure correspond à un pas de l'execution du programme (assure le passage d'un pixel au suivant) 
*/
void suivant(calque* cal, int x_0, int y_0, itineraire* db, int fin, stack* p);


#endif // LECTURE_H_INCLUDED